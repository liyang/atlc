#include "definitions.h"

/* The following simple function just prints data into a file, or if
fp-stout, to the screen. Depending on whether the dielectric is mixed or
not, it is or is not possible to quote a value for Er. If Er is passed
as a mumber < 0, this function interprets that as meaning that the
dielectric is mixed, and says 'Er= MIXED' */

int print_data(FILE *fp, char *filename, double Er, double C,\
double L, double Zo, double v, double vf)
{
  int a=1;
  if(Er<0.0)
  {
    fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zo, v,vf,VERSION);
  }
  else
  {
    fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zo, v,vf,VERSION);
  }
  return(a);
}
