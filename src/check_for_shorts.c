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
extern int **cell_type;

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
	  fprintf(stderr,"Its also possible the adjacent pixels is a\n");
	  fprintf(stderr,"floating conductor, in which case make the\n");
	  fprintf(stderr,"conductor green (0V). Either way correct it.\n");
          exit(CONDUCTOR_ZERO_V);
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
	  fprintf(stderr,"Its also possible the adjacent pixels is a\n");
	  fprintf(stderr,"floating conductor, in which case make the\n");
	  fprintf(stderr,"conductor red (1 V). Either way correct it.\n");
          exit(CONDUCTOR_PLUS_ONE_V);
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
	  fprintf(stderr,"Its also possible the adjacent pixels is a\n");
	  fprintf(stderr,"floating conductor, in which case make the\n");
	  fprintf(stderr,"conductor black (-1 V). Either way correct it.\n");
          exit(CONDUCTOR_MINUS_ONE_V);
        }
      } /* end of if(cell_type==CONDUCTOR_PLUS_ONE_V) */

      else /* There are no shorting conductors */
      {
      }

    } /* end of for w.. loop */
  } /* end of for h .. loop */
} /* end of function check_for_shorts */

