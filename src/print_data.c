/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

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

int print_data(FILE *fp, char *filename, double Er, double C,\
double L, double Zo, double Zodd, double Zeven, int whichZ, double v, double vf)
{
  int a=1;
  if(Er<0.0)
  {
    if(whichZ==Z0)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= N/A Ohms Zeven= N/A Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zo, v,vf,VERSION);
    else if(whichZ==Z_ODD)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= N/A Ohms Zodd= %.4f Ohms Zeven= N/A Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zodd, v,vf,VERSION);
    else if(whichZ==Z_ALL)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= %.4f Ohms Zeven= %.4f Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zo, Zodd,Zeven,v,vf,VERSION);
  }
  else
  {
    if(whichZ==Z0)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= N/A Ohms Zeven= N/A Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zo, v,vf,VERSION);
    else if(whichZ==Z_ODD)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= N/A Ohms Zodd= %.4f Ohms Zeven= N/A Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zodd, v,vf,VERSION);
    else if(whichZ==Z_ALL)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= %.4f Ohms Zeven= %.4f Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zo, Zodd, Zeven, v,vf,VERSION);

  }
  return(a);
}
