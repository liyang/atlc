#ifdef HAVE_STDLIB_H
#include <stdlib.h>   
#endif

#include "definitions.h"

void usage_rect_in_rect(void)
{
      fprintf(stderr,"Usage: rect_in_rect [-b bmp_size] [-f outfile] [-v] W H a b c d w h Er1 Er2 \n\n");
      fprintf(stderr,"where W, H, a, b, c, d, w, and h  are all in mm or all in inches\n");      
      fprintf(stderr,"(they *must* use the same units. Non-integers allowed for all parameters)\n");
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMPSIZE);
      fprintf(stderr,"  -f outfile \n     Write output to 'outfile' instead of stdout\n");
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n");
      fprintf(stderr,"-----------------------------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|               Dielectric, permittivity=Er1                          |  |\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|       <----------------d------------------------->                  |  |\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|             <----------w----------->                                |  |\n");
      fprintf(stderr,"|             ------------------------   ^                            |  |\n");
      fprintf(stderr,"|             |                      |   |                            |  |\n");
      fprintf(stderr,"|             |  Metallic conductor  |   |                            |  H\n");
      fprintf(stderr,"|<-----b----->|  conductor (can be   |   c                            |  |\n");
      fprintf(stderr,"|             |  off-centre)         |   |                            |  |\n");
      fprintf(stderr,"|             |                      |   |                            |  |\n");
      fprintf(stderr,"|       |------------------------------------------- ^                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"|       |.....Dielectric, permittivity=Er2.........| |                |  |\n");
      fprintf(stderr,"|<--a-->|.......(can be off centre )...............| h                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"-----------------------------------------------------------------------  |\n");
      fprintf(stderr,"<----------------------------------W--------------------------------->\n\n");
      fprintf(stderr,"***WARNING*** Since the output from rect_in_rect is binary data (the bitmap) it\n");
      fprintf(stderr,"will screw up your terminal unless you redirect the output to a file.\n");
      fprintf(stderr,"The '-f' option can be used to send the output to 'outfile' \n");
      fprintf(stderr,"or you can use rect_in_rect W H a b c d w h Er1 Er2 > filename.bmp \n");

      exit(8); /* Exit - program called with wrong number of arguments */
}
