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

/* This function take a filename with the extension .bmp (eg coax.bmp) 
and will produce files such as coax.V.bmp, coax.E.bmp, coax.E.bin etc */

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

FILE *get_file_pointer_with_right_filename(char *filename, char *extension)
{
  char *basename, *temp;
  FILE *fp;
  basename=string(0,1000);
  temp=string(0,1000);
  memset((void *)temp,0,1000);
  memset((void *)basename,0,1000);

  basename=strncpy(basename,filename,strlen(filename)-4);
  strcpy(temp,basename);
  strcat(temp,extension);
  if((fp=fopen(temp,"w+b"))==NULL)
  {
    fprintf(stderr,"Sorry, cant open %s for writing\n", temp);
    exit_with_msg_and_error_code("",CANT_OPEN_FOR_WRITING);
  }
  return(fp);
}
