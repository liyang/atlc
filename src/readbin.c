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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int main(int argc, char **argv)
{
  FILE *fp;
  double *data, x;
  int q;
  int one=0, zero=0, minusone=0, other=0, length, i, reverse=0;
  int metal_er=0;
  while((q=get_options(argc,argv,"Cr")) != -1)
  switch (q)
  {
    case 'C':
      print_copyright("2002");
      exit(1);
    break;
    case 'r':
      reverse=1;
    break;
    case '?':
      usage_readbin();
  }
  if(argc-my_optind == 1)
  {
    fp=fopen(argv[my_optind],"r");
    if (fp==NULL)
    {
      fprintf(stderr,"Can't open %s for reading\n",argv[my_optind]);
      exit(1);
    }
    fseek(fp,0,SEEK_END);
    length=ftell(fp);
    printf("file length=%d bytes. There are %ld pixels\n", length, (long)
    length/sizeof(double));
    data=(double *)malloc(length);
    if(data==NULL)
    {
      fprintf(stderr,"Can't allocate ram in readbin.c\n");
      exit(2);
    }
    fseek(fp,0,SEEK_SET);
    fread(&(data[0]), sizeof(double), length/sizeof(double),fp);
    for(i=0;i<length/sizeof(double);++i)
    {
       x=data[i];
       //printf("i=%d x=%g\n",i,x);
       if(reverse==1)
	 byteswap_doubles(&x);
       if (fabs(x) <= 1e-15)
         zero++;
       else if ( x > 0.9999999999 && x < 1.000000000000001)
         one++;
       else if (x < -0.9999999999 && x > -1.000000000000001)
         minusone++;
       else if (x == METAL_ER)
	 metal_er++;
       else 
         other++;
    }
    printf("there are: %d ones, %d zeros, %d minus ones, %d %g's and %d other values\n",one, zero, minusone, metal_er, METAL_ER, other);
  }
  else
    usage_readbin();
  exit(0);
}
