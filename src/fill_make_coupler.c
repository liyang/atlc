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

extern int W, H, w,  s, verbose;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2) 
{
   int i, j, red, green, blue, vector_original=0;
   int left_edge_blue;
   int left_edge_red;
   left_edge_red=W/2 - w -s/2;
   left_edge_blue=(W+s)/2;
   if(verbose)
     printf("\nw=%d s=%d W=%d H=%d\n", w, s, W, H);
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
         red=0xff; green=0xff; blue=0xff;
	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */

         if( (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
	 if( (i>=left_edge_blue) && (i<left_edge_blue+w) && j==(H/2)) /* conductor */
	 {
	    red=0x00;
	    green=0x00;
	    blue=0xff;
         }
	 if( (i>=left_edge_red) && (i<left_edge_red+w) && j==(H/2)) /* conductor */
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
