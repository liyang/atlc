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

extern double **Vij;
extern signed char **cell_type;
extern double **Er;
extern int width, height, coupler;

/*
Note, a bitmap has the following pixel nomecture.


(0,0)                  (width-1,0)

(0,height-1)           (width-1, height-1)
*/

#define USE_OLD_FORMULAS

#ifdef USE_OLD_FORMULAS

double find_Ex(int i, int j) 
{
  double Ex;
  if(cell_type[i][j]>=0 && i > 0 && i < width-1)
  {
    Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);
    if((cell_type[i][j]&METAL_LEFT)==METAL_LEFT)
      Ex=(Vij[i][j]-Vij[i+1][j]);

    if((cell_type[i][j]&METAL_RIGHT)==METAL_RIGHT)
    {
      /* The following should cause a problem if i == 0 */
      if (i == 0)
        fprintf(stderr,"This is an error - memory access violation.\n");
      Ex=(Vij[i-1][j]-Vij[i][j]);
    }
  }
  else
   Ex=0; /* for now */
  return(Ex);
}

double find_Ey(int i, int j)
{
  double Ey;
  if(cell_type[i][j]>=0 && j > 0 && j< height-1)
  {
    Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);
    if((cell_type[i][j]&METAL_ABOVE)==METAL_ABOVE)
      Ey=(Vij[i][j+1]-Vij[i][j]);
    if((cell_type[i][j]&METAL_BELOW)==METAL_BELOW)
      Ey=(Vij[i][j]-Vij[i][j-1]);
  }
  else
    Ey=0; /* for now */
  return(Ey);
}

#endif

#ifdef USE_NEW_FORMULAS_A

double find_Ex(int i, int j) 
{
  double Ex;
  if(i < 0 || i > width-1 || j < 0 || j > height-1)

  if(cell_type[i][j]>=0)
  {
    if(i>0 && i <width-1)
      Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);
    else
      Ex=0; /* for now */
    if((cell_type[i][j]&METAL_LEFT)==METAL_LEFT)
      Ex=(Vij[i][j]-Vij[i+1][j]);
    if((cell_type[i][j]&METAL_RIGHT)==METAL_RIGHT)
      Ex=(Vij[i-1][j]-Vij[i][j]);
  }
  else if (cell_type[i][j] == CONDUCTOR_MINUS_ONE_V && Vij[i][j] != -1.0 && coupler ==FALSE)
  {
    fprintf(stderr,"in find_Ex celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be -1 volts", VOLTAGE_NOT_MINUS_ONE_V_AS_EXPECTED);
  }
  else if (cell_type[i][j] == CONDUCTOR_PLUS_ONE_V && Vij[i][j] != 1.0)
  {
    fprintf(stderr,"in find_Ex  celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be 1 volts", VOLTAGE_NOT_PLUS_ONE_V_AS_EXPECTED);
  }
  else if (cell_type[i][j] == CONDUCTOR_ZERO_V && Vij[i][j] != 0.0)
  {
    fprintf(stderr,"in find_Ex celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be 1 volts", VOLTAGE_NOT_ZERO_V_AS_EXPECTED);
  }
  else
    Ex=0; /* for now */
  return(Ex);
}

double find_Ey(int i, int j)
{
  double Ey;
  if(cell_type[i][j]>=0)
  {
    if(j > 0 && j < height-2)
      Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);
    else
      Ey=0; /* for now */
    if((cell_type[i][j]&METAL_ABOVE)==METAL_ABOVE)
      Ey=(Vij[i][j+1]-Vij[i][j]);
    if((cell_type[i][j]&METAL_BELOW)==METAL_BELOW)
      Ey=(Vij[i][j]-Vij[i][j-1]);
  }
  else if (cell_type[i][j] == CONDUCTOR_MINUS_ONE_V && Vij[i][j] != -1.0 && coupler == FALSE)
  {
    fprintf(stderr,"in find_Ey  celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be -1 volts", VOLTAGE_NOT_MINUS_ONE_V_AS_EXPECTED);
  }
  else if (cell_type[i][j] == CONDUCTOR_PLUS_ONE_V && Vij[i][j] != 1.0 )
  {
    fprintf(stderr,"in find_Ey celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be 1 volts", VOLTAGE_NOT_PLUS_ONE_V_AS_EXPECTED);
  }
  else if (cell_type[i][j] == CONDUCTOR_ZERO_V && Vij[i][j] != 0.0 )
  {
    fprintf(stderr,"in find_Ey celltype[%d][%d] =%d V[%d][%d]=%f\n", i,j,cell_type[i][j],i,j,Vij[i][j]);
    exit_with_msg_and_exit_code("should be 0 volts", VOLTAGE_NOT_ZERO_V_AS_EXPECTED);
  }
  else
    Ey=0; /* for now */
  return(Ey);
}

#endif

#ifdef USE_NEW_FORMULAS_B
double find_Ex(int i, int j) 
{
  /* Ex = -dV/dx by definition, so is left - right */
  double Ex;

  if( i==0 )                                           /* Far left of image  */
      Ex=Vij[0][j]-Vij[1][j];

  else if( i == width-1 )                              /* Far right of image */
      Ex=Vij[width-2][j]-Vij[width-1][j];

  else                                                 /* Not on edges */
    Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);

  return(Ex);
}

double find_Ey(int i, int j) 
{
  /* Ey = -dV/dy by definition, so is bottom - top  (big j - little j ) */
  double Ey;

  if( j==0 )                                           /* Top of image */ 
      Ey=Vij[i][1]-Vij[i][0];

  else if ( j==height-1 )                              /* Bottom of image */
      Ey=Vij[i][height-1]-Vij[i][height-2];

  else                                                 /* Not near edges */
    Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);

  return(Ey);
}
#endif

double find_E(int w, int h)
{
  double Ex, Ey, E;
  Ex=find_Ex(w,h);
  Ey=find_Ey(w,h);
  E=sqrt(Ex*Ex+Ey*Ey);
  return(E);
}

