/* The function 'setup_arrays sets the cell_type[i][j] to be DIELECTRIC
if the material is non-metal. This function expands on that, checking if
the adjactent cells are dielectrics, or metals, and if dielectric,
whether or nor there is a boundary vertically, or horizontally between
two different dielectrics. Doing this once, is much faster than doing it
inside a loop, checking for all possibilities each time one needs to
know. */

#include "definitions.h"

extern int width, height, **cell_type;
extern double **Er;

void check_for_boundaries(void) 
{
  int i, j, type;
  double ER;
  for(j=0;j<=height-1;++j)
  {
    for(i=0;i<=width-1; ++i)
    {  
      ER=Er[i][j];
      if(cell_type[i][j]==DIELECTRIC)
      {
	type=cell_type[i][j];
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
	if( j < height-1)
	{
	  if(Er[i][j-1]==METAL_ER)
	    cell_type[i][j]+=METAL_ABOVE;
        }
	/*
	if( Er_l!=ER || Er_r!=ER || Er_a !=ER || Er_b != ER)
	{
	  Er[i][j]+=DIFFERENT_DIELECTRIC_NEARBY;
        }
	*/
      }/* end of if dielectric */
    }/* end of for w=0 to width-1 */
  }
}

