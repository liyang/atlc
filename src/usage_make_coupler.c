#ifdef HAVE_STDLIB_H
#include <stdlib.h>  
#endif

#include "definitions.h"

void usage_make_coupler(void)
{
  fprintf(stderr,"Usage: make_coupler [-v] [-b bitmapsize] H w s \n\n");
  fprintf(stderr,"make_coupler produces a bitmap for the following coupled lines\n");
  fprintf(stderr,"------------^------------------------------------------------------------------\n");
  fprintf(stderr,"            |                                               \n");
  fprintf(stderr,"            |              <---w---><-----s----><---w-->\n");
  fprintf(stderr,"            H              ---------            --------\n");
  fprintf(stderr,"            |                                      \n");
  fprintf(stderr,"            |   Er=1.0                      \n");
  fprintf(stderr,"------------v------------------------------------------------------------------\n");
  fprintf(stderr,"and calculates the theoretical impedances if the -v option is given\n");
  fprintf(stderr,"e.g. make_coupler  1.23 0.7 1.2 1.   coupler.bmp (standard bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -b 23 1.23 0.7 1.2  large.bmp  (large bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -b 2 1.23 0.7 1.2  small.bmp   (small bitmap produced)\n");
  fprintf(stderr,"e.g. make_coupler -v 2 1.23 0.7 1.2  theory.bmp  (prints theoretical values too)\n");
  fprintf(stderr,"\nThe default bitmap size b is %d. File sizes will be between 2^(b-1) and 2^(b+1)\n",DEFAULT_COUPLER_BITMAP_SIZE);
}
