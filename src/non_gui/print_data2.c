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

#include "definitions.h"

/* The following simple function just prints data into a file, or if
fp-stout, to the screen. Depending on whether the dielectric is mixed or
not, it is or is not possible to quote a value for Er. If Er is passed
as a mumber < 0, this function interprets that as meaning that the
dielectric is mixed, and says 'Er= MIXED' */

int print_data2(FILE *fp, char *filename, struct tline_parameters *data, int which_Z)
{
  int a=1;
  if (data->conductors == 2)
  {
    if(data->Er < 0.0)
      fprintf(fp,"%s conductors= %d Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms v= %4g m/sv_f= %.4f PACKAGE_VERSION=%s\n",filename,data->conductors, data->C,data->L,data->Zo, data->v, data->v_f, PACKAGE_VERSION);
    else 
      fprintf(fp,"%s conductors= %d Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms v= %4g m/sv_f= %.4f PACKAGE_VERSION=%s\n",filename,data->conductors, data->Er, data->C,data->L,data->Zo, data->v, data->v_f,PACKAGE_VERSION);
  }
  else if (data->conductors > 2) /* couplers */
  {
    if(which_Z==Z_ODD && data->Er < 0.0)
    {
    }
    else if (which_Z == Z_ODD && data->Er < 0.0)
    {
    }
    else if (which_Z == Z_EVEN && data->Er < 0.0)
    {
    }
    else if (which_Z == Z_EVEN && data->Er < 0.0)
    {
    }
  }
  return(a);
}
