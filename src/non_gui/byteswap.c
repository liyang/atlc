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

#include "definitions.h"

extern int errno;

/* This routine swaps data from the little-endian format to the big-endian 
format or visa-versa. */

void byteswap_doubles(double *a)
{
	unsigned char b[8],c[8];
	(void) memcpy(b,a,8); 
	c[0]=b[7]; /* swap data around */
	c[1]=b[6];
	c[2]=b[5];
	c[3]=b[4];
	c[4]=b[3];
	c[5]=b[2];
	c[6]=b[1];
	c[7]=b[0];
	(void) memcpy(a,c,8);
#ifdef DEBUG
	error_check("byteswap");
#endif
}

#if SIZEOF_INT==4
void byteswap_ints(int *a)
{
	unsigned char b[4],c[4];
	(void) memcpy(b,a,4); 
	c[0]=b[3]; /* swap data around */
	c[1]=b[2];
	c[2]=b[1];
	c[3]=b[0];
	(void) memcpy(a,c,4);
#ifdef DEBUG
	error_check("byteswap_ints (8 byte variety)");
#endif
}

#elif SIZEOF_INT==8

void byteswap_ints(int *a)
{
	unsigned char b[8],c[8];
	(void) memcpy(b,a,8); 
	c[0]=b[7]; /* swap data around */
	c[1]=b[6];
	c[2]=b[5];
	c[3]=b[4];
	c[4]=b[3];
	c[5]=b[2];
	c[6]=b[1];
	c[7]=b[0];
	(void) memcpy(a,c,8);
#ifdef DEBUG
	error_check("byteswap_ints (8 byte variety)");
#endif
}

#endif

#if SIZEOF_LONG==4
void byteswap_longs(long *a)
{
	unsigned char b[4],c[4];
	(void) memcpy(b,a,4); 
	c[0]=b[3]; /* swap data around */
	c[1]=b[2];
	c[2]=b[1];
	c[3]=b[0];
	(void) memcpy(a,c,4);
#ifdef DEBUG
	error_check("byteswap_longs (4 byte variety)");
#endif
}

#elif SIZEOF_LONG==8

void byteswap_longs(long *a)
{
	unsigned char b[8],c[8];
	(void) memcpy(b,a,8); 
	c[0]=b[7]; /* swap data around */
	c[1]=b[6];
	c[2]=b[5];
	c[3]=b[4];
	c[4]=b[3];
	c[5]=b[2];
	c[6]=b[1];
	c[7]=b[0];
	(void) memcpy(a,c,8);
#ifdef DEBUG
	error_check("byteswap_longs (8 byte variety)");
#endif
}
#endif

void byteswap_shorts(short *a)
{
	unsigned char b[2],c[2];
	(void) memcpy(b,a,2); 
	c[0]=b[1]; /* swap data around */
	c[1]=b[0];
	(void) memcpy(a,c,2);
}

/* The function swap_bytes4() swaps 4 bytes of data some distance 'offset' into a buffer.
It is typically used when swaping the bytes in a header, where the offset into the
header is known and it is necessary to byteswap them for reasons of differing byte
ordering*/

void swap_bytes4(unsigned char *buffer, int offset, int *answer)
{
   *answer=256*256*256*buffer[offset+3]+256*256*buffer[offset+2]+256*buffer[offset+1]+buffer[offset];
}

/* The function swap_bytes2() swaps two bytes of data some distance 'offset' into a buffer.
It is typically used when swaping the bytes in a header, where the offset into the
header is known and it is necessary to byteswap them for reasons of differing byte
ordering*/

void swap_bytes2(unsigned char *buffer, int offset, short *answer)
{
   *answer=256*buffer[offset+1]+buffer[offset];
}
