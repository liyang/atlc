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

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */



/* This function checks to see if the errors on the grid are too large.
A problem occurs if a number was zero, so this needs to be carefullly
controlled. */

void check_error(double user, int rect_in_rect, double gridsize, char *name)
{
   double fractional_error;
   fractional_error=fabs((user-(rect_in_rect*gridsize))/user);
   if(user > 0)
   {
      if(fractional_error > UNACCEPTABLE_ERROR)
      {
         fprintf(stderr,"Error #14. Unacceptable %f%% error in representing %s on the grid\n", fractional_error*100.0, name);
	 fprintf(stderr,"Exiting ....\n");
	 exit(2);
      }
      else if(fractional_error > ACCEPTABLE_ERROR)
         fprintf(stderr,"*WARNING*  %f%% error in representing %s on the grid\n", fractional_error*100.0, name);
      else{}
   }
}
