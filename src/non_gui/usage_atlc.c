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

void usage_atlc(void)
{
#ifdef ENABLE_MP
  fprintf(stderr,"Usage: atlc [options ...] bitmap\n\n");
#endif
  fprintf(stderr,"options are:\n");
  fprintf(stderr,"  -C       \n      Print Licence and copying information\n");
  fprintf(stderr,"  -s       \n      Skip writing the Ex, Ey, E, V, U and Er files bitmap (.bmp) files\n");
  fprintf(stderr,"  -S       \n      Skip writing the Ex, Ey, E, V, U and Er files binary (.bin) files\n");
  fprintf(stderr,"  -v       \n      Verbose option. Print extra data (-vv or -vvv gives even more)\n\n");
  fprintf(stderr,"  -c cutoff\n      where 'cutoff' sets the cutoff criteria - see html docs or man page.\n");
  fprintf(stderr,"  -d rrggbb=Er\n      where the colour rrggbb (in hex) is a (d)ielectric of permittivity Er.\n");
  fprintf(stderr,"  -i factor\n      which lightens (factor>%.1f) or darkens (1.0 <factor<%.1f) output bitmaps.\n",
  IMAGE_FIDDLE_FACTOR,IMAGE_FIDDLE_FACTOR);
  fprintf(stderr,"  -r rate_multiplier\n      where 'rate_multiplier' sets the rate multipler (called r in source code)\n");
#ifdef ENABLE_MP
  fprintf(stderr,"  -t THREADs. \n      Where THREADs is the number of threads to use (normally best set to \n      the number of cpus). The default is %d.\n",MAX_THREADS);
#endif
#ifndef ENABLE_MP
  fprintf(stderr,"****************NOTE******************************\n");
  fprintf(stderr,"The -t option setting the number of threads is disabled since either\n");
  fprintf(stderr,"1) This is a Windoze executable OR\n");
  fprintf(stderr,"2) This is a Unix executable but not configured with multi-processor support.\n");
  fprintf(stderr,"There are no plans to add multi-processor support to Windoze, but if this is a\n");
  fprintf(stderr,"Unix executable, then re-run 'configure' using the '--with-mp' option\n");
#endif
  exit(0);
}
