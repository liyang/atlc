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

#ifndef ENABLE_POSIX_THREADS

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern int width, height;
extern double **Vij, **Er;
extern char **cell_type;
extern int dielectrics_to_consider_just_now;
extern double r; 

extern int coupler;

double finite_difference(int number_of_iterations)
{
  int i, j, iteration;
  double capacitance_per_metre, energy_per_metre;

  /* The following might not look very neat, with a whole load of code being 
  written twice, when it would be posible to make it easier to read if the 
  'if(dielectrics_in_bitmap > 1)' was in an inner loop. However, the 
  following is almost certainly more efficient. It is not a good idea to 
  have any more than necessary in the inner loop. 

  The option to avoid the faster convergence algorithm has been didtched
  too, as this was in an inner loop. The faster covergence method seems
  to work fine, so there is no need to avoid using it */

  for(iteration=1; iteration<=number_of_iterations; ++iteration)
  {
    for(i=1; i<width-1; ++i)
    {
      update_voltage_array(i,1); /* finds new v[i][j] for all j's */
    }  
  }
  /* Once the voltage distribution is found, the energy in the field may be 
  found. This can be shown to be Energy = 0.5 * integral(E.D) dV, when 
  integrated over a volume V, and D.E is the vector dot product of E and
  D. 
  
  Energy per metre is 0.5 * D.E or (0.5*Epsilon)* E.E. Now E.E is given
  by Ex^2 + Ey^2 (by definition of a dot product. */

  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
    { 
      energy_per_metre+=find_energy_per_metre(i,j);
    }
  /* The capacitance C is relatated to the energy (U) by Energy=0.5*C*V^2 
  so C=2*U/(V^2). When there is a coupler, V is 2 V, not one, so the
  capciance C=0.5*U; */
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
#endif
