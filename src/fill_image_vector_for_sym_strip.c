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

void fill_image_vector_for_thin_strip(int W,int H, int w, unsigned char *image_vector) 
{
   int i, j, red, green, blue, vector_original=0;
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */

         if( (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
	 /* Fill in the dielectric */
	 else if( (j==H/2)  && (i > (W-w)/2) && (i < (W+w)/2)) 
	 {
	    red=0xff; 
	    green=0x00; 
	    blue=0x00; 
         }
	 else
	 {
	    red=0xff; 
	    green=0xff; 
	    blue=0xff; 
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
