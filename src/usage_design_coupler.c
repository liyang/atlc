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

void usage_design_coupler()
{
  fprintf(stderr,"\nUsage: design_coupler -h] [-l ] [-s] [-z ] CF fmin fmax filename\n");
  fprintf(stderr,"where: \n");
  fprintf(stderr,"      CF          is the coupling factor required in dB [10 log(P4/P1)]\n");
  fprintf(stderr,"      fmin        is the minimum frequency (MHz)\n");
  fprintf(stderr,"      fman        is the maximum frequency (MHz)\n");
  fprintf(stderr,"      filename    is the file to write data to.\n\n");
  fprintf(stderr,"Options are:\n");
  fprintf(stderr,"     -C           Print copyright, licencing and distribution information.\n");
  fprintf(stderr,"     -h           help\n");
  fprintf(stderr,"     -l length    to set the coupler length (m). Defaults to lambda/4\n");
  fprintf(stderr,"     -s fstep     to set the analysis frequecny in MHz step\n");
  fprintf(stderr,"     -z Zo        to set the impedance (default 50 Ohms)\n");
  fprintf(stderr,"Port 3 ****                                           *****Port 4\n");
  fprintf(stderr,"           *                                         *\n");
  fprintf(stderr,"           *******************************************\n");
  fprintf(stderr,"           *******************************************\n");
  fprintf(stderr,"           *                                         *\n");
  fprintf(stderr,"Port 1 ***                                            *****Port 2\n");
  fprintf(stderr,"           <-----------------L----------------------->\n");
  fprintf(stderr,"\nDrive Port 1, terminate P3 in Zo. P2 is the thru port, P4 is the coupled port\n");
}
