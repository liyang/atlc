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

#include "definitions.h"

//#define DEBUG

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "exit_codes.h"

/* Write the following files, assuming an input of example.bmp 

example.E.Even.bmp   Grayscale Bitmap of |E-field|, normallised to 1,
                     for even mode, but corrected for Gamma
example.Ex.Even.bmp  Colour Bitmap of x-directed E-field, normallised to 1, 
                     for even mode, but corrected for Gamma
example.Ey.Even.bmp  Colour Bitmap of y-directed E-field, normallised to 1, 
                     for even mode, but corrected for Gamma
example.V.Even.bmp   Colour Bitmap of Voltage field, normallised to 1,
                     for even mode, corrected for Gamma
example.U.Even.bmp   Grayscale bitmap, with just the energy (U=CV^2).
                     for even mode, corrected for Gamma


example.E.Odd.bmp    Grayscale Bitmap of |E-field|, normallised to 1,
                     for odd mode, but corrected for Gamma
example.Ex.Odd.bmp   Colour Bitmap of x-directed E-field, normallised to 1, 
                     for odd mode, but corrected for Gamma
example.Ey.Odd.bmp   Colour Bitmap of y-directed E-field, normallised to 1, 
                     for odd mode, but corrected for Gamma
example.V.Odd.bmp    Colour Bitmap of Voltage field, normallised to 1,
                     for odd mode, corrected for Gamma
example.U.Odd.bmp    Grayscale bitmap, with just the energy (U=CV^2).
                     for odd mode, corrected for Gamma


example.Er.bmp       Bitmap, showing dielectric constant as on grayscale 
		     and conductors as red,green and blue. This is *not* 
		     specifically for the any one mode. 




example.E.Odd.bin    Binary file of |E-field|, normallised to for odd mode.
example.Ex.Odd.bin   Colour binary file of x-directed E-field, for odd mode.
example.Ey.Odd.bin   Colour binary file of y-directed E-field, for odd mode.
example.V.Odd.bin    Colour binary file of Voltage field, normallised to 1, for odd mode.
example.U.Odd.bin    Bitmap, with just the energy (U=CV^2).  for odd mode.

example.E.Even.bin   Binary file of |E-field|, for even mode.
example.Ex.Even.bin  Colour binary file of x-directed E-field for even mode.
example.Ey.Even.bin  Colour binary file of y-directed E-field for even mode.
example.V.Even.bin   Colour binary file of Voltage field, for even mode.
example.U.Even.bin   Bitmap, with just the energy (U=CV^2) for even mode.


example.Er.bin       binary file, showing dielectric constant as on grayscale 
		     and conductors as red,green and blue. This is *not* 
		     specifically for the any one mode. 


*/

extern double **Vij;
extern double **Er;
extern unsigned char *bitmap_file_buffer;
extern int width, height, errno;
extern size_t size;
extern char **cell_type;

