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


#include "config.h"
#include "definitions.h"
#include "exit_codes.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

extern double **Vij;
extern signed char **oddity;
extern double **Er;
extern int width, height, coupler;

/*
Note, a bitmap has the following pixel nomecture.


(0,0)                  (width-1,0)

(0,height-1)           (width-1, height-1)
*/


double find_Ex(int i, int j) 
{
  /* Ex = -dV/dx by definition, so is left - right */
  double Ex;

  if(oddity[i][j]>=0)
  {
    if(i>0 && i <width-1)
      Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);
    else if ( i == 0)
      Ex=(Vij[i][j]-Vij[i+1][j]);
    else if ( i == width-1)
      Ex=(Vij[i-1][j]-Vij[i][j]);
    else{
      fprintf(stderr, "this should not happen XXXXXXX #1\n");
      exit(1);
    }      
  }
  else
    Ex=0; /* Metal, so Ex=0 */
  return(Ex);
}

double find_Ey(int i, int j)
{
  /* Ey = -dV/dy by definition, so is bottom -  top  */
  double Ey;
  if(oddity[i][j]>=0)
  {
    if(j > 0 && j < height-1)
      Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);
    else if ( j == 0)
      Ey=Vij[i][j+1]-Vij[i][j];
    else if ( j == height-1)
      Ey=Vij[i][j]-Vij[i][j-1];
    else{
      fprintf(stderr, "this should not happen #2 XXXXXXXX\n");
      exit(1);
    }      
  }
  else
    Ey=0; /* Metal so Ey=0 */
  return(Ey);
}

double find_E(int w, int h)
{
  double Ex, Ey, E;
  Ex=find_Ex(w,h);
  Ey=find_Ey(w,h);
  E=sqrt(Ex*Ex+Ey*Ey);
  return(E);
}

