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

extern int W, H, a, b, c, d, w, h;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2) 
{
   int i, j, red, green, blue, vector_original=0;
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
	 red=colour_Er1/(256*256); /* Fill in areas with Er1 */
	 green=colour_Er1/256;
	 blue=colour_Er1%256;

	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */

         if( (i<BORDER) || (i>=W-BORDER) || (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
	 /* Fill in the dielectric */
	 if( (i>=a+BORDER) && (i<a+d+BORDER) && (j<h+BORDER) && (j>=BORDER)) 
	 {
	    red=colour_Er2/(256*256); /* fill in areas with Er2 */
	    green=colour_Er2/256;
	    blue=colour_Er2%256;
         }
	 if( (i>=b+BORDER) && (i<b+w+BORDER) && (j<h+c+BORDER) && (j>=h+BORDER)) /* conductor */
	 {
	    red=0xff;
	    green=0x00;
	    blue=0x00;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
