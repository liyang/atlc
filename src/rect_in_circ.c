/* The programme rect_in_rect is a pre-processor for atlc. It produces bitmaps of rectangular
inner and rectangular outer */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

#include "definitions.h"


double DD, ww, hh, xx, yy, Er1, Er2;
int D, w, h, x, y, W, H;

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
      /*usage_rect_in_circ();*/
      fprintf(stderr,"SORRY RECT_IN_CIRC IS NOT YET WORKING, SO HAS BEEN DISABLED. IT\n");
      fprintf(stderr,"BE ENABLED ON A FORTHCOMING VERSION\n");
      exit(1);
   if(argc-my_optind == 6)
   {
      DD=atof(argv[my_optind]);
      ww=atof(argv[my_optind+1]);
      hh=atof(argv[my_optind+2]);
      xx=atof(argv[my_optind+3]);
      yy=atof(argv[my_optind+4]);
      Er1=atof(argv[my_optind+5]);
      check_rect_in_circ_doubles();
      convert_rect_in_circ_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp);
   }
   else
      usage_rect_in_circ();
   exit(0);
}
