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


/* These items are supplied on the commmand line */

extern double DD, dd, hh, Er1;
extern int D, d, h;
extern int verbose;

void check_circ_in_circ_doubles(void)
{
   if( Er1<1.0) 
      error_and_exit("Error #9. The relative permittivity (Er) must be >= 1.0",9);
   if (dd/2.0+hh >= DD) 
      error_and_exit("Error #10 The inner will be touching the outer !!!",10);
}

void check_circ_in_circ_int(void)
{
   if(verbose==TRUE)
      fprintf(stderr,"d_outer = %d d_inner=%d offset=%x \n",D, d, h);
}
