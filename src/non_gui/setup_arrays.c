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
#include "Erdata.h"

/* We need to set up the permittivity and cell_type arrays. A
complication arrises if a diaectric is found, that is not vacuum. 
If it is the only dielectric found, we calaculate C by saying C=C*Er. If
there are more than one dielectric, we need to calculate it twice. */

extern struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];
extern struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];
extern int width, height;

extern double **Vij, **Er;
extern unsigned char *image_data;
extern int **cell_type, non_vacuum_found;
extern int coupler;
void setup_arrays(struct transmission_line_properties *data)
{
   struct pixels pixels_found;
   int conductor_found;
   int w,h, offset=-3, colour_mixture, i, z;
   /* int total_pixels_found; */
   unsigned char red, green, blue;
   int dielectric_found;
   int new_colour_in_image;
   int total_pixels_found;
   data->dielectrics_in_bitmap=0;
   pixels_found.red=0;
   pixels_found.green=0;
   pixels_found.blue=0;
   pixels_found.white=0; 
   pixels_found.other_colour=0; 
   for(h=0;h<height;h++)
   {
      for (w=0; w<width;++w)
      {
	 cell_type[w][height-1-h]=0;
         dielectric_found=FALSE;
         conductor_found=FALSE;
	 //data->conductor_found=FALSE;
	 offset+=3;
	 if((w==0) && (offset%4!=0) && (h!=0)) 
	    offset++; 
	 if((w==0) && (offset%4!=0) && (h!=0)) 
	    offset++; 
	 if((w==0) && (offset%4!=0) && (h!=0)) 
	    offset++; 
	 blue=image_data[offset];
	 green=image_data[offset+1];
	 red=image_data[offset+2];
	 colour_mixture=256*256*red+256*green+blue;
	 if( colour_mixture == 0xff0000 ) /* +1V red */
	 {
	    cell_type[w][height-1-h]=CONDUCTOR_PLUS_ONE_V;
	    Vij[w][height-1-h]=1.0;
	    Er[w][height-1-h]=METAL_ER;
	    conductor_found=TRUE;
	    pixels_found.red++;
         }
	 else if( colour_mixture == 0x00ff00 ) /* 0v green */
	 {
	    cell_type[w][height-1-h]=CONDUCTOR_ZERO_V;
	    Vij[w][height-1-h]=0.0;
	    conductor_found=TRUE;
	    pixels_found.green++;
	    Er[w][height-1-h]=METAL_ER;
         }
	 else if( colour_mixture == 0x0000ff ) /* -1V blue */
	 {
	    cell_type[w][height-1-h]=CONDUCTOR_MINUS_ONE_V;
	    Vij[w][height-1-h]=-1.0;
	    conductor_found=TRUE;
	    pixels_found.blue++;
	    Er[w][height-1-h]=METAL_ER;
	    coupler=TRUE;
	    data->couplerQ=TRUE;
         }
	 else /* A dielectric */
	 {
	    if(colour_mixture == 0xffffff ) /* White */
	       pixels_found.white++; /* Vacuum */
	    else
	       pixels_found.other_colour++; /* Some other dielectric */
	    cell_type[w][height-1-h]=DIELECTRIC;
	    Vij[w][height-1-h]=0.0;
	    for(z=0;z<NUMBER_OF_DIELECTRICS_DEFINED;++z)
	    {
	       /* Check to see if the colour is one of the 10 known
	       about, without any need to define on the command line
	       */
	       if (colour_mixture == colours[z])
	       {
	          Er[w][height-1-h]=Ers[z];
	          dielectric_found=TRUE;
		  if(z != 0)
		  {
		     non_vacuum_found=TRUE;
		     data->found_this_dielectric=Ers[z];
                  }
               }
            }
            for(i=0;i<data->dielectrics_on_command_line;++i)
            {
	       if (Er_on_command_line[i].other_colour ==  colour_mixture)
	       {
	          Er[w][height-1-h]=Er_on_command_line[i].epsilon;
	          dielectric_found=TRUE;
		  data->found_this_dielectric=Er_on_command_line[i].epsilon;
		  non_vacuum_found=TRUE;
               }
            }
         }
         if((dielectric_found == FALSE) && (conductor_found==FALSE))
         {
            fprintf(stderr,"Error#7: The colour r=0x%x g=0x%x b=0x%x (0x%2x%2x%2x) exists in the image at pixel %d,%d but\n",red,green,blue,red,green,blue,w,h);
	    fprintf(stderr,"the programme does not know how to interpret this colour. This is not a\n");
	    fprintf(stderr,"conductor (pure red, green or blue), nor is it one of the %d dielectrics that\n",NUMBER_OF_DIELECTRICS_DEFINED);
	    fprintf(stderr,"are predefined in Erdata.h, nor is a corresponding dielectric constant defined\n");
	    fprintf(stderr,"on the command line line with the -d option\n");
	    fprintf(stderr,"e.g. atlc -d %2x%2x%2x=1.9 file.bmp if this colour has a permittivity of 1.9\n",red,green,blue);
	    exit(1);
         }
         /* We need to keep a record of the number of dielectrics in the image, 
         and determine if they are defined on the command line, or if they are
         defined on in the header file. */ 
         if (dielectric_found == TRUE) 
         {
	    new_colour_in_image=TRUE;
            for (i=0; i< data->dielectrics_in_bitmap; ++i)
	    {
	       if (Er_in_bitmap[i].other_colour == colour_mixture) /* a known colour */
	       {
	          new_colour_in_image=FALSE;
	          if(colour_mixture != 0xffffff)
	          {
		     non_vacuum_found=TRUE;
                  }
	       }
            } 
	    if(new_colour_in_image==TRUE)
	    {
	      (data->dielectrics_in_bitmap)++;
	      Er_in_bitmap[i].other_colour=colour_mixture;
	      Er_in_bitmap[i].red=red;
	      Er_in_bitmap[i].green=green;
	      Er_in_bitmap[i].blue=blue;
	      Er_in_bitmap[i].epsilon=Er[w][height-1-h];
            }
         } /* end of if dielctric found */ 
      } /* end of for w */
   } /*end of for h */
   if(data->verbose_level >=2)
   {
     printf("Red (+1 V conductor) pixels found   =        %8d \n",pixels_found.red);
     printf("Green (0 V conductor) pixels found  =        %8d \n",pixels_found.green);
     printf("Blue  (-1 V conductor) pixels found =        %8d \n",pixels_found.blue);
     printf("White (vacuum dielectric) pixels found =     %8d \n",pixels_found.white);
     printf("Others (not vacuum dielectic) pixels found = %8d \n",pixels_found.other_colour);
     total_pixels_found=pixels_found.red+pixels_found.green+pixels_found.blue+ \
     pixels_found.white+pixels_found.other_colour;
     printf("Total number of pixels (sum of all above) =  %8d \n",total_pixels_found);
   }
   /* The following should not be necessary, but may be as a test */
   for(h=0;h<height;h++)
   {
     for (w=0; w<width;++w)
     {
       if((Vij[h][w] > 1.0) || (Vij[h][w]<-1.0))
         fprintf(stderr,"Sorry, something is wrong Vij[%d][%d]=%f\n",h,w,Vij[h][w]);
     }
   } 
  check_for_shorts();
} /* end of function */
