/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */
#define RATIO 4
#include "definitions.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
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

int main(int argc, char **argv)
{
  double H, w, s, W, er;
  // Zodd, Zeven, Zo;
  int bmp_size=18, q; 
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

  H=atof(argv[my_optind]);
  w=atof(argv[my_optind+1]);
  s=atof(argv[my_optind+2]);
  er=atof(argv[my_optind+3]);
  if(er <1.0)
  {
    fprintf(stderr,"Er must be 1.0 or more \n");
    exit(1);
  }

  W=2.0*w+s+RATIO*H;
  printf("W=%f\n",W);
  optimise.float_values[0]=W            ;   /* minimum width as a float*/
  optimise.float_values[1]=H;               /* height in floats */
  optimise.float_values[2]=w;               /* stripline width */
  optimise.float_values[3]=s;               /* spacing between the strips */

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
  exit(0);
}

double calculate_integer_values(struct data *optimise,int nmax,int accuracy_level)
{
  double grid_size=500, error=0, error_max=1e6; 
  int i, min_pixels, max_pixels, n, min_critical_pixels, max_critical_pixels;
  int best_i, most_critical; 
  double min_pixel_size, max_pixel_size;
  double W, H, best_grid_size, w, s;

  for(i=0;i<9;++i)
    optimise->best[i]=-1;   /* A silly value, indicating it is not acceptable */
 
  /* Let the number of pixel in the image be between 2^n and 2^(n+2) */

  min_pixels=(int) pow(2.0,accuracy_level-1);
  max_pixels=(int) pow(2.0,accuracy_level+1);

  /* Although the stucture W by H has an exact area of W*H, we will    
  allocate some pixels to  this, which will be much smaller than
  the W*H. Each pixel will have a variable area, which we don't  
  know yet, but can put upper and lower limits on it. 
  */

  W=optimise->float_values[0];  /* The calculated W and H  */ 
  H=optimise->float_values[1];
  w=optimise->float_values[2];  /* The calculated W and H  */ 
  s=optimise->float_values[3];

  min_pixel_size=sqrt(W*H/max_pixels);
  max_pixel_size=sqrt(W*H/min_pixels);

  printf("W=%f H=%f w=%f s=%f min=%d max=%d nmax=%d\n",W,H,w,s,min_pixels, max_pixels, nmax);
  printf("min_pixel_size=%f max_pixels_size=%f \n",min_pixel_size, max_pixel_size);
  /* find the most critical dimension */
  for(n=0;n<nmax;n++)
  {
    if(optimise->importance[n]==MOST_IMPORTANT)
      most_critical=n;
  }
  /* we will allocate a number of pixels to this most critical 
  dimension, set by */
  
  min_critical_pixels = optimise->float_values[most_critical]/max_pixel_size;
  max_critical_pixels = optimise->float_values[most_critical]/min_pixel_size;

  printf("mcd = %f min crit = %d max crit = %d\n", optimise->float_values[most_critical],min_critical_pixels,max_critical_pixels);

  for(i=min_critical_pixels; i<max_critical_pixels;++i)
  {
    /* set the most critical dimension to i pixels, trying every i 
    between two set limits */

    optimise->int_values[most_critical]=i;
    grid_size=optimise->float_values[most_critical]/i;

    /* Now set all the others to the optimal, assuming i would be used
    for the most critical dimension */
    error=0.0;
    for(n=0; n<nmax;++n)
    {
      optimise->int_values[n]=(int) (0.5+optimise->float_values[n]/grid_size);
      if (optimise->importance[n] != NOT_IMPORTANT)
      {
       error+=fabs((double)optimise->int_values[n]*grid_size-optimise->float_values[n]);
       //printf("error=%f i=%d n=%d int_values[%d]=%d float_values[%d]=%f\n",error,i,n,n,optimise->int_values[n],n,optimise->float_values[n]);
      }
    }
    if(error<error_max)
    {
     error_max=error;
     best_i=i;
     best_grid_size=grid_size;
     for(n=0; n<nmax;++n)
       optimise->best[n]=optimise->int_values[n];
     printf("good at i=%d\n",i);
    }
    printf("grid_size=%f error=%g ermax=%f\n",grid_size,error,error_max);
  }
  printf("optimal are: %d %d %d %d best_grid_size=%f %f %f %f %f\n",optimise->best[0], optimise->best[1], optimise->best[2], optimise->best[3], best_grid_size, best_grid_size*optimise->best[0], best_grid_size*optimise->best[1], best_grid_size*optimise->best[2], best_grid_size*optimise->best[3]);
  printf("size=W*H=%d\n",optimise->best[0]*optimise->best[1]);
  return(error_max); /* return the error */
}
