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

extern int D, w, h, x, y;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2) 
{
   int i, j, red, green, blue, vector_original=0;
   for(j=0;j<D;++j)
   {
      for(i=0;i<D; ++i)
      {
	 red=colour_Er1/(256*256); /* Fill in areas with Er1 */
	 green=colour_Er1/256;
	 blue=colour_Er1%256;

	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */
         if( pow((double)i-(double)D/2.0-(double)BORDER,2.0) +
	 pow((double)j-(double)D/2.0-(double)BORDER,2.0)>=((double)D*(double)D)/4.)
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
	 /* Fill in the inner conductor */
	 else if(j==D/2)
	 {
         }
	 else /* fill in areas of Er1 */
	 {
	    red=colour_Er2/(256*256); /* fill in areas with Er2 */
	    green=colour_Er2/256;
	    blue=colour_Er2%256;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
