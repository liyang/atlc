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

Dr. David Kirkby, e-mail drkirkby at ntlworld.com 

*/

/* The function setup_arrays sets the type of a pixel to be dielectric, 
or metal. This routines refines that, setting the type of a pixel to be
some number between 1 and 28 according to where it is located, and what 
is around it. See Green paper to understand what they mean */

#include "config.h"
#include "definitions.h"

extern int width, height;
extern signed char **oddity;
extern signed char **cell_type;
extern double **Er;

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

void set_oddity_from_Greens_paper(void) 
{
  int i, j, odd;
  for(i=0;i<width; ++i)
  {
    for(j=0;j<height;++j)
    {  
      /* If the oddity value is a fixed voltage, then let it 
      remain as such */

      odd=oddity[i][j]; 

      oddity[i][j]=ORDINARY_INTERIOR_POINT; 
      if(cell_type[i][j] == CONDUCTOR_ZERO_V )
        oddity[i][j] = CONDUCTOR_ZERO_V;

      else if(cell_type[i][j]== CONDUCTOR_PLUS_ONE_V)
        oddity[i][j] = CONDUCTOR_PLUS_ONE_V;

      else if(cell_type[i][j]== CONDUCTOR_MINUS_ONE_V )
        oddity[i][j] = CONDUCTOR_MINUS_ONE_V; 

#ifdef FULL

      /* Fill in the edges */

      else if ( j == height-1 ) /* 2 */
	oddity[i][j]=ORDINARY_POINT_BOTTOM_EDGE;

      else if ( j == 0 ) /* 3 */
	oddity[i][j]=ORDINARY_POINT_TOP_EDGE;

      else if ( i == 0 ) /* 4 */
	oddity[i][j]=ORDINARY_POINT_LEFT_HAND_EDGE;

      else if ( i == width-1 ) /* 5 */
	oddity[i][j]=ORDINARY_POINT_RIGHT_HAND_EDGE;


      /* fill in the corners, overwriting the edges */

      if( i == 0 && j ==  height-1  ) /* case  6 */
	oddity[i][j]=CORNER_POINT_BOTTOM_LEFT_HAND_EDGE;

      else if ( i == width-1 && j == height-1  ) /* case  7 */
	oddity[i][j]=CORNER_POINT_BOTTOM_RIGHT_HAND_EDGE;
     
      else if( i == 0 && j == 0 ) /* case  8 */
	oddity[i][j]=CORNER_POINT_TOP_LEFT_HAND_EDGE;

      else if( i == width-1 && j == 0 ) /* case  9 */
	oddity[i][j]=CORNER_POINT_TOP_RIGHT_HAND_EDGE;



      /* Fill in any regions where a conductor (?) meets a dielectric */

      
      if ( i > 0 && i <width-1 && j > 0 && j < height-1 && \
      cell_type[i-1][j] < 0 && cell_type[i][j-1] < 0 && cell_type[i+1][j-1] < 0 && \
      cell_type[i-1][j-1] >= 0 && cell_type[i][j-1] >= 0 && cell_type[i+1][j-1] >= 0) {
	printf("dielectric to top %d %d\n",i,j);
	oddity[i][j]=DIELECTRIC_ROW_INTERFACE_DIELECTRIC_TO_TOP; /* case 10 */
      }

      else if ( i > 0 && i <width-1 && j > 0 && j < height-1 && \
      cell_type[i-1][j] < 0 && cell_type[i][j] < 0 && cell_type[i+1][j] <  0 && \
      cell_type[i][j+1] >= 0 ) {
	printf("dielectric to top %d %d\n",i,j);
	oddity[i][j]=DIELECTRIC_ROW_INTERFACE_DIELECTRIC_TO_BOTTOM; /* case 11 */
      }

#endif
      else if ( i > 0 && i <width-1 && j > 0 && j < height-1 )
	 oddity[i][j]=ORDINARY_INTERIOR_POINT;



    }/* end of for i=0 to width-1 */
  } /* end of for j= 0 to height-1 */
}

