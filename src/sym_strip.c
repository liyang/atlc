/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

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

/* The programme widestrip is a pre-processor for atlc. It produces bitmaps 
of a thin strip, between two wide plates */
#define RATIO 4           /* W = H*RATIO+w */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_STRING_H
#include <string.h>
#endif  
#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int verbose=FALSE;

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
  int W, H, w, size_of_image;
  double Zo;
  unsigned char *unaligned_image_vector, *aligned_image_vector;
  FILE *fp;

  if(argc-my_optind !=4)
  {
    usage_symmetrical_strip();    
    exit(1);
  }
  W=atoi(argv[1]);
  H=atoi(argv[2])+2*BORDER;
  if(H%2==0) /* make it odd, so that the inner can sit in the middle */
  {
    H++;
    printf("H needs to be odd, so the inner conductor (1 pixel high) will fit\
    centrally. Hence H has been increased to %d pixels\n",H);
  }
  w=atoi(argv[3]);
  if(H <= 200)
  {
    fprintf(stderr,"To be accurate, make H at least 201 pixels\n");
    exit(1);
  }
  if (W < RATIO*H + w)
  {
    fprintf(stderr,"For this to be a valid test, W must exceed w + %dxH\n",RATIO);
    fprintf(stderr,"Therefore W has been is set to %d\n",RATIO*H+w );
    W=RATIO*H+w;
  }
  aligned_image_vector=ustring(0,(W+3)*3*H+100);
  unaligned_image_vector=ustring(0,(W+3)*3*H+100);

  if((fp=fopen(argv[4],"w")) == NULL)
  {
    fprintf(stderr,"Error in opening file in sym_strip\n");
    exit(1);
  }
  aligned_image_vector=ustring(0,(W+3)*3*H);
  unaligned_image_vector=ustring(0,(W+3)*3*H);
  memset((void *) (aligned_image_vector),0xff,W*H*3);

  /* Fill a vector with */
  fill_image_vector_for_thin_strip(W,H,w,unaligned_image_vector);
  size_of_image=align_bitmap_image(W, H, unaligned_image_vector,aligned_image_vector);

  write_bitmap_out(aligned_image_vector, fp, size_of_image, W, H);
  /* write_bitmap_out closes the file pointer */
  Zo=calculate_thin_strip_impedance(H-2*BORDER,w);
  printf("Zo is theoretically %f Ohms (assuming W is infinite)\n",Zo);
  exit(0);
}
