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

void usage_circ_in_rect(void)
{
      fprintf(stderr,"Usage: circ_in_rect [-b bmp_size] [-f outfile] [-v] d W H x y Er\n\n");
      fprintf(stderr,"Where \n");
      fprintf(stderr,"  d  is the outside diameter of the inner conductor\n");
      fprintf(stderr,"  W  is the horizontal internal dimension of the outer conductor\n");
      fprintf(stderr,"  H  is the vertical internal dimension of the outer conductor\n");
      fprintf(stderr,"  x  is the horizontal offset between the centre of the inner and outer conductors \n");
      fprintf(stderr,"  y  is the vertical offset between the centre of the inner and outer conductors \n");
      fprintf(stderr,"  Er is the relative permettivity of the dielectric.\n");
      fprintf(stderr,"  d, W, H, x and y are either all in mm or all in inches (but not a mixture!!)\n\n");   
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMPSIZE);
      fprintf(stderr,"  -f outfile \n     Write output to 'outfile' instead of stdout\n");
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n\n");
      fprintf(stderr," --------------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|           Dielectric, permittivity=Er                |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|         <------x------> ^                            |  H\n");
      fprintf(stderr,"|       *****             |                            |  |\n");
      fprintf(stderr,"|    ***********          y                            |  |\n");
      fprintf(stderr,"|   *************         |                            |  |\n");
      fprintf(stderr,"|   **************        |                            |  |\n");
      fprintf(stderr,"|   <-----d------>        v                            |  |\n");
      fprintf(stderr,"|   **************                                     |  |\n");
      fprintf(stderr,"|   *************                                      |  |\n");
      fprintf(stderr,"|    ***********                                       |  |\n");
      fprintf(stderr,"|        ***                                           |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"-------------------------------------------------------   v\n");
      fprintf(stderr,"<---------------------------W-------------------------->\n");
      fprintf(stderr,"                                     ***\n\n");
      fprintf(stderr,"***WARNING*** Since the output from circ_in_rect is binary data (the bitmap) it\n");
      fprintf(stderr,"will screw up your terminal unless you redirect the ouptut to a file.\n");
      fprintf(stderr,"The '-f' option can be used to send the output to 'outfile' \n");
      fprintf(stderr,"or you can use circ_in_rect d W H x y Er > filename.bmp \n");
      exit(8); /* Exit - program called with wrong number of arguments */
}
