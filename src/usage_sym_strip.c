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
