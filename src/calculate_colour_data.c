#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#ifdef HAVE_STDLIB_h
#include <stdlib.h>
#endif

#include "definitions.h"

extern double **Vij;
extern double **Er;
extern double image_fiddle_factor;
extern double width, height;
extern int **cell_type;

void calculate_colour_data(double x, double xmax, int w, int h, int offset, unsigned char *image_dat, char image_type)
{
  int red=0, green=0, blue=0; /*just to avoid a compiler warning */
  if(image_type==COLOUR) /*Ex, Ey, V */
  {
    if(x >= 0.0)
    {
      red=255*pow(x/xmax,1.0/image_fiddle_factor);
      green=0; 
      blue=0; 
    }
    else if (x < 0)
    {
      red=0; 
      green=0; 
      blue=255*pow(-x/xmax,1.0/image_fiddle_factor); 
    }
  }
  else if (image_type==MONOCHROME) /* E, energy, permittivity */
  {
    if(x > xmax)
    {
      red=0; green=0; blue=0;
    }
    else
    {
      red=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      green=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      blue=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
     }
  }
  else if (image_type==MIXED) /* Only for permittivity*/
  {
    if(cell_type[w][h]==CONDUCTOR_ZERO_V)
    {
      red=0; green=255; blue=0;
    }
    else if(cell_type[w][h]==CONDUCTOR_PLUS_ONE_V)
    {
      red=255; green=0; blue=0;
    }
    else if(cell_type[w][h]==CONDUCTOR_MINUS_ONE_V)
    {
      red=0; green=0; blue=255;
    }
    else
    {
      red=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      green=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      blue=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
     }
  }
  image_dat[offset]=blue; 
  image_dat[offset+1]=green; 
  image_dat[offset+2]=red; 
}
