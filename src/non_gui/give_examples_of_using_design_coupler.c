#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

void give_examples_of_using_design_coupler(void)
{
  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  printf("Here are a list of examples of how to use desgin_coupler\n");
  printf("In the examples, the %c sign is used in front of anything you must type\n",'%');
  printf("which is what you will probably see when using the csh or tcsh as a shell. It\n");
  printf("would probably be a $ sign if using the sh or bash shell. \n\n");
  printf("To find the odd and even mode impedances and frequency response of a 50 Ohm\n"); 
  printf("coupler covering 130 to 170 MHz with a coupling coefficient of 30 dB:\n\n");
  printf("%c design_coupler 30 130 170\n\n",'%');
  printf("Note the freqency response is symmetrical about the centre frequency at 0.192 dB");
  printf("below that wanted. You may wish to redesign this for a coupling coefficient of \n");
  printf("about 19.9 dB, so the maximum deviation from the ideal 30.0 dB never exceeds 0.1 dB\n");
  printf("Note the length suggested is 0.5 m (nearly 20\") is a quarter wave at\n");
  printf("the centre frequency of 150 MHz. You might find this a bit long, so\n");
  printf("let's specify a length of 0.25 m.\n\n");
  printf("% design_coupler -L 0.25 30 130 170\n\n",'%');
  printf("What you may notice is that while the coupling to the coupled port is exactly\n");
  printf("30 dB below the input power at the centre frequency (150 MHz) it is \n");
  printf("no longer symmetical about the centre frequency and the deviations from the\n");
  printf("ideal 30 dB are now much larger, with a maximum error of 1.012 dB\n");
  printf("Unlike the case when the length is the default quarter wave, there is not much\n");
  printf("you can do about this, since the deviations occur in both directions.\n\n");
  printf("Now assume you are reasonably happy with the response when the length is 0.0.25 m\n");
  printf("but would like to see the response at every 2.5 MHz. This can be done using the\n");
  printf("-s option to design_coupler.\n\n");
  printf("%c design_coupler -L 0.25 -s 2.5 30 130 170\n\n",'%');
  printf("Assuming the performance is acceptable, the dimensions of the coupler can\n"); //XX
  printf("be determined by adding the -d option. This will design a coupler that must look\n");
  printf("like the structure below. The two inner conductors, which are spaced equally\n");
  printf("between the top and bottom edges of the conductor, must be very thin.\n");
  printf("These are placed along the length of a box of width W, height H and of\n");
  printf("a length determined by the user, which in this case is 0.0.25 m\n");
  printf("|-----------^------------------------------------------------------------------|\n");
  printf("|           |                                                                  |\n");
  printf("|           |              <---w---><-----s----><---w-->                       |\n");
  printf("|           H              ---------            --------                       |\n");
  printf("|           |                                                                  |\n");
  printf("|           |   Er=1.0 (air)                                                   |\n");
  printf("------------v------------------------------------------------------------------\n");
  printf("<-----------------------------------------W----------------------------------->\n");
  printf("The program reports: H = 1.0, ; w = 1.44 ; s = 0.44\n");

  printf("The height of the box is H must be small compared to the length, (perhaps\n");
  printf("no more than 7%c of the length), or 17.5 mm in this case, with a length of 250 mm,\n",'%');
  printf("otherwise fringing effects will be significant. The width of the structure W\n");
  printf("should be as large as possible. The program suggests making this 5*H+2*w+s. The\n");
  printf("7%c and 5*H+2*w+s are educated gueeses, rather than exact figures. There is\n",'%');
  printf("no problem in making the width  larger than than 5*H+2*w+s, as long as the\n");
  printf("length is kept at 100 mm. The RATIO of the dimensions H, w and s (but not the\n");
  printf("length) must be kept constant. W just needs to be sufficiently large - it is\n");
  printf("uncritical.  \n\n");
  printf("If you happened to have some 6.3 mm sqaure brass available, then using\n");
  printf("this for the side walls would mean H becoming 6.3 mm and the dimensions w and s\n");
  printf("being; s=6.3*0.02=0.126 mm the size walls would mean H becoming 6.3 and the dimensions w and s\n");
  exit(0);
}