void write_fields_for_directional_couplers(char * filename, struct transmission_line_properties data, int odd_or_even)
{
  FILE *Ex_even_bin_fp, *Ey_even_bin_fp, *E_even_bin_fp, *V_even_bin_fp, *U_even_bin_fp;
  FILE *Ex_odd_bin_fp, *Ey_odd_bin_fp, *E_odd_bin_fp, *V_odd_bin_fp, *U_odd_bin_fp;
  FILE *Ex_even_bmp_fp, *Ey_even_bmp_fp, *E_even_bmp_fp, *V_even_bmp_fp, *U_even_bmp_fp;
  FILE *Ex_odd_bmp_fp, *Ey_odd_bmp_fp, *E_odd_bmp_fp, *V_odd_bmp_fp, *U_odd_bmp_fp;
  FILE *permittivity_bin_fp, *permittivity_bmp_fp;
#ifdef DEBUG
  FILE *fpOddEx, *fpOddEy;
  FILE *fpEvenEx, *fpEvenEy;
#endif
  unsigned char *image_data_Ex=NULL; 
  unsigned char *image_data_Ey=NULL;
  unsigned char *image_data_E=NULL;
  unsigned char *image_data_U=NULL; 
  unsigned char *image_data_V=NULL;
  unsigned char *image_data_Er=NULL;

  unsigned char r, g, b;

  static struct max_values maximum_values;
  int offset=-3, w, h;
  double E, Ex, Ey, U;

  if(data.write_binary_field_imagesQ==TRUE && odd_or_even == ODD)
  {
    Ex_odd_bin_fp=get_file_pointer_with_right_filename(filename,".Ex.odd.bin");
    Ey_odd_bin_fp=get_file_pointer_with_right_filename(filename,".Ey.odd.bin");
    E_odd_bin_fp=get_file_pointer_with_right_filename(filename,".E.odd.bin");
    V_odd_bin_fp=get_file_pointer_with_right_filename(filename,".V.odd.bin");
    U_odd_bin_fp=get_file_pointer_with_right_filename(filename,".U.odd.bin");
    permittivity_bin_fp=get_file_pointer_with_right_filename(filename,".Er.bin");

    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_E(w,h);
        U=find_energy_per_metre(w,h);
        if( fwrite((void *) &Ex,sizeof(double), 1, Ex_odd_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#1: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Ey,sizeof(double), 1, Ey_odd_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#2: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &E,sizeof(double), 1, E_odd_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#3: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &U,sizeof(double), 1, U_odd_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#4: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Vij[w][h],sizeof(double), 1, V_odd_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#5: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Er[w][h],sizeof(double), 1, permittivity_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#6: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
      }
    }
    if( fclose(Ex_odd_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#7: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(Ey_odd_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#8: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(E_odd_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#9: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(U_odd_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#10: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(V_odd_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#11: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(permittivity_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#12: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
  } /* End of writing odd binary files */

  if(data.write_bitmap_field_imagesQ==TRUE && odd_or_even == ODD)
  {
    /* Allocate ram to store the bitmaps before they are written to disk */
    image_data_Ex=ustring(0,size);
    image_data_Ey=ustring(0,size);
    image_data_E=ustring(0,size);
    image_data_V=ustring(0,size);
    image_data_Er=ustring(0,size);
    image_data_U=ustring(0,size);
    memset((void *) image_data_Ex,0,size);
    memset((void *) image_data_Ey,0,size);
    memset((void *) image_data_E,0,size);
    memset((void *) image_data_U,0,size);
    memset((void *) image_data_V,0,size);
    memset((void *) image_data_Er,0,size);

    /* Find maximum of the parameters */
    find_maximum_values(&(maximum_values),ZERO_ELEMENTS_FIRST); /* sets stucture maximum_values */
    Ex_odd_bmp_fp=get_file_pointer_with_right_filename(filename,".Ex.odd.bmp");
    Ey_odd_bmp_fp=get_file_pointer_with_right_filename(filename,".Ey.odd.bmp");
    E_odd_bmp_fp=get_file_pointer_with_right_filename(filename,".E.odd.bmp");
    V_odd_bmp_fp=get_file_pointer_with_right_filename(filename,".V.odd.bmp");
    U_odd_bmp_fp=get_file_pointer_with_right_filename(filename,".U.odd.bmp");
    permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");

    /* Permittivity images are written along with the odd images. It
    makes no difference whey they are written, since they don't change */

    permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");

    fwrite(bitmap_file_buffer,0x36,1,Ex_odd_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,Ey_odd_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,E_odd_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,U_odd_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,V_odd_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,permittivity_bmp_fp);
    offset=-3;
#ifdef DEBUG
    fpOddEx=fopen("Ex.odd.txt","w");
    fpOddEy=fopen("Ey.odd.txt","w");
#endif
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
        offset+=3;
        if((w==0) && (offset%4!=0) && (h!=0)) 
          offset+=(4-offset%4);
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_Ex(w,h);
        U=find_energy_per_metre(w,h);

        calculate_colour_data(Ex, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ex, COLOUR,&r,&g,&b);
        calculate_colour_data(Ey, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ey, COLOUR,&r,&g,&b);
        calculate_colour_data(E, maximum_values.E_max, w, h, offset,image_data_E, MONOCHROME,&r,&g,&b);
        calculate_colour_data(U, maximum_values.U_max, w, h, offset,image_data_U, MONOCHROME,&r,&g,&b);
        calculate_colour_data(Vij[w][h], maximum_values.V_max, w, h, offset,image_data_V, COLOUR,&r,&g,&b);
        calculate_colour_data(Er[w][h], MAX_ER, w, h, offset,image_data_Er, MIXED,&r,&g,&b);
#ifdef DEBUG
	fprintf(fpOddEx,"Ex w= %d h= %d r= %d g=%d blue= %d maximum_values.Ex_or_Ey_max= %g\n",w,h,r,g,b,maximum_values.Ex_or_Ey_max);
	fprintf(fpOddEy,"Ey w= %d h= %d r= %d g=%d blue= %d maximum_values.Ex_or_Ey_max= %g\n",w,h,r,g,b,maximum_values.Ex_or_Ey_max);
#endif
      }
    } 
#ifdef DEBUG
    fclose(fpOddEx);
    fclose(fpOddEy);
#endif
    if( fwrite((void *) image_data_Ex,size, 1, Ex_odd_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#25: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_Ey[0]),size, 1, Ey_odd_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#26: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_E[0]),size, 1, E_odd_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#27: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_V[0]),size, 1, V_odd_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#28: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_U[0]),size, 1, U_odd_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#29: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_Er[0]),size, 1, permittivity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#29: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);

    if( fclose(Ex_odd_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#30: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(Ey_odd_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#31: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(E_odd_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#32: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(V_odd_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#33: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(U_odd_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#34: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(permittivity_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#35: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    free_ustring(image_data_Ex,0,size);
    free_ustring(image_data_Ey,0,size);
    free_ustring(image_data_E,0,size);
    free_ustring(image_data_V,0,size);
    free_ustring(image_data_U,0,size);
    free_ustring(image_data_Er,0,size);
  } /* End of writing odd bitmap files  and therefore *all* odd files */

  if(data.write_binary_field_imagesQ==TRUE && odd_or_even == EVEN)
  {
    Ex_even_bin_fp=get_file_pointer_with_right_filename(filename,".Ex.even.bin");
    Ey_even_bin_fp=get_file_pointer_with_right_filename(filename,".Ey.even.bin");
    E_even_bin_fp=get_file_pointer_with_right_filename(filename,".E.even.bin");
    V_even_bin_fp=get_file_pointer_with_right_filename(filename,".V.even.bin");
    U_even_bin_fp=get_file_pointer_with_right_filename(filename,".U.even.bin");
    permittivity_bin_fp=get_file_pointer_with_right_filename(filename,".Er.bin");

    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_E(w,h);
        U=find_energy_per_metre(w,h);

        if( fwrite((void *) &Ex,sizeof(double), 1, Ex_even_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#1: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Ey,sizeof(double), 1, Ey_even_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#2: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &E,sizeof(double), 1, E_even_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#3: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &U,sizeof(double), 1, U_even_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#4: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Vij[w][h],sizeof(double), 1, V_even_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#5: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
        if( fwrite((void *) &Er[w][h],sizeof(double), 1, permittivity_bin_fp) != 1)
	  exit_with_msg_and_exit_code("Error#6: Failed to write binary file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
      }
    }
    if( fclose(Ex_even_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#7: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(Ey_even_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#8: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(E_even_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#9: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(U_even_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#10: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(V_even_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#11: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(permittivity_bin_fp) != 0)
      exit_with_msg_and_exit_code("Error#12: can't close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
  } /* End of writing even binary files */

  if(data.write_bitmap_field_imagesQ==TRUE &&  odd_or_even == EVEN)
  {
    /* Allocate ram to store the bitmaps before they are written to disk */
    image_data_Ex=ustring(0,size);
    image_data_Ey=ustring(0,size);
    image_data_E=ustring(0,size);
    image_data_V=ustring(0,size);
    image_data_Er=ustring(0,size);
    image_data_U=ustring(0,size);
    memset((void *) image_data_Ex,0,size);
    memset((void *) image_data_Ey,0,size);
    memset((void *) image_data_E,0,size);
    memset((void *) image_data_U,0,size);
    memset((void *) image_data_V,0,size);
    memset((void *) image_data_Er,0,size);
    /* Find maximum of the parameters */
    find_maximum_values(&(maximum_values),FALSE); /* sets stucture maximum_values */

    Ex_even_bmp_fp=get_file_pointer_with_right_filename(filename,".Ex.even.bmp");
    Ey_even_bmp_fp=get_file_pointer_with_right_filename(filename,".Ey.even.bmp");
    E_even_bmp_fp=get_file_pointer_with_right_filename(filename,".E.even.bmp");
    V_even_bmp_fp=get_file_pointer_with_right_filename(filename,".V.even.bmp");
    U_even_bmp_fp=get_file_pointer_with_right_filename(filename,".U.even.bmp");
    permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");

    /* Permittivity images are written along with the even images. It
    makes no difference whey they are written, since they don't change */

    permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");

    fwrite(bitmap_file_buffer,0x36,1,Ex_even_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,Ey_even_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,E_even_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,U_even_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,V_even_bmp_fp);
    fwrite(bitmap_file_buffer,0x36,1,permittivity_bmp_fp);
    offset=-3;
#ifdef DEBUG
    fpEvenEx=fopen("Ex.even.txt","w");
    fpEvenEy=fopen("Ey.even.txt","w");
#endif
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
        offset+=3;
        if((w==0) && (offset%4!=0) && (h!=0)) 
          offset+=(4-offset%4);
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_Ex(w,h);
        U=find_energy_per_metre(w,h);

        calculate_colour_data(Ex, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ex, COLOUR,&r,&g,&b);
        calculate_colour_data(Ey, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ey, COLOUR,&r,&g,&b);
        calculate_colour_data(E, maximum_values.E_max, w, h, offset,image_data_E, MONOCHROME,&r,&g,&b);
        calculate_colour_data(U, maximum_values.U_max, w, h, offset,image_data_U, MONOCHROME,&r,&g,&b);
        calculate_colour_data(Vij[w][h], maximum_values.V_max, w, h, offset,image_data_V, COLOUR,&r,&g,&b);
        calculate_colour_data(Er[w][h], MAX_ER, w, h, offset,image_data_Er, MIXED,&r,&g,&b);
#ifdef DEBUG
	fprintf(fpEvenEx,"Ex w= %d h= %d r= %d g=%d blue= %d maximum_values.Ex_or_Ey_max= %g\n",w,h,r,g,b,maximum_values.Ex_or_Ey_max);
	fprintf(fpEvenEy,"Ey w= %d h= %d r= %d g=%d blue= %d maximum_values.Ex_or_Ey_max= %g\n",w,h,r,g,b,maximum_values.Ex_or_Ey_max);
#endif 
      }
    } 
#ifdef DEBUG
    fclose(fpEvenEx);
    fclose(fpEvenEy);
#endif
    if( fwrite((void *) &(image_data_Ex[0]),size, 1, Ex_even_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#25: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_Ey[0]),size, 1, Ey_even_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#26: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_E[0]),size, 1, E_even_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#27: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_V[0]),size, 1, V_even_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#28: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_U[0]),size, 1, U_even_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#29: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);
    if( fwrite((void *) &(image_data_Er[0]),size, 1, permittivity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#29: Failed to write bitmap file in write_fields_for_directional_couplers.c",WRITE_FAILURE);

    if( fclose(Ex_even_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#30: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(Ey_even_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#31: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(E_even_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#32: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(V_even_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#33: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(U_even_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#34: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);
    if( fclose(permittivity_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#35: Unable to close file in write_fields_for_directional_couplers.c",CANT_CLOSE_FILE);

    /* Free ram used to store the bitmaps before they were written to disk */
    free_ustring(image_data_Ex,0,size);
    free_ustring(image_data_Ey,0,size);
    free_ustring(image_data_E,0,size);
    free_ustring(image_data_V,0,size);
    free_ustring(image_data_U,0,size);
    free_ustring(image_data_Er,0,size);
  } /* End of writing even bitmap files */
}
