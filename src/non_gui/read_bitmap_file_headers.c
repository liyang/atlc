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
#include "exit_codes.h"

unsigned char *bitmap_file_buffer;
/* We make the bitmap header public, as we write it back 
later, when saving bmp files. It saves a lot of hassle,
just writing what we read back, rather than correctly 
calculating all the data in the header correctly */

void read_bitmap_file_headers(char *filename, int *offset, size_t *size, int *width, int *height)
{
   FILE *fp;

   struct Bitmap_File_Head_Struct Bitmap_File_Head;
   struct Bitmap_Head_Struct Bitmap_Head;
   int ColormapSize, Maps;
   bitmap_file_buffer=ustring(0,0x50);
   if(strcmp(filename,"-")==0)
   {
      fp=stdin;   
   }
   else  
      fp=fopen(filename,"rb");
   if(fp==NULL)
   {
      fprintf(stderr,"cannot open %s\n", filename);
      exit_with_msg_and_error_code("",CANT_OPEN_FILE_FOR_READING);
   }
   /* Read the .bmp file header into a bitmap_file_buffer */
   if (!(fread(bitmap_file_buffer, 1,0x36,fp))||(strncmp((char *) bitmap_file_buffer,"BM",2)))
   {
      fprintf(stderr,"%s is not a valid BMP file\n", filename);
      exit_with_msg_and_error_code("",NOT_A_VALID_BITMAP_FILE);
   }
#ifdef WORDS_BIGENDIAN
   swap_bytes4(bitmap_file_buffer,0x02,(int *) &Bitmap_File_Head.bfSize);
   swap_bytes2(bitmap_file_buffer,0x06,(short *) &Bitmap_File_Head.zzHotX);
   swap_bytes2(bitmap_file_buffer,0x08,(short *) &Bitmap_File_Head.zzHotY);
   swap_bytes4(bitmap_file_buffer,0x0A,(int *) &Bitmap_File_Head.bfOffs);
   swap_bytes4(bitmap_file_buffer,0x0E,(int *) &Bitmap_File_Head.biSize);
#else
   memcpy(&Bitmap_File_Head.bfSize,bitmap_file_buffer+0x2,4);
   memcpy(&Bitmap_File_Head.zzHotX,bitmap_file_buffer+0x6,2);
   memcpy(&Bitmap_File_Head.zzHotY,bitmap_file_buffer+0x8,2);
   memcpy(&Bitmap_File_Head.bfOffs,bitmap_file_buffer+0xa,4);
   memcpy(&Bitmap_File_Head.biSize,bitmap_file_buffer+0xe,4);
#endif
   /*
   printf("bfSize = %ld \n",Bitmap_File_Head.bfSize);
   printf("zzHotX %d\n",Bitmap_File_Head.zzHotX);
   printf("zzHotY %d\n",Bitmap_File_Head.zzHotY);
   printf("bfOffs %ld\n",Bitmap_File_Head.bfOffs);
   printf("biSize %ld\n\n",Bitmap_File_Head.biSize); 
   */
   /* What kind of bitmap is it? */  
     
   if (Bitmap_File_Head.biSize == 12) /* OS/2 1.x ? */
   {
      fprintf(stderr,"Sorry, this appears to be a OS2 format bitmap, which atlc can't read\n");
      exit_with_msg_and_error_code("",OS2_FORMAT_BMP_FILE);
   }
   if (Bitmap_File_Head.biSize != 40) /* Windows 3.x */
   {
      fprintf(stderr,"This appears not to be a Windows format bitmap - perhaps OS2 ? Exiting ...\n");
      exit_with_msg_and_error_code("This appears not to be a Windows format bitmap - perhaps OS2 ? Exiting ..",NOT_A_WINDOZE_FORMAT_BITMAP);
   }
#ifdef WORDS_BIGENDIAN
   swap_bytes4(bitmap_file_buffer,0x12,(int *) &Bitmap_Head.biWidth);
   swap_bytes4(bitmap_file_buffer,0x16,(int *) &Bitmap_Head.biHeight);
   swap_bytes2(bitmap_file_buffer,0x1A,(short *) &Bitmap_Head.biPlanes);
   swap_bytes2(bitmap_file_buffer,0x1C,(short *) &Bitmap_Head.biBitCnt);
   swap_bytes4(bitmap_file_buffer,0x1E,(int *) &Bitmap_Head.biCompr);
   swap_bytes4(bitmap_file_buffer,0x22,(int *) &Bitmap_Head.biSizeIm);
   swap_bytes4(bitmap_file_buffer,0x26,(int *) &Bitmap_Head.biXPels);
   swap_bytes4(bitmap_file_buffer,0x2A,(int *) &Bitmap_Head.biYPels);
   swap_bytes4(bitmap_file_buffer,0x2E,(int *) &Bitmap_Head.biClrUsed);
   swap_bytes4(bitmap_file_buffer,0x32,(int *) &Bitmap_Head.biClrImp);
#else
   memcpy(&Bitmap_Head.biWidth,bitmap_file_buffer+0x12,4);
   memcpy(&Bitmap_Head.biHeight,bitmap_file_buffer+0x16,4);
   memcpy(&Bitmap_Head.biPlanes,bitmap_file_buffer+0x1a,2);
   memcpy(&Bitmap_Head.biBitCnt,bitmap_file_buffer+0x1c,2);
   memcpy(&Bitmap_Head.biCompr,bitmap_file_buffer+0x1e,4);
   memcpy(&Bitmap_Head.biSizeIm,bitmap_file_buffer+0x22,4);
   memcpy(&Bitmap_Head.biXPels,bitmap_file_buffer+0x26,4);
   memcpy(&Bitmap_Head.biYPels,bitmap_file_buffer+0x2a,4);
   memcpy(&Bitmap_Head.biClrUsed,bitmap_file_buffer+0x2e,4);
   memcpy(&Bitmap_Head.biClrImp,bitmap_file_buffer+0x32,4);
#endif
   Maps=4;
   if(Bitmap_Head.biBitCnt!=24)
   {
      fprintf(stderr,"Sorry, the .bmp bitmap must have 24 bits per colour,\n");
      fprintf(stderr,"but it has %d bits. Resave the \n",Bitmap_Head.biBitCnt);
      fprintf(stderr,"image using 24-bit colour\n");
      exit_with_msg_and_error_code("mage using 24-bit colour",BITMAP_NOT_24_BIT);
   }
   /*
   printf("Bitmap_Head.biWidth   =%ld =0x%x\n",Bitmap_Head.biWidth,Bitmap_Head.biWidth);
   printf("Bitmap_Head.biHeight  =%ld =0x%x\n",Bitmap_Head.biHeight,Bitmap_Head.biHeight);
   printf("Bitmap_Head.biPlanes  =%d =0x%x\n",Bitmap_Head.biPlanes,Bitmap_Head.biPlanes);
   printf("Bitmap_Head.biBitCnt  =%d =0x%x\n",Bitmap_Head.biBitCnt,Bitmap_Head.biBitCnt);
   printf("Bitmap_Head.biCompr   =%ld =0x%x\n",Bitmap_Head.biCompr,Bitmap_Head.biCompr );
   printf("Bitmap_Head.biSizeIm  =%ld =0x%x\n",Bitmap_Head.biSizeIm,Bitmap_Head.biSizeIm);
   printf("Bitmap_Head.biXPels   =%ld =0x%x\n",Bitmap_Head.biXPels,Bitmap_Head.biXPels);
   printf("Bitmap_Head.biYPels   =%ld =0x%x\n",Bitmap_Head.biYPels,Bitmap_Head.biYPels);
   printf("Bitmap_Head.biClrUsed =%ld =0x%x\n",Bitmap_Head.biClrUsed,Bitmap_Head.biClrUsed);
   printf("Bitmap_Head.biClrImp  =%ld =0x%x\n",Bitmap_Head.biClrImp,Bitmap_Head.biClrImp);
   */
   ColormapSize = (Bitmap_File_Head.bfOffs - Bitmap_File_Head.biSize - 14) / Maps;

   if ((Bitmap_Head.biClrUsed == 0) && (Bitmap_Head.biBitCnt <= 8))
	   Bitmap_Head.biClrUsed = ColormapSize;

   /* Sanity checks */

   if (Bitmap_Head.biHeight == 0 || Bitmap_Head.biWidth == 0) 
   {
      fprintf(stderr,"error reading BMP file header of %s - width or height is zero\n",filename);
      exit_with_msg_and_error_code("",WIDTH_OR_HEIGHT_ZERO_IN_BITMAP);
   } 
   if (Bitmap_Head.biPlanes != 1) 
   {
      fprintf(stderr,"error reading BMP file header of %s - bitplanes not equal to 1\n",filename);
      exit_with_msg_and_error_code("",BITPLANES_NOT_1_IN_BITMAP);
   }
   if (ColormapSize > 256 || Bitmap_Head.biClrUsed > 256)
   {
      fprintf(stderr,"error reading BMP file header of %s - colourmap size error\n",filename);
      exit_with_msg_and_error_code("",COLOURMAP_GREATER_THAN_256);
   }
   /* Windows and OS/2 declare filler so that rows are a multiple of
      word length (32 bits == 4 bytes)
   */

   /*fclose(fp); I'm not sure if this should be closed or not. Why did I ??? */
   *width=Bitmap_Head.biWidth;
   *height=Bitmap_Head.biHeight;
   *offset=Bitmap_File_Head.bfOffs;
   *size=Bitmap_Head.biSizeIm;
}
