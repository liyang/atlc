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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

double aa, bb, cc, dd, hh, ww, DD, WW, HH, Er1, Er2;
int a, b, c, d, h, w, D, W, H;

int verbose=FALSE;
int lowest=50, highest=100;
int fileflag=FALSE;

/* The following are only needed so that I can link in both 
convert_circ_in_circ_dimensions_to_integers.c
and convert_rect_in_rect_dimensions_to_integers.c
*/


extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
   int  bmp_size=DEFAULT_BMPSIZE;
   int q;
   FILE *image_data_fp=stdout;
   double Zo, x, HHH;

   while((q=get_options(argc,argv,"b:f:v")) != -1)
   switch (q) 
   {
      case 'b':
      bmp_size=atol(my_optarg); 
      break;
      case 'f':
      /* By default bitmap image goes to stdout, but we can send to a file 
      with the -f option. */
      if((image_data_fp=fopen(my_optarg,"w"))==NULL)
      {
	 fprintf(stderr,"Can't write to %s. Exiting ...\n",my_optarg);
	 exit(1);
      }
      fileflag=TRUE;
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
   if(argc-my_optind ==4)
   {
      DD=atof(argv[my_optind]);
      WW=HH=DD;
      dd=atof(argv[my_optind+1]);
      hh=atof(argv[my_optind+2]);
      Er1=atof(argv[my_optind+3]);
      check_circ_in_circ_doubles();
      convert_circ_in_circ_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp);
      HHH=(DD/2.0)-hh;
      x=(dd*dd+DD*DD-4*hh*hh)/(2*DD*dd);
      x=(double) (d*d+D*D-4*h*h)/(2*D*d);
      Zo=60*log(x+sqrt(x*x-1))/sqrt(Er1); 
      if(verbose == TRUE)
      {
        fprintf(stderr,"DD=%f dd=%f hh=%f x=%f\n",DD, dd, hh, x);
        fprintf(stderr,"D=%d d=%d h=%d x=%f\n",D, d, h, x);
        fprintf(stderr,"Zo is theoretically %f Ohms\n",Zo);
      }
   }
   else
      usage_circ_in_circ();
   exit(0);
}
