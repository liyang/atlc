#include "definitions.h"

extern double **Vij, **Er;
extern int **cell_type, dielectrics_to_consider_just_now;
extern double r;
extern int width, height;

double find_energy_per_metre(int w, int h)
{
  double energy_per_metre=0;
  double Ex, Ey;

  if(cell_type[w][h] >= 0)
  {
    Ex=find_Ex(w,h);
    Ey=find_Ey(w,h);
    energy_per_metre+=0.5*EPSILON_0*(Ex*Ex+Ey*Ey);
    if(cell_type[w][h] >= 0 && dielectrics_to_consider_just_now>1)
      energy_per_metre*=Er[w][h];
  }
  else
   energy_per_metre=0.0;

  return(energy_per_metre);
}
