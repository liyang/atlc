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
  fprintf(stderr,"  -c cutoff\n      where 'cutoff' sets the cutoff criteria - see html docs or man page.\n");
  fprintf(stderr,"  -d rrggbb=Er\n      where the colour rrggbb (in hex) is a (d)ielectric of permittivity Er.\n");
  fprintf(stderr,"  -F appendfile\n");
  fprintf(stderr,"      appends all data to 'appendfile'.\n");
  fprintf(stderr,"  -i factor\n      which lightens (factor>%.1f) or darkens (1.0 <factor<%.1f) output bitmaps.\n",
  IMAGE_FIDDLE_FACTOR,IMAGE_FIDDLE_FACTOR);
#ifdef ENABLE_MP
  fprintf(stderr,"  -t THREADs. \n      Where THREADs is the number of threads to use (normally best set to \n      the number of cpus).\n");
#endif
  fprintf(stderr,"  -r rate_multiplier\n      where 'rate_multiplier' sets the rate multipler (called r in source code)\n");
  fprintf(stderr,"  -s       \n      Skip writing the Ex, Ey, E, V, U and Er files\n");
  fprintf(stderr,"  -v       \n      Verbose option. Print extra data to stdout.\n\n");
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
