/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.

Dr. David Kirkby, e-mail drkirkby@ntlworld.com 

*/

/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */

#define RATIO 8
#include "definitions.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_GSL_GSL_SF_ELLINT_H
#include <gsl/gsl_sf_ellint.h>
#endif

double WW, HH, ss, ww, Er1, Er2;
int W, H, s,  w,  verbose=FALSE;

int main(int argc, char **argv)
{
  double er, return_error;
  double Zodd, Zeven, Zo;
  int bmp_size=DEFAULT_COUPLER_BITMAP_SIZE, q; 
  FILE *image_data_fp;
  struct data optimise;

  while((q=get_options(argc,argv,"b:f:v")) != -1)
  switch (q) 
  {
    case 'b':
      bmp_size=atol(my_optarg); 
    break;
    case 'v':
      verbose=TRUE;
    break;
  }
  if( bmp_size < 6 || (argc-my_optind != 4) || bmp_size>28)
  {
    usage_make_coupler();
    exit(1);
  }

  HH=atof(argv[my_optind]);
  ww=atof(argv[my_optind+1]);
  ss=atof(argv[my_optind+2]);
  //er=atof(argv[my_optind+3]);
  er=1.0;
  image_data_fp=fopen(argv[my_optind+3],"wb");
  if(er <1.0)
  {
    fprintf(stderr,"Er must be 1.0 or more \n");
    exit(1);
  }

  WW=2.0*ww+ss+RATIO*HH;
  optimise.float_values[0]=WW            ;   /* minimum width as a float*/
  optimise.float_values[1]=HH;               /* height in floats */
  optimise.float_values[2]=ww;               /* stripline width */
  optimise.float_values[3]=ss;               /* spacing between the strips */

  optimise.importance[0]=NOT_IMPORTANT;      /* W is non critical */
  optimise.importance[1]=MOST_IMPORTANT;          /* H is critical */
  optimise.importance[2]=IMPORTANT;          /* w is critical */
  optimise.importance[3]=IMPORTANT;     /* s is most critical */

  optimise.odd_or_even[0]=DONT_CARE;        /* W can be odd or even */
  optimise.odd_or_even[1]=ODD;              /* H must be even */
  optimise.odd_or_even[2]=DONT_CARE;        /* w can be odd or even */
  optimise.odd_or_even[3]=DONT_CARE;        /* s can be odd or even */

  /* We will now optimise for the 4 parameters W, H, w and s, forcing H
  to be odd, and not bothering what the width is, as long as its about
  right. */

  return_error=calculate_integer_values(&optimise, 4, bmp_size);
  if(verbose)
    printf("error returned from calculate_integer_values=%g\n", return_error);
  W=optimise.best[0];
  H=optimise.best[1];
  w=optimise.best[2];
  s=optimise.best[3];

  write_bitmap(image_data_fp);
  if(verbose)
  {
    calculate_Zodd_and_Zeven(&Zodd, &Zeven, &Zo, w, H-10, s, 1.0);
    printf("Wanted:            Zodd=%f Zeven=%f Zo=%f\n", Zodd, Zeven, Zo);

    calculate_Zodd_and_Zeven(&Zodd, &Zeven, &Zo, ww, HH, ss, 1.0);
    printf("Actually modelled: Zodd=%f Zeven=%f Zo=%f\n", Zodd, Zeven, Zo);
  }
  exit(0);
}
