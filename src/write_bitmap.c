#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"
#include "Erdata.h" 

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */

extern double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2;
extern int W, H, a, b, c, d, w, h;

void write_bitmap(FILE *image_data_fp)
{
   int colour_Er1=-1, colour_Er2=-1, vector_aligned;
   unsigned char *image_data, *unaligned_image_vector;

   get_Er1_and_Er2_colours(&colour_Er1, &colour_Er2);
   W+=2*BORDER;
   H+=2*BORDER;
   /* We create an vector big enough for the image. Since rows are 
   aligned on 4-byte boundaries, we need to allow suffient space for
   (W+2)*(H-1) bytes. */

   /* when aligning data on 4-byte boundaries, the 
   padding must be filled with 0's, to meet the 
   .bmp standard */

   image_data=ustring(0,(W+3)*3*H);
   unaligned_image_vector=ustring(0,(W+3)*3*H);

   memset((void *) (image_data),0xff,W*H*3);

   /* Fill a vector with the initial (original) data on the 
   tline. This is not aligned in any way */
   /* The following function 'fill_image_vector_diwth_data' is *not* in the file
   fill_image_vector_eith_data.c, but instead different versions of it are 
   located in files fill_rect_with_rect.c, fill_circ_with_circ.c, 
   fill_rect_with_circ.c and fill_cirec_with_rect.c */
   fill_image_vector_with_data(unaligned_image_vector, colour_Er1, colour_Er2);
   
   /* put into the vector, in reverse order - i.e. from bottom to top and 
   align each row on 4-byte boundaries */
   vector_aligned=align_bitmap_image(W, H, unaligned_image_vector,image_data);
   write_bitmap_out(image_data, image_data_fp,vector_aligned, W, H);
}
