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

/* The programme rect_in_rect is a pre-processor for atlc. It produces bitmaps of rectangular
inner and rectangular outer */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2, DD;
int W, H, a, b, c, d, w, h, o;
/* The following are only needed, so I can link in two  
convert_circ_in_circ_dimensions_to_integers.c
and
convert_rect_in_rect_dimensions_to_integers.c
*/

int verbose=FALSE;
int lowest=2500, highest=10000;
int fileflag=FALSE;

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
   int  bmp_size=DEFAULT_BMPSIZE;
   int q;
   FILE *image_data_fp=stdout;
   struct transmission_line_properties not_used_currently;

   while((q=get_options(argc,argv,"b:f:v")) != -1)
   switch (q) 
   {
      case 'b':
      bmp_size=atol(my_optarg); 
      break;
      case 'f':
      /* By default bitmap image goes to stdout, but we can send to a file 
      with the -f option. */
      if((image_data_fp=fopen(my_optarg,"w"))==NULL)
      {
	 fprintf(stderr,"Can't write to %s. Exiting ...\n",my_optarg);
	 exit(1);
      }
      fileflag=TRUE;
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
   if(argc-my_optind ==10)
   {
      WW=atof(argv[my_optind]);
      HH=atof(argv[my_optind+1]);
      aa=atof(argv[my_optind+2]);
      bb=atof(argv[my_optind+3]);
      cc=atof(argv[my_optind+4]);
      dd=atof(argv[my_optind+5]);
      ww=atof(argv[my_optind+6]);
      hh=atof(argv[my_optind+7]);
      Er1=atof(argv[my_optind+8]);
      Er2=atof(argv[my_optind+9]);
      if(verbose==TRUE)
        printf("WW=%f HH=%f aa=%f bb=%f cc=%f dd=%f ww=%f hh=%f Er1=%f Er2=%f\n",WW,HH,aa,bb,cc,dd,ww,hh,Er1,Er2);
      check_rect_in_rect_doubles();
      convert_rect_in_rect_dimensions_to_integers(bmp_size);
      if(verbose==TRUE)
        printf("W=%d H=%d a=%d b=%d c=%d d=%d w=%d h=%d\n",W,H,a,b,c,d,w,h);
      write_bitmap(image_data_fp, not_used_currently);
   }
   else
      usage_rect_in_rect();
   exit(0);
}
