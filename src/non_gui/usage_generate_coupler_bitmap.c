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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>  
#endif

#include "definitions.h"

void usage_generate_coupler_bitmap(void)
{
  fprintf(stderr,"Usage: generate_coupler_bitmap [-C] [-b bitmapsize] H w s Er filename\n\n");
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"         -C\n");
  fprintf(stderr,"            Print copyright, licencing and distribution information\n");
  fprintf(stderr,"         -b  bitmapsize\n");
  fprintf(stderr,"            Set the size of the bitmap to about 2^bitmapsize bytes\n");
  fprintf(stderr,"         -v\n");
  fprintf(stderr,"            Print a little extra information on goodness of fit\n");
  fprintf(stderr,"------------^------------------------------------------------------------------\n");
  fprintf(stderr,"            |                                               \n");
  fprintf(stderr,"            |              <---w---><-----s----><---w-->\n");
  fprintf(stderr,"            H              ---------            --------\n");
  fprintf(stderr,"            |                                      \n");
  fprintf(stderr,"            |   Er                          \n");
  fprintf(stderr,"------------v------------------------------------------------------------------\n");
  fprintf(stderr,"e.g. generate_coupler_bitmap  1.23 0.7 1.2 1   coupler.bmp\n");
  fprintf(stderr,"e.g. generate_coupler_bitmap -b 8 1.23 0.7 1   small.bmp\n");
  fprintf(stderr,"e.g. generate_coupler_bitmap -v 12 1.23 0.7 1   theory.bmp\n");
  fprintf(stderr,"\nThe default bitmap_bitmap size b is %d. Files will be between 2^(b-1)\n", DEFAULT_COUPLER_BITMAP_SIZE);
  fprintf(stderr,"and 2^(b+1) bytes in length\n");
}
