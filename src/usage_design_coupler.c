#include "definitions.h"

void usage_design_coupler()
{
  fprintf(stderr,"\nUsage: design_coupler [-l length] [-s step] [-z Zo] CF low_MHz up_MHz filename\n");
  fprintf(stderr,"where: \n");
  fprintf(stderr,"      CF          is the coupling factor required in dB (eg 20.0 to couple 1%%)\n");
  fprintf(stderr,"      low_MHz     is the minimum frequency (eg 144)\n");
  fprintf(stderr,"      up_MHz      is the maximum frequency (eg 146)\n");
  fprintf(stderr,"      filename    is the file to write data to.\n\n");
  fprintf(stderr,"Options are:\n");
  fprintf(stderr,"     -z Zo       to set the impedance (default 50 Ohms)\n");
  fprintf(stderr,"     -s step     to set the analysis frequecny in MHz step\n");
  fprintf(stderr,"     -l length   to set the coupler length (m). Defaults to lambda/4 \n\n");
  fprintf(stderr,"P3****                                           *****P4\n");
  fprintf(stderr,"      *                                         *\n");
  fprintf(stderr,"      *******************************************\n");
  fprintf(stderr,"      *******************************************\n");
  fprintf(stderr,"      *                                         *\n");
  fprintf(stderr,"P1***                                            *****P2\n");
  fprintf(stderr,"      <-----------------L----------------------->\n");
  fprintf(stderr,"\nDrive P1, terminate P3 in Zo\n");
}
