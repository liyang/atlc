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

void usage_design_coupler()
{
  fprintf(stderr,"\nUsage: design_coupler [-c] [-P] [-H height] [-L length] [-s fstep] [-z Zo] CF fmin fmax\n");
  fprintf(stderr,"where: \n");
  fprintf(stderr,"      CF          is the coupling factor required in dB [10 log(P1/P2)]\n");
  fprintf(stderr,"      fmin        is the minimum frequency (MHz)\n");
  fprintf(stderr,"      fman        is the maximum frequency (MHz)\n");
  fprintf(stderr,"Options are:\n");
  fprintf(stderr,"     -c           calculate physical dimensions (takes a while)\n");
  fprintf(stderr,"     -P           Print copyright, licencing and distribution information.\n");
  fprintf(stderr,"     -H height    to set the height of the enclosure (defaults to 1 unit) \n");
  fprintf(stderr,"     -L length    to set the coupler length (m). Defaults to lambda/4\n");
  fprintf(stderr,"     -s fstep     to set the analysis frequency in MHz step\n");
  fprintf(stderr,"     -z Zo        to set the impedance (default 50 Ohms)\n");
  fprintf(stderr,"coupled port 2 ****                                        **** reflected port 3");
  fprintf(stderr,"                  *                                        *\n");
  fprintf(stderr,"                  ******************************************\n");
  fprintf(stderr,"                  ******************************************\n");
  fprintf(stderr,"                  *                                        *\n");
  fprintf(stderr,"input port 1   ****                                        **** through port 4\n");
  fprintf(stderr,"                  <-----------------L---------------------->\n");
  fprintf(stderr,"\nDrive Port 1. The main power comes out from port 4.\n");
  fprintf(stderr,"A fraction of the forward power comes from port 2\n"); 
  fprintf(stderr,"A fraction of the reflected power comes from port 3\n"); 
  fprintf(stderr,"All ports must present an impedance Zo.\n");
}
