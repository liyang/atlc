#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"


/* These items are supplied on the commmand line */

extern double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2;
extern int W, H, a, b, c, d, w, h;
extern int verbose;

void check_rect_in_rect_doubles(void)
{
   if( (Er1<1.0) || (Er2 <1.0))
      error_and_exit("Both Er1  and Er2 must be >= 1.0",100);
   if(aa+dd>WW)
      error_and_exit("the dielectric extends horizontally outside the box (a+d>W)",100);
   if(bb+ww>=WW)
      error_and_exit("the inner conductor extends horizontally beyond the outer conductor(b+w>=W)",101);
   if(cc<=0.0)
      error_and_exit("The inner conductors's thickness (c) must be greater than zero ",12);
   if(hh<=0.0)
      error_and_exit("The thickness of dielectric Er2 (h) must be greater than zero ",12);
   if(hh+cc>=HH)
      error_and_exit("the inner conductor extends verticaly beyond the outer conductor(c+h>=H)",101);
   if((WW<=0.0) || (HH<=0.0) || (aa<0.0) || (bb<0.0) || (cc<=0.0) || (dd<=0.0)
   ||(ww<=0.0) || (hh<=0.0))
      error_and_exit("W,H,c,d,w, & h must be positive numbers. Non-integers are okay, but they must be >0 \n",102); 
      
}

void check_rect_in_rect_int(void)
{
   if(verbose==TRUE)
      fprintf(stderr,"W=%d H=%d a=%d b=%d c=%d d=%d w=%d h=%d\n",W,H,a,b,c,d,w,h);
   if(a < 1)
      error_and_exit("internal paramter 'a' is less that 1. This indicates the LHS of the dielectric",102); 
}
