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

extern int width, height;
extern double **Vij, **Er;
extern signed char **cell_type;

double check_convergence(double **grid1, double **grid2, int width, int height)
{
  double maxdiff = 0.0, temp;
  int i,j;
  for (i = 0; i <width; i++) {
    for (j = 0; j <height; j++) {
    temp = grid1[i][j]-grid2[i][j];
    if (temp < 0)
      temp = -temp;
    if (maxdiff < temp)
    maxdiff = temp;
    }
  }
  return(maxdiff);
}
