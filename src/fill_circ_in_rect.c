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

extern int d, W, H, x, y;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2) 
{
   int i, j, red, green, blue, vector_original=0;
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
	 if( (i<BORDER) || (i>=W-BORDER) || (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
         else if( pow((double)i-(double)W/2.0-(double) x,2.0) + pow((double)j-(double)H/2.0-(double)y,2.0)<=((double)d*(double)d)/4.0)
	 {
	    red=0xff;
	    green=0x0;
	    blue=0x0;
         }
	 else
	 {
	    red=colour_Er1/(256*256); /* Fill in areas with Er1 */
	    green=colour_Er1/256;
	    blue=colour_Er1%256;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
