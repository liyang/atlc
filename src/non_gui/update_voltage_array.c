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

/*
The code below for calculating the voltage at a point i,j, given the
voltages and permittivities at the four adjacent points (i,j+1),
(i,j-1), (i-1,j), and (i+1,j), is I belive correct. However, it was
derrived by assuming 2 series  capacitors between each of the 4 centres
of the points and the point (i,j). The code is valid for any 
permittivity (I believe).

A document giving the proof may be found in the docs subdirecory, with
the name thoery.pdf

Here's the results from Mathematica, which was used to derrive the
equation for the new voltage v[i][j]

In[9]:= y=(eijm1*eij*(vijm1 - vij))/(eij + eijm1) 
+ (eijp1*eij*(vijp1 - vij))/(eij + eijp1) 
+ (eim1j*eij*(vim1j - vij))/(eij + eim1j) 
+ (eip1j*eij*(vip1j - vij))/(eij + eip1j)        

        eij eijm1 (-vij + vijm1)   eij eijp1 (-vij + vijp1)
Out[9]= ------------------------ + ------------------------ + 
              eij + eijm1                eij + eijp1
 
     eij eim1j (-vij + vim1j)   eij eip1j (-vij + vip1j)
>    ------------------------ + ------------------------
           eij + eim1j                eij + eip1j

In[10]:= Solve[y==0,vij]

Out[10]= {{vij -> 
 
         eij eijm1 vijm1   eij eijp1 vijp1   eij eim1j vim1j   eij eip1j vip1j
         --------------- + --------------- + --------------- + ---------------
           eij + eijm1       eij + eijp1       eij + eim1j      eij + eip1j
          
        ---------------------------------------------------------------------
                  eij eijm1      eij eijp1     eij eim1j     eij eip1j
                ----------- + ----------- + ----------- + -----------
                 eij + eijm1    eij + eijp1   eij + eim1j   eij + eip1j
 
*/
#include "definitions.h"

extern int width, height, **cell_type;
extern double r, **Er, **Vij;
void update_voltage_array(int i, int calculate_edges)
{
  int j, type;
  double a, b, c, d, e, f, g, h;
  for(j=1; j<height-1; ++j)
  {
    type = cell_type[i][j];
    if(type >=DIELECTRIC) /*only update dielectrics, not conductors*/
    {
      if(type == DIELECTRIC)
        Vij[i][j]=r*(Vij[i][j+1]+Vij[i+1][j]+Vij[i][j-1]+Vij[i-1][j])/4.0+(1-r)*Vij[i][j];
      //else  if (type == DIFFERENT_DIELECTRIC_NEARBY || type==METAL_NEARBY)
      else  
      {
        a=(Er[i][j] * Er[i][j-1] * Vij[i][j-1])/(Er[i][j] + Er[i][j-1]);
        b=(Er[i][j] * Er[i][j+1] * Vij[i][j+1])/(Er[i][j] + Er[i][j+1]);
        c=(Er[i][j] * Er[i-1][j] * Vij[i-1][j])/(Er[i][j] + Er[i-1][j]);
        d=(Er[i][j] * Er[i+1][j] * Vij[i+1][j])/(Er[i][j] + Er[i+1][j]);
     
        e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
        f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
        g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
        h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
        Vij[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*Vij[i][j];
      }
      /* the following few lines calculate the voltages at the edges.
      They are not accurate, but better than no calculation at all */

	  if (calculate_edges) {
		if(i==1 && cell_type[0][j]>=0)
		  Vij[0][j]=(Vij[0][j+1]+Vij[0][j-1])/2.0; //ok
		if(i==width-2 && cell_type[width-1][j] >= DIELECTRIC)
		  Vij[width-1][j]=(Vij[width-1][j+1]+Vij[width-1][j-1])/2.0;
	  } /* calculate_edges */

	  if(j==1 && cell_type[i][0]>=0)
		Vij[i][0]=(Vij[i][j-1]+Vij[i][j+1])/2.0;
	  if(j==height-2 && cell_type[i][height-1]>=DIELECTRIC)
		Vij[i][height-1]=(Vij[i][j-1]+Vij[i][j+1])/2.0;
    }
  }
}
