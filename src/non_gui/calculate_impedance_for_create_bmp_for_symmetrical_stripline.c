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

/* This routine calaculates the impedance exaclty for the case of two
infinity wide conductors sepparated a distance H, with between them
placed centrally a conductor of width w and infinitely thin. 

i.e.
******^***********************************************************************
      |
      |
      H                    ----------w----------
      |
      |
******Vij***********************************************************************

It uses the method given in "Filed Theory of Guided Waves, Colen R.E.,
2nd edition, pp 259-273, IEEE Press, (1990). */

#include "definitions.h"

double calculate_thin_strip_impedance(int H, int w)
{
  double Zo=-1;
  double mu=4*M_PI*1e-7, x0, v0,  c, l, k;
  if (w/H<24.0) 
  {
    x0=pow(cosh(M_PI*w/(2.0*H)),2.0);
    printf("w=%d H=%d w/H=%f xo=%f\n",w,H,(double)w/H,x0);
    k=1.0/sqrt(x0);
    v0=K_over_Kdash(k);
    c=4*EPSILON_0/v0;
    l=mu*EPSILON_0/c;
    Zo=sqrt(l/c);
  }
  else
  {
  /*
    K=M_PI/2.0;
    KDASH=(log(2.0)+M_PI*w)/(4.0*H);
    v0=K/KDASH;
    c=4*Eo/v0;
    l=mu*Eo/c;
    Zo=sqrt(l/c);
    */
  }
  return(Zo);
}


