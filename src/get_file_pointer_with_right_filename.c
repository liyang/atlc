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
    exit(1);
  }
  return(fp);
}
