#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"


/* These items are supplied on the commmand line */

extern double dd, WW, HH, xx, yy, Er1;
extern int d, W, H, x, y;
extern int verbose;

void check_circ_in_rect_doubles(void)
{
   if( Er1<1.0) 
      error_and_exit("The relative permittivity (Er) must be >= 1.0",100);
   if (dd/2.0+yy >= HH) 
      error_and_exit("The inner will be touching the top or bottom of the outer !!! ",100);
   if (dd/2.0+xx >= WW) 
      error_and_exit("The inner will be touching one of the sides !!! ",100);
      
}

void check_circ_in_rect_int(void)
{
/*
   if(verbose==TRUE)
      fprintf(stderr,"d_outer = %d d_inner=%d offset=%h \n",D, d, h);
      */
}
