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

void usage_symmetrical_strip(void)
{
  fprintf(stderr,"sym_strip produces a bitmap for a wide stripline and \ncalculates Zo ASSUMING IT IT INFINITELY WIDE (which it is not of course)\n\n");
  fprintf(stderr,"Usage: sym_strip W H w filename\n\n");
  fprintf(stderr,"-----------------------------------------------\n");
  fprintf(stderr,"                                               \n");
  fprintf(stderr,"              <----------w----------->\n");
  fprintf(stderr,"              ------------------------\n");
  fprintf(stderr,"                                      \n");
  fprintf(stderr,"                                      \n");
  fprintf(stderr,"------------------------------------------------\n");
  fprintf(stderr,"<-----------------------W---------------------->\n\n");
}
