#include "definitions.h"

extern double **Vij;
extern int **cell_type;
extern double **Er;
extern int width, height;

double find_Ex(int i, int j) 
{
  double Ex;
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
  else
    Ey=0; /* for now */
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

