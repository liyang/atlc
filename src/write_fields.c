/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

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

#include "definitions.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

extern double **Vij;
extern double **Er;
extern unsigned char *bitmap_file_buffer;
extern int width, height, size, errno;
extern int **cell_type;

/* Write the following files, assuming an input of example.bmp 

example.E.bmp   Grayscale Bitmap of |E-field|, normallised to 1,
but corrected for Gamma
example.Ex.bmp  Colour Bitmap of x-directed E-field, normallised to 1, 
but corrected for Gamma
example.Ey.bmp  Colour Bitmap of y-directed E-field, normallised to 1, 
but corrected for Gamma
example.V.bmp   Colour Bitmap of Voltage field, normallised to 1, but 
corrected for Gamma
eexample.U.bmp  Grayscale bitmap, with just the energy (U=CV^2).

example.Ex.bin  binary file, with just the x-directed E-field 
(in volts/pixel) as doubles 
example.Ey.bin  binary file, with just the y-directed E-field 
(in volts/pixel) as doubles 
example.E.bin   binary file, with just the E-field {sqrt(Ex^2+Ey^2)} 
(in volts/pixel) as doubles 
example.V.bin   binary file, with just the Voltage as doubles 
eexample.U.bin  binary file, with just the energy (U=CV^2).

*/

extern double image_fiddle_factor;

void write_fields(char * filename)
{
  FILE *Ex_bin_fp, *Ey_bin_fp, *E_bin_fp, *V_bin_fp, *U_bin_fp;
  FILE *Ex_bmp_fp, *Ey_bmp_fp, *E_bmp_fp, *V_bmp_fp, *U_bmp_fp;
  FILE *permittivity_bin_fp, *permittivity_bmp_fp;
  unsigned char *image_dat;
  struct max_values maximum_values;
  int offset=-3, w, h;
  double E, Ex, Ey, U, ER;

  /* Allocate space in image_dat for an images, to show E, Ex, Ey etc  */
  image_dat=ustring(0,size);

  /* Find maximum of the parameters */

  find_maximum_values(&(maximum_values)); /* sets stucture maximum_values */


  /* Calculate the colours for Ex */
  Ex_bmp_fp=get_file_pointer_with_right_filename(filename,".Ex.bmp");
  Ex_bin_fp=get_file_pointer_with_right_filename(filename,".Ex.bin");
  fwrite(bitmap_file_buffer,0x36,1,Ex_bmp_fp);
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
        offset+=(4-offset%4);
        Ex=find_Ex(w,h);
      fwrite((void *) &Ex,sizeof(double), 1, Ex_bin_fp);
      calculate_colour_data(Ex, maximum_values.Ex_or_Ey_max, w, h, offset,image_dat, COLOUR);
    }
  } 
  fwrite(&(image_dat[0]),size,1,Ex_bmp_fp);
  fclose(Ex_bin_fp);
  fclose(Ex_bmp_fp);

  /* Calculate the colours for Ey */
  offset=-3;
  Ey_bmp_fp=get_file_pointer_with_right_filename(filename,".Ey.bmp");
  Ey_bin_fp=get_file_pointer_with_right_filename(filename,".Ey.bin");
  fwrite(bitmap_file_buffer,0x36,1,Ey_bmp_fp);
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
        offset+=(4-offset%4);
      Ey=find_Ey(w,h);
      fwrite((void *) &Ey, sizeof(double), 1, Ey_bin_fp);
      calculate_colour_data(Ey, maximum_values.Ex_or_Ey_max, w, h, offset,image_dat, COLOUR);
    }
  } 
  fwrite(&(image_dat[0]),size,1,Ey_bmp_fp);
  fclose(Ey_bin_fp);
  fclose(Ey_bmp_fp);


  /* Calculate the grayscale for E */
  offset=-3;
  E_bmp_fp=get_file_pointer_with_right_filename(filename,".E.bmp");
  E_bin_fp=get_file_pointer_with_right_filename(filename,".E.bin");
  fwrite(bitmap_file_buffer,0x36,1,E_bmp_fp);
  offset=-3;
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
        offset+=(4-offset%4);
      E=find_E(w,h);
      fwrite((void *) &E, sizeof(double), 1,E_bin_fp);
      calculate_colour_data(E, maximum_values.E_max, w, h, offset,image_dat, MONOCHROME);
    }
  } 
  fwrite(&(image_dat[0]),size,1,E_bmp_fp);
  fclose(E_bin_fp);
  fclose(E_bmp_fp);
   

  /* Calculate the grayscale for V */
  offset=-3;
  V_bmp_fp=get_file_pointer_with_right_filename(filename,".V.bmp");
  V_bin_fp=get_file_pointer_with_right_filename(filename,".V.bin");
  fwrite(bitmap_file_buffer,0x36,1,V_bmp_fp);
  offset=-3;
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
        offset+=(4-offset%4);
      fwrite((void *) &Vij[w][h], sizeof(double), 1,V_bin_fp);
      calculate_colour_data(Vij[w][h], maximum_values.V_max, w, h, offset,image_dat, COLOUR);
    }
  }
  fwrite(&(image_dat[0]),size,1,V_bmp_fp);
  fclose(V_bin_fp);
  fclose(V_bmp_fp);

  /* Calculate the grayscale for energy U */
  offset=-3;
  U_bmp_fp=get_file_pointer_with_right_filename(filename,".U.bmp");
  U_bin_fp=get_file_pointer_with_right_filename(filename,".U.bin");
  fwrite(bitmap_file_buffer,0x36,1,U_bmp_fp);
  offset=-3;
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
       offset+=(4-offset%4);
      U=find_energy_per_metre(w,h);
      fwrite((void *) &U, sizeof(double), 1,U_bin_fp);
      calculate_colour_data(U, maximum_values.U_max, w, h, offset,image_dat, MONOCHROME);
    }
  } 
  fwrite(&(image_dat[0]),size,1,U_bmp_fp);
  fclose(U_bin_fp);
  fclose(U_bmp_fp);


  /* Calculate the mixed colour/grayscale for permittivity. The red
  conductor (+1 V) is shown red, the green one (0V) green and the 
  blue conductor (-1V) as blue. The dielectrics are shown as a grayscale */
  
  offset=-3;
  permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");
  permittivity_bin_fp=get_file_pointer_with_right_filename(filename,".Er.bin");
  fwrite(bitmap_file_buffer,0x36,1,permittivity_bmp_fp);
  for(h=height-1;h>=0;h--)
  {
    for(w=0;w<width;++w)
    {
      offset+=3;
      if((w==0) && (offset%4!=0) && (h!=0)) 
        offset+=(4-offset%4);
      ER=Er[w][h];
      fwrite((void *) &ER, sizeof(double), 1,permittivity_bin_fp);
      calculate_colour_data(Er[w][h], MAX_ER, w, h, offset,image_dat,MIXED);
    }
  } 
  fwrite(&(image_dat[0]),size,1,permittivity_bmp_fp);
  fclose(permittivity_bin_fp);
  fclose(permittivity_bmp_fp);
  exit(8);
}
