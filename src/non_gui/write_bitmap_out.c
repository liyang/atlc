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

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */


extern int W, H;

/* This function can be used on any routines that writes .bmp files */

void write_bitmap_out(unsigned char *byte_aligned_image_data, FILE *image_data_fp,int sizeof_image, int W, int H)
{
   long temp_long;
   short temp_short;

   struct Bitmap_File_Head_Struct Bitmap_File_Head;
   struct Bitmap_Head_Struct Bitmap_Head;
   Bitmap_File_Head.zzMagic[0]='B';
   Bitmap_File_Head.zzMagic[1]='M';

   /* But the rest of Bitmap_File_Head does */

   temp_long=sizeof_image+0x36; /* 0x2 */
   /* fprintf(stderr,"file size=%ld\n",temp_long); */
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_File_Head.bfSize=(long) (temp_long);

   temp_short=0;  /* 0x6 */
#ifdef WORDS_BIGENDIAN
   byteswap_shorts(&temp_short);
#endif
   Bitmap_File_Head.zzHotX=temp_short; /* reserved */

   temp_short=0;   /*0x8*/
#ifdef WORDS_BIGENDIAN
   byteswap_shorts(&temp_short);
#endif
   Bitmap_File_Head.zzHotY=temp_short; /* reserved */

   temp_long=54;   /*0xA */
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_File_Head.bfOffs=temp_long;


   temp_long=0x28;   /*0xE */
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_File_Head.biSize=temp_long;

/* Done with the Bitmap_File_head */

   temp_long=W; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biWidth=temp_long;



   temp_long=H; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biHeight=temp_long;


   temp_short=1; 
#ifdef WORDS_BIGENDIAN
   byteswap_shorts(&temp_short);
#endif
   Bitmap_Head.biPlanes=temp_short;


   temp_short=24; 
#ifdef WORDS_BIGENDIAN
   byteswap_shorts(&temp_short);
#endif
   Bitmap_Head.biBitCnt=temp_short;


   temp_long=0; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biCompr=temp_long;


   temp_long=sizeof_image; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biSizeIm=temp_long;



   temp_long=W*10; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biXPels=temp_long;

   temp_long=H*10; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biYPels=temp_long;

   temp_long=0; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biClrUsed=temp_long;

   temp_long=0; 
#ifdef WORDS_BIGENDIAN
   byteswap_longs(&temp_long);
#endif
   Bitmap_Head.biClrImp=temp_long;

   /* Write Bitmap_File_Head, which is 18 bytes */
   fwrite(&(Bitmap_File_Head.zzMagic[0]),1,1,image_data_fp);  /*0x0*/
   fwrite(&(Bitmap_File_Head.zzMagic[1]),1,1,image_data_fp);  /*0x*/
   fwrite(&(Bitmap_File_Head.bfSize),4,1,image_data_fp);  /*0x02*/
   fwrite(&(Bitmap_File_Head.zzHotX),2,1,image_data_fp);  /*0x06*/
   fwrite(&(Bitmap_File_Head.zzHotY),2,1,image_data_fp);  /*0x08*/
   fwrite(&(Bitmap_File_Head.bfOffs),4,1,image_data_fp);  /*0xA*/
   fwrite(&(Bitmap_File_Head.biSize),4,1,image_data_fp);  /*0xE*/

   /* Now write Bitmap_Head to disk, which is  bytes */
   
   fwrite(&(Bitmap_Head.biWidth),4,1,image_data_fp);  /*0x12*/
   fwrite(&(Bitmap_Head.biHeight),4,1,image_data_fp); /*0x*/
   fwrite(&(Bitmap_Head.biPlanes),2,1,image_data_fp);
   fwrite(&(Bitmap_Head.biBitCnt),2,1,image_data_fp);
   fwrite(&(Bitmap_Head.biCompr),4,1,image_data_fp);
   fwrite(&(Bitmap_Head.biSizeIm),4,1,image_data_fp);
   fwrite(&(Bitmap_Head.biXPels),4,1,image_data_fp); /*0x26*/
   fwrite(&(Bitmap_Head.biYPels),4,1,image_data_fp); /*0x2a*/
   fwrite(&(Bitmap_Head.biClrUsed),4,1,image_data_fp); /*0x2e*/
   fwrite(&(Bitmap_Head.biClrImp),4,1,image_data_fp); /*0x32*/
  

   /* Finally write the image */
   fwrite(byte_aligned_image_data,(size_t) sizeof_image,1,image_data_fp);
   if( fclose(image_data_fp) != 0)
     exit_with_msg_and_exit_code("failed to close file in write_bitmap_out.c",CANT_CLOSE_FILE);
}
