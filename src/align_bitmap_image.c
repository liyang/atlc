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

/* a vector of length W*H called 'unaligned_image' contains the data. 
This is written to a vector 'byte_aligned_image', which in general is longer
and is of length 'vector_aligned. This routine returns the lenght of the image, 
once it have been byte-aligned 

The image 'unaligned_image' is expected to have the top of the image at the top of the
file. This routine puts the image, so the bottom of the image is at the beggining of the 
vector 'byte_aligned_image' 
*/

int align_bitmap_image(int W,int H,unsigned char *unaligned_image,unsigned char *byte_aligned_image)
{
   int i, j, vector_aligned=0, vector_original=0;
   /* put into the vector, in reverse order - i.e. from bottom to top */
   for(j=0;j<H;j++)
   {
      for(i=0;i <W; ++i)
      {
	 /* vector_aligned is the offset into the image that's padded
	 to allow 4-byte alignment */
	 /* offset is not, and so will allways be <=vector_offset */
	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++;
	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++;
	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++; 
	 byte_aligned_image[vector_aligned]=unaligned_image[vector_original];
	 byte_aligned_image[vector_aligned+1]=unaligned_image[vector_original+1];
	 byte_aligned_image[vector_aligned+2]=unaligned_image[vector_original+2];
         vector_original+=3;
         vector_aligned+=3;
      }
   }
   if( vector_aligned%4!=0 )
      vector_aligned++;
   if( vector_aligned%4!=0 )
      vector_aligned++;
   if( vector_aligned%4!=0 )
      vector_aligned++;
   return(vector_aligned);
}
