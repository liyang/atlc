#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

void usage_readbin(void)
{
  fprintf(stderr,"Usage: readbin [-r] binaryfile.V.bin\n\n");
  fprintf(stderr,"options are:\n");
  fprintf(stderr,"  -r        Used when analysing binary files created on\
  the other byte-ordering\n            (ie a big-endian example.V.bin file\
  on a small endian machine - or\n            the reverse)\n");
  exit(0);
}
