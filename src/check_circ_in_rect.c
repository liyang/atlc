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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"


/* These items are supplied on the commmand line */

extern double dd, WW, HH, xx, yy, Er1;
extern int d, W, H, x, y;
extern int verbose;

void check_circ_in_rect_doubles(void)
{
   if( Er1<1.0) 
      error_and_exit("The relative permittivity (Er) must be >= 1.0",100);
   if (dd/2.0+yy >= HH) 
      error_and_exit("The inner will be touching the top or bottom of the outer !!! ",100);
   if (dd/2.0+xx >= WW) 
      error_and_exit("The inner will be touching one of the sides !!! ",100);
      
}

void check_circ_in_rect_int(void)
{
/*
   if(verbose==TRUE)
      fprintf(stderr,"d_outer = %d d_inner=%d offset=%h \n",D, d, h);
      */
}
