/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */

#define RATIO 4
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

#ifdef HAVE_GSL_GSL_COMPLEX_H
#include <gsl/gsl_complex.h>
#endif

#ifdef HAVE_GSL_GSL_COMPLEX_MATH_H
#include <gsl/gsl_complex_math.h>
#endif

double WW, HH, ss, ww, Er1, Er2, DD;
int W, H, s, a, b, c, d, w, h, o;

int main(int argc, char **argv)
{
  double er;
  int bmp_size=18, q; 
  FILE *image_data_fp;
  struct data optimise;

  while((q=get_options(argc,argv,"b:f:v")) != -1)
  switch (q) 
  {
    case 'b':
      bmp_size=atol(my_optarg); 
    break;
  }
  if( (bmp_size==0 && argc-my_optind != 4) || (bmp_size!=0 && argc-my_optind != 5))
  {
    usage_make_coupler();
    exit(1);
  }

  HH=atof(argv[my_optind]);
  ww=atof(argv[my_optind+1]);
  ss=atof(argv[my_optind+2]);
  er=atof(argv[my_optind+3]);
  image_data_fp=fopen(argv[my_optind+4],"wb");
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
  optimise.importance[1]=IMPORTANT;          /* H is critical */
  optimise.importance[2]=IMPORTANT;          /* w is critical */
  optimise.importance[3]=MOST_IMPORTANT;     /* s is most critical */

  optimise.odd_or_even[0]=DONT_CARE;        /* W can be odd or even */
  optimise.odd_or_even[1]=ODD;              /* H must be even */
  optimise.odd_or_even[2]=DONT_CARE;        /* w can be odd or even */
  optimise.odd_or_even[3]=DONT_CARE;        /* s can be odd or even */

  /* We will now optimise for the 4 parameters W, H, w and s, forcing H
  to be odd, and not bothering what the width is, as long as its about
  right. */

  calculate_integer_values(&optimise, 4, bmp_size);
  W=optimise.best[0];
  H=optimise.best[1];

  write_bitmap(image_data_fp);

  exit(0);
}
