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
#include "config.h"
#include "definitions.h"

extern double **Vij, **Er;
extern signed char **cell_type;
extern int dielectrics_to_consider_just_now;
extern double r;
extern int width, height;

double find_energy_per_metre(int w, int h)
{
  double energy_per_metre=0;
  double Ex, Ey;

  if(cell_type[w][h] >= 0 )
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
