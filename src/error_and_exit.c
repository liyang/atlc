#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"


void error_and_exit(char s[], int exitnumber)
{
   fprintf(stderr,"%s\n",s);
   exit(exitnumber);
}
