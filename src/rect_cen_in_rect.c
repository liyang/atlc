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

double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2, oo;
int W, H, a, b, c, d, w, h, D, o;
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
   if(argc-my_optind ==5)
   {

      WW=atof(argv[my_optind]);
      HH=atof(argv[my_optind+1]);
      ww=atof(argv[my_optind+2]);
      cc=atof(argv[my_optind+3]);
      Er1=atof(argv[my_optind+4]);

      /* To make the programme easier to write, rect_cen_in_rect uses 
      the same variables as rect_in_rect. We just calculate the 
      values not given (a, b, d, h and Er1 from those given
      (W, H, c and w) */

      aa=(WW-ww)/2.0;
      bb=(WW-ww)/2.0;
      dd=ww;
      hh=(HH-cc)/2.0;
      Er2=Er1;
      check_rect_in_rect_doubles();
      convert_rect_in_rect_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp);
   }
   else
      usage_rect_cen_in_rect();
   exit(0);
}
