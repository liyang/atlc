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

extern double DD, ww, hh, xx, yy, Er1;
extern int D, w, h, x, y;
extern int verbose;

void check_rect_in_circ_doubles(void)
{
   /* if(aa+dd>WW)
      error_and_exit("the dielectric extends horizontally outside the box (a+d>W)",100);
   if(bb+ww>=WW)
      error_and_exit("the inner conductor extends horizontally beyond the outer conductor(b+w>=W)",101);
   if(cc<=0.0)
      error_and_exit("The inner conductors's thickness (c) must be greater than zero ",12);
   if(hh<=0.0)
      error_and_exit("The thickness of dielectric Er2 (h) must be greater than zero ",12);
   if(hh+cc>=HH)
      error_and_exit("the inner conductor extends verticaly beyond the outer conductor(c+h>=H)",101); */


   /* XXXX I need to put some checks in here, as its easy for the inner to */
   /* touch the outer, if silly data is input. */

   if((DD<=0.0) || (ww<=0.0) || (hh<=0.0) || (xx<0.0) || (yy<0.0) )
      error_and_exit("D, w, and h must all be >0. x and y must be >=0. \n",102); 
}

void check_rect_in_circ_int(void)
{
   if(verbose==TRUE)
      fprintf(stderr,"D=%d w=%d h=%d x=%d y=%d \n",D, w, h, x, y);
}

