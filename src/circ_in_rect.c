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

double  dd, WW, HH, xx, yy, Er1;
int d, W, H, x, y;

/* The following are only needed, so I can link in two  
convert_circ_in_circ_dimensions_to_integers.c
and
convert_rect_in_rect_dimensions_to_integers.c
*/

double Er2;

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
	 fprintf(stderr,"Error #11. Can't write bitmap to %s. Exiting...\n",my_optarg);
	 exit(11);
      }
      fileflag=TRUE;
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
   if(argc-my_optind ==6)
   {
      dd=atof(argv[my_optind]);
      WW=atof(argv[my_optind+1]);
      HH=atof(argv[my_optind+2]);
      xx=atof(argv[my_optind+3]);
      yy=atof(argv[my_optind+4]);
      Er1=atof(argv[my_optind+5]);
      check_circ_in_rect_doubles();
      convert_circ_in_rect_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp);
   }
   else
      usage_circ_in_rect();
   exit(0);
}
