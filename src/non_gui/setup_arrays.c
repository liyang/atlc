#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "Erdata.h"

/* We need to set up the permittivity and cell_type arrays. A
complication arrises if a diaectric is found, that is not vacuum. 
If it is the only dielectric found, we calaculate C by saying C=C*Er. If
there are more than one dielectric, we need to calculate it twice. */

extern struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];
extern struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];
extern int width, height, verbose;

extern double **Er;
extern unsigned char *image_data;
extern int **cell_type, non_vacuum_found;
extern double found_this_dielectric;
extern double **Vij;

int colour_found, conductor_found, dielectric_found;


void setup_arrays(int *dielectrics_in_bitmap, int dielectrics_on_command_line)
{
   struct pixels pixels_found;
   int w,h, offset=-3, colour_mixture, i, z;
   unsigned char red, green, blue;
   int new_colour_in_image;
   double **v=Vij;
   pixels_found.red=0; pixels_found.white=0; pixels_found.other_colour=0;
   pixels_found.green=0;
   for(h=0;h<height;h++)
   {
      for (w=0; w<width;++w)
      {
	 cell_type[w][height-1-h]=0;
         dielectric_found=FALSE;
         conductor_found=FALSE;
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
	    v[w][height-1-h]=1.0;
	    Er[w][height-1-h]=METAL_ER;
	    conductor_found=TRUE;
	    pixels_found.red++;
         }
	 else if( colour_mixture == 0x00ff00 ) /* 0v green */
	 {
	    cell_type[w][height-1-h]=CONDUCTOR_ZERO_V;
	    v[w][height-1-h]=0.0;
	    conductor_found=TRUE;
	    pixels_found.green++;
	    Er[w][height-1-h]=METAL_ER;
         }
	 else if( colour_mixture == 0x0000ff ) /* -1V blue */
	 {
	    cell_type[w][height-1-h]=CONDUCTOR_MINUS_ONE_V;
	    v[w][height-1-h]=-1.0;
	    conductor_found=TRUE;
	    pixels_found.blue++;
	    Er[w][height-1-h]=METAL_ER;
         }
	 else /* A dielectric */
	 {
	    if(colour_mixture == 0xffffff ) /* White */
	       pixels_found.white++; /* Vacuum */
	    else
	       pixels_found.other_colour++; /* Some other dielectric */
	    cell_type[w][height-1-h]=DIELECTRIC;
	    v[w][height-1-h]=0.0; /* XXXXXXXXXXXXx */
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
		     found_this_dielectric=Ers[z];
                  }
               }
            }
            for(i=0;i<dielectrics_on_command_line;++i)
            {
	       if (Er_on_command_line[i].other_colour ==  colour_mixture)
	       {
	          Er[w][height-1-h]=Er_on_command_line[i].epsilon;
	          dielectric_found=TRUE;
		  found_this_dielectric=Er_on_command_line[i].epsilon;
		  non_vacuum_found=TRUE;
               }
            }
         }
         if((dielectric_found == FALSE) && (conductor_found==FALSE))
         {
            fprintf(stderr,"Error: The colour r=0x%x g=0x%x b=0x%x exists in the image, but the programme does not know how to interpret this colour. This is not a conductor (pure red, green or blue), nor is it one of the 10 dielectrics that are predefined in definitions.h, nor is a corresponding dielectric constant defined on the command line\n", red, green, blue);
	    exit(1);
         }
         /* We need to keep a record of the number of dielectrics in the image, 
         and determine if they are defined on the command line, or if they are
         defined on in the header file. */ 
         if (dielectric_found == TRUE) 
         {
	    new_colour_in_image=TRUE;
            for (i=0; i< *dielectrics_in_bitmap; ++i)
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
	      (*dielectrics_in_bitmap)++;
	      Er_in_bitmap[i].other_colour=colour_mixture;
	      Er_in_bitmap[i].red=red;
	      Er_in_bitmap[i].green=green;
	      Er_in_bitmap[i].blue=blue;
	      Er_in_bitmap[i].epsilon=Er[w][height-1-h];
            }
         } /* end of if dielctric found */ 
#ifdef DEBUG
         printf("cell_type[w][height-1-h]=cell_type[%d][%d]=%d\n", w, height-1-h ,cell_type[w][height-1-h]);
#endif
      } /* end of for w */
   } /*end of for h */
/*
   if(verbose)
   {
     printf("Red (+1 V conductor) pixels found   =       %7d \n",pixels_found.red);
     printf("Green (0 V conductor) pixels found  =       %7d \n",pixels_found.green);
     printf("Blue  (-1 V conductor) pixels found =       %7d \n",pixels_found.blue);
     printf("White (vacuum dielectric) pixels found =       %7d \n",pixels_found.white);
     printf("Others (not vacuum dielectic) pixels found =   %7d \n",pixels_found.other_colour);
     total_pixels_found=pixels_found.red+pixels_found.green+pixels_found.blue+ \
     pixels_found.white+pixels_found.other_colour;
     printf("Total number of pixels (sum of all above) = %7d \n",total_pixels_found);
   }
*/
   /* The following should not be necessary, but may be as a test */
   for(h=0;h<height;h++)
   {
     for (w=0; w<width;++w)
     {
       if((v[h][w] > 1.0) || (v[h][w]<-1.0))
         fprintf(stderr,"Sorry, something is wrong v[%d][%d]=%f\n",h,w,v[h][w]);
     }
   } 
  /*check_for_shorts();*/

} /* end of function */
