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


/* This is a very quick hack at producing a program that provides 
a checksum. GNU produce one of course, but not everyone has it, 
or if like myself, they use a Sun, they will find Sun's 
sum is not the same as the GNU one. This is a very quick 
hack at producing a checksum. I did consider using the GNU one, 
but getting it to work is not trivual. The textutils package is 
nearly 1 Mb, so I thought this would do. It does in fact give the 
same answer as GNU's sum, but it can't read from standard input
or do anytthing else clever. It is just good enough for the job
needed, which was to have a quick check to see that some files 
are identical. */

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#define ROTATE_RIGHT(c) if ((c) & 01) (c) = ((c) >>1) + 0x8000; else (c) >>= 1;

int main(int argc, char **argv)
{
  FILE *fp;
  //unsigned long checksum = 0;
  //unsigned long checksum = 0;
  register unsigned long checksum = 0;
  register int ch;

  if( (fp=fopen(argv[1],"r")) == NULL)
  {
    printf("Error: can't open file\n");
    exit(1);
  }
  while ((ch = getc (fp)) != EOF)
  {
    ROTATE_RIGHT (checksum);
    checksum += ch;
    checksum &= 0xffff;       /* Keep it within bounds. */
  }
  printf ("%05lu\n", checksum);
  //printf("%05u\n",checksum);
}
