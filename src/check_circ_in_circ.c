#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"


/* These items are supplied on the commmand line */

extern double DD, dd, hh, Er1;
extern int D, d, h;
extern int verbose;

void check_circ_in_circ_doubles(void)
{
   if( Er1<1.0) 
      error_and_exit("Error #9. The relative permittivity (Er) must be >= 1.0",9);
   if (dd/2.0+hh >= DD) 
      error_and_exit("Error #10 The inner will be touching the outer !!!",10);
}

void check_circ_in_circ_int(void)
{
   if(verbose==TRUE)
      fprintf(stderr,"d_outer = %d d_inner=%d offset=%x \n",D, d, h);
}
