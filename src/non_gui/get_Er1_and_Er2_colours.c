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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern double Er1, Er2, Ers[];
extern int colours[];
extern char names[];

void get_Er1_and_Er2_colours(int *colour_Er1, int *colour_Er2)
{
   int i;
   //int number_of_dielectrics_defined;
   *colour_Er2=-1; /* set them to a silly value, so we can check for it */
   *colour_Er2=-1;
   //number_of_dielectrics_defined=sizeof(Ers)/sizeof(Ers[0]);
   for(i=0; i<NUMBER_OF_DIELECTRICS_DEFINED; ++i)
   {
      if (  (Er1 < Ers[i] + TINY) && (Er1 > Ers[i] - TINY) )
         *colour_Er1=colours[i];
      if (  (Er2 < Ers[i] + TINY) && (Er2 > Ers[i] - TINY) )
         *colour_Er2=colours[i];
   }
   if (*colour_Er2 == -1) /* ie its not one defined in Erdata.h */
      *colour_Er2 =0xac82ac; /* report it is a silly value */
   if (*colour_Er1 == -1) /* ie its not one defined in Erdata.h */
      *colour_Er1 =0xcaff00; /* report it is a silly value */
}
