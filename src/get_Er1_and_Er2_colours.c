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
   *colour_Er2=-1; /* set them to a silly value, so we can check for it */
   *colour_Er2=-1;
   for(i=0; i<NUMBER_OF_DIELECTRICS_DEFINED; ++i)
   {
      if (  (Er1 < Ers[i] + TINY) && (Er1 > Ers[i] - TINY) )
      {
         *colour_Er1=colours[i];
      }
      if (  (Er2 < Ers[i] + TINY) && (Er2 > Ers[i] - TINY) )
      {
         *colour_Er2=colours[i];
      }
   }
   if (*colour_Er2 == -1) /* ie its not one defined in Erdata.h */
      *colour_Er2 =0xac82ac; /* report it is a silly value */
   if (*colour_Er1 == -1) /* ie its not one defined in Erdata.h */
      *colour_Er1 =0xcaff00; /* report it is a silly value */
}
