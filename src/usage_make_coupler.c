#ifdef HAVE_STDLIB_H
#include <stdlib.h>  
#endif

#include "definitions.h"

void usage_make_coupler(void)
{
  fprintf(stderr,"Usage: make_coupler [-b bitmapsize] H w s Er\n\n");
  fprintf(stderr,"make_coupler produces a bitmap for the following coupled lines\n");
  fprintf(stderr,"------------^------------------------------------------------------------------\n");
  fprintf(stderr,"            |                                               \n");
  fprintf(stderr,"            |              <---w---><-----s----><---w-->\n");
  fprintf(stderr,"            H              ---------            --------\n");
  fprintf(stderr,"            |                                      \n");
  fprintf(stderr,"            |                               \n");
  fprintf(stderr,"------------v------------------------------------------------------------------\n");
  fprintf(stderr,"and calculates the theoretical impedances. The bitmap can be ommited if\n");
  fprintf(stderr,"you only want the theoretical impedances by using the -b 0 option.\n\n");
  fprintf(stderr,"e.g. make_coupler 1.23 0.7 1.2 1.0      coupler.bmp (standard bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -b 0 1.23 0.7 1.2 1.0              (no bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -b 9 1.23 0.7 1.2 1.0 large.bmp    (large bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -b 2 1.23 0.7 1.2 1.0 small.bmp    (small bitmap produced)\n");

}
