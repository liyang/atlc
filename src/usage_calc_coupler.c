#ifdef HAVE_STDLIB_H
#include <stdlib.h>  
#endif

#include "definitions.h"

void usage_calc_coupler(void)
{
  fprintf(stderr,"Usage: sym_strip H w s Er\n\n");
  fprintf(stderr,"calc_coupler calculates Zodd and Zeven for the following coupled lines\n\n");
  fprintf(stderr,"------^---------------------------------------------------\n");
  fprintf(stderr,"      |                                        \n");
  fprintf(stderr,"      |       <---w---><-----s----><---w-->\n");
  fprintf(stderr,"      H       ---------            --------\n");
  fprintf(stderr,"      |                               \n");
  fprintf(stderr,"      |                               \n");
  fprintf(stderr,"------v----------------------------------------------------\n");
  //fprintf(stderr,"<----------------------------W---------------------------->\n\n");
}
