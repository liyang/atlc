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

/* The function 'setup_arrays sets the cell_type[i][j] to be DIELECTRIC
if the material is non-metal. This function expands on that, checking if
the adjactent cells are dielectrics, or metals, and if dielectric,
whether or nor there is a boundary vertically, or horizontally between
two different dielectrics. Doing this once, is much faster than doing it
inside a loop, checking for all possibilities each time one needs to
know. */

#include "config.h"


#include "definitions.h"

extern int width, height;
extern signed char **cell_type;
extern double **Er;

void check_for_boundaries(void) 
{
  int i, j;
  for(j=0;j<=height-1;++j)
  {
    for(i=0;i<=width-1; ++i)
    {  
      if(cell_type[i][j]==DIELECTRIC)
      {
	if( i > 0) 
	{
	  if (Er[i-1][j]== METAL_ER) 
	    cell_type[i][j]+=METAL_LEFT;
        }
	if(i<width-1) /*if i==width-1, there can't be metal at right */
	{
	  if(Er[i+1][j]==METAL_ER)
	    cell_type[i][j]+=METAL_RIGHT;
        }
	if( j > 0)
	{
	  if(Er[i][j+1]==METAL_ER)
	    cell_type[i][j]+=METAL_BELOW;
        }
	if( (j < height-1) && (j > 0))
	{
	  if(Er[i][j-1]==METAL_ER)
	    cell_type[i][j]+=METAL_ABOVE;
        }
      }/* end of if dielectric */
    }/* end of for w=0 to width-1 */
  }
}

