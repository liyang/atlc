#include "definitions.h"

/* The following simple function just prints data into a file, or if
fp-stout, to the screen. Depending on whether the dielectric is mixed or
not, it is or is not possible to quote a value for Er. If Er is passed
as a mumber < 0, this function interprets that as meaning that the
dielectric is mixed, and says 'Er= MIXED' */

int print_data(FILE *fp, char *filename, double Er, double C,\
double L, double Zo, double Zodd, double Zeven, int whichZ, double v, double vf)
{
  int a=1;
  if(Er<0.0)
  {
    if(whichZ==Z0)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= N/A Ohms Zeven= N/A Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zo, v,vf,VERSION);
    else if(whichZ==Z_ODD)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= N/A Ohms Zodd= %.4f Ohms Zeven= N/A Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zodd, v,vf,VERSION);
    else if(whichZ==Z_ALL)
      fprintf(fp,"%s Er= MIXED C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= %.4f Ohms Zeven= %.4f Ohms v= %4g m/sv_f= %.4f VERSION=%s\n",filename,C*1e12, L*1e9, Zo, Zodd,Zeven,v,vf,VERSION);
  }
  else
  {
    if(whichZ==Z0)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= N/A Ohms Zeven= N/A Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zo, v,vf,VERSION);
    else if(whichZ==Z_ODD)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= N/A Ohms Zodd= %.4f Ohms Zeven= N/A Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zodd, v,vf,VERSION);
    else if(whichZ==Z_ALL)
      fprintf(fp,"%s Er= %.4f C= %.4f pF/m L= %.4f nH/m Zo= %.4f Ohms Zodd= %.4f Ohms Zeven= %.4f Ohms v= %4g m/s v_f= %.4f VERSION= %s\n",filename,Er,C*1e12, L*1e9, Zo, Zodd, Zeven, v,vf,VERSION);

  }
  return(a);
}
