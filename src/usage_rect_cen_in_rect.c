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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>    
#endif

#include "definitions.h"

void usage_rect_cen_in_rect(void)
{
      fprintf(stderr,"Usage: rect_cen_in_rect [-b bmp_size] [-f outfile] [-v] W H w h Er1\n\n");
      fprintf(stderr,"where W, H, w, and h  are all in mm or all in inches\n");      
      fprintf(stderr,"(they *must* use the same units. Non-integers allowed for all parameters)\n");
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMPSIZE);
      fprintf(stderr,"  -f outfile \n     Write output to 'outfile' instead of stdout\n");
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n");
      fprintf(stderr,"-----------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                   |  |\n");
      fprintf(stderr,"|     Er1     <----------w----------->              |  |\n");
      fprintf(stderr,"|             ------------------------   ^          |  |\n");
      fprintf(stderr,"|             |                      |   |          |  |\n");
      fprintf(stderr,"|             |  Metallic conductor  |   |          |  H\n");
      fprintf(stderr,"|             |  conductor (centred  |   h          |  |\n");
      fprintf(stderr,"|             |  vertically and      |   |          |  |\n");
      fprintf(stderr,"|             |  horizontally)       |   |          |  |\n");
      fprintf(stderr,"|             ------------------------              |  |\n");
      fprintf(stderr,"|                                                   |  |\n");
      fprintf(stderr,"-----------------------------------------------------  |\n");
      fprintf(stderr,"<-------------------------W------------------------->\n\n");
      fprintf(stderr,"***WARNING*** Since the output from rect_cen_in_rect is binary data (the bitmap) it\n");
      fprintf(stderr,"will screw up your terminal unless you redirect the ouptut to a file.\n");
      fprintf(stderr,"The '-f' option can be used to send the output to 'outfile' \n");
      fprintf(stderr,"or you can use rect_cen_in_rect W H w h Er1 > filename.bmp \n");

      exit(8); /* Exit - program called with wrong number of arguments */
}
