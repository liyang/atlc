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

/* This routines checkes for short circuits in the image. Clearly, it is
should not possible to have a 1V conductor touching a -1 V conductor. 

Although currently the software does not support the use of a floating 
conductor (an anea of fixed, but undefined) voltage, error messages
to take this into account have been included, but commentted out.*/ 

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern int width, height;
extern char **cell_type;

void check_for_shorts(void)
{
  int w, h;

  for(h=1;h<height;h++)
  {
    for(w=1; w<width;w++)
    {
      if( cell_type[w][h]==CONDUCTOR_ZERO_V )
      {
	if((cell_type[w][h+1]==CONDUCTOR_PLUS_ONE_V) || \
	(cell_type[w][h+1]==CONDUCTOR_MINUS_ONE_V) \
	|| (cell_type[w][h+1]==CONDUCTOR_FLOATING))
	{
	  fprintf(stderr,"\n**************ERROR******************\n");
	  fprintf(stderr,"Pixel (%d,%d) is set to 0V, but pixel\n",w,h);
	  fprintf(stderr,"(%d,%d) is set to a different fixed voltage\n",w,h+1);
	  fprintf(stderr,"creating a short. Please correct this.\n");
          exit_with_msg_and_exit_code("",CONDUCTOR_ZERO_V);
        }
      } /* end of if(cell_type==CONDUCTOR_ZERO_V) */

      else if( cell_type[w][h]==CONDUCTOR_PLUS_ONE_V )
      {
	if((cell_type[w][h+1]==CONDUCTOR_ZERO_V) || \
	(cell_type[w][h+1]==CONDUCTOR_MINUS_ONE_V) \
	|| (cell_type[w][h+1]==CONDUCTOR_FLOATING))
	{
	  fprintf(stderr,"\n**************ERROR******************\n");
	  fprintf(stderr,"Pixel (%d,%d) is set to 1 V, but pixel\n",w,h);
	  fprintf(stderr,"(%d,%d) is set to a different fixed voltage\n",w,h+1);
	  fprintf(stderr,"creating a short. Please correct this.\n");
          exit_with_msg_and_exit_code("",CONDUCTOR_PLUS_ONE_V);
        }
      } /* end of if(cell_type==CONDUCTOR_PLUS_ONE_V) */
      
      else if( cell_type[w][h]==CONDUCTOR_MINUS_ONE_V )
      {
	if((cell_type[w][h+1]==CONDUCTOR_ZERO_V) || \
	(cell_type[w][h+1]==CONDUCTOR_PLUS_ONE_V) \
	|| (cell_type[w][h+1]==CONDUCTOR_FLOATING))
	{
	  fprintf(stderr,"\n**************ERROR******************\n");
	  fprintf(stderr,"Pixel (%d,%d) is set to -1 V, but pixel\n",w,h);
	  fprintf(stderr,"(%d,%d) is set to a different fixed voltage\n",w,h+1);
	  fprintf(stderr,"creating a short. Please correct this.\n");
          exit_with_msg_and_exit_code("",CONDUCTOR_MINUS_ONE_V);
        }
      } /* end of if(cell_type==CONDUCTOR_PLUS_ONE_V) */

      else /* There are no shorting conductors */
      {
      }

    } /* end of for w.. loop */
  } /* end of for h .. loop */
} /* end of function check_for_shorts */

