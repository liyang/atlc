/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

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

#include "definitions.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

double calculate_integer_values(struct data *optimise,int nmax,int accuracy_level)
{
  double grid_size=500, error=0, error_max=1e6; 
  int i, min_pixels, max_pixels, n, min_critical_pixels, max_critical_pixels;
  int best_i, most_critical=0, step=1; 
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

  //printf("W=%f H=%f w=%f s=%f min=%d max=%d nmax=%d\n",W,H,w,s,min_pixels, max_pixels, nmax);
  //printf("min_pixel_size=%f max_pixels_size=%f \n",min_pixel_size, max_pixel_size);
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

  //printf("mcd = %f min crit = %d max crit = %d\n", optimise->float_values[most_critical],min_critical_pixels,max_critical_pixels);

  /* Normally we would try every combination of i, but it may be necessary to keep it even or odd */
  //printf("od or even=%d\n", optimise->odd_or_even[most_critical]);
  if(optimise->odd_or_even[most_critical] == ODD  &&  min_critical_pixels%2==0) 
    min_critical_pixels--;
  else if(optimise->odd_or_even[most_critical] == EVEN  &&  min_critical_pixels%2==1) 
    min_critical_pixels--;
  if(optimise->odd_or_even[most_critical] != DONT_CARE)
    step=2;

  for(i=min_critical_pixels; i<max_critical_pixels;i+=step)
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
    /* Since the numbers generated for the integers seeme to differ on different
    computers, I've suspected the problem might be that an error is very
    similar at two different sets of integer values. Hence I will only
    consider the error lower its lower by 1e-9. That should avoid silly
    rounding problems. */

    if(error<(error_max-TINY)) /* The 1e-9 avoids different results on different*/
    {                          /* machines due to rounding errors */
     error_max=error;
     best_i=i;
     best_grid_size=grid_size;
     for(n=0; n<nmax;++n)
       optimise->best[n]=optimise->int_values[n];
     //printf("good at i=%d\n",i);
    }
    //printf("grid_size=%f error=%g ermax=%f\n",grid_size,error,error_max);
  }
  //printf("optimal are: %d %d %d %d best_grid_size=%f %f %f %f %f\n",optimise->best[0], optimise->best[1], optimise->best[2], optimise->best[3], best_grid_size, best_grid_size*optimise->best[0], best_grid_size*optimise->best[1], best_grid_size*optimise->best[2], best_grid_size*optimise->best[3]);
  //printf("size=W*H=%d\n",optimise->best[0]*optimise->best[1]);
  return(error_max); /* return the error */
}
