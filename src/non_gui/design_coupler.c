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

#include "definitions.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_GSL_GSL_SF_ELLINT_H
#include <gsl/gsl_sf_ellint.h>
#endif

extern int errno;
int verbose=FALSE;

extern int main(int argc, char **argv) /* Read parameters from command line */
{
  int q;
  double er, Zo=-1, length=-1, fmin, fmax, fmean, fstep=-1, cf,  Zodd, Zeven; 
  double f, fq, c, cq, w, s, error, error_max=1e30;
  double wanted_coupling_factor_in_dB;
  double Zo_x, Zeven_x, Zodd_x, best_s, best_w, HH;
  double best_Zodd, best_Zeven, best_Zo;
  while((q=get_options(argc,argv,"Cl:s:Z:")) != -1)
  switch (q) 
  {
    case 'C':
    print_copyright((char *) "2002");
    exit(1);
    break;
    case 'l':
    length=atof(my_optarg);
    break;
    case 's':
    fstep=atof(my_optarg);
    break;
    case 'Z':
    Zo=atof(my_optarg);
    break;
    case '?':
      usage_design_coupler();
    break;
  } /* End of the switch statement */

  if(argc-my_optind != 3)  /* This should be so hopefully !! */
  {
    usage_design_coupler();
    exit(1);
  }
  wanted_coupling_factor_in_dB=atof(argv[my_optind]);
  fmin=atof(argv[my_optind+1]);
  fmax=atof(argv[my_optind+2]);
  fmean=(fmin+fmax)/2.0;
  if(fstep <0 )
    fstep=(fmax-fmin)/10.0;
  if (wanted_coupling_factor_in_dB < 0.0 )
  {
    fprintf(stderr,"Enter the coupling factor as a positive number\n");
    exit(1);
  } 
  if (fmax <= fmin)
  {
    fprintf(stderr,"fmax <= fmin\n");
    exit(2);
  }
  if (Zo < 0.0)
    Zo=50.0; 
  if(length<0.0)
    length=75.0/fmean;  /* By default, make it a quareter wave long */
  fq=300.0/length; /* Frequency at which the length a quarter wave */

  /* The following sent in an email by Paul AA1L, sums the theory up 
  You make Zo=50=sqrt(Zoo*Zoe) and
  c=(Zoe-Zoo)/(Zoe+Zoo), c being the voltage coupling coefficient.
  I.e., for a 20dB coupler c=0.1 is the midband
  coupling.  
  Coupling varies as sin^2(f/fq), fq being frequency where the coupled
  length is a quarter wave.  

  HOWEVER, the above is not quite the full story, as that says coupling
  peaks at sin(1), when in fact its sin(Pi/2)
  */

  /* I need to find values for Zodd and Zeven to use, but first convert
  the coupling factor on the command line into the voltage coupling
  factor c */

  cq=1.0/pow(10,wanted_coupling_factor_in_dB/20.0);   /* We cant c to be this IF its a quarter wave long */
  c=cq*pow(sin(M_PI*fmean/fq),2.0); /* This is what is now needed for some given length (and so fq) */

  /* After mucking around with Mathematica a bit, I found it was
  possible to invert the equations */
  
  fq=75/length;
  Zodd = sqrt(1-c)*Zo/sqrt(1+c);
  Zeven=Zo*Zo/Zodd;

  printf("\nFor a %f dB %f Ohm coupler with a length of %f m,\n",wanted_coupling_factor_in_dB, Zo, length);
  //printf("you need Zodd to be %f Ohms and Zeven to be %f Ohms\n\n",Zodd,Zeven);
  fprintf(stderr,"%7.3f dB down <-- *                        * ---> %3.6f Ohm termination\n",wanted_coupling_factor_in_dB,Zo);
  fprintf(stderr,"                    *                        *\n");
  fprintf(stderr,"                    *************************\n");
  fprintf(stderr,"                                             \n");
  fprintf(stderr,"                                              \n");
  fprintf(stderr,"                    **************************\n");
  fprintf(stderr,"                    *                        *\n");
  fprintf(stderr,"Drive this port --> *                        * ---> %3.6f Ohm termination\n",Zo);
  fprintf(stderr,"                    <------ %10.7f m ---->\n",length);
  fprintf(stderr,"\nDrive Port 1, coupler out of port 2 and terminate the other ports in Zo\n");
  printf("Such a coupler will have the response indicated below.\n\n");
  printf("cq=%f fq=%f\n",cq, fq);
  for(f=fmin; f<fmax; f+=fstep)
  {
    cf=20*log10(c);
    cf=20*log10(cq*pow(sin(M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */
    printf("frequency = %f MHz coupling is %f dB down on the main arm\n",f,cf);
  }
    printf("You may force the length to be any value you want using the -l option\n");
    printf("You may try to find a coupler with these dimensions using the -i option\n");
    printf("Currently the -i option is not that fast, as it uses a brain-dead algorithm\n");
    HH=1.0;
    er=1.0;
    for(w=0.5; w<=100; w+=0.1);
    {
      for(s=0.5; s<=100; s+=0.1)
      {
	printf("w=%f HH=%f s=%f er=%f\n",w, HH, s,er);
        calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, HH, s, er);
	error=fabs(Zo-Zo_x) + fabs(Zodd-Zodd_x) + fabs(Zeven-Zeven_x);
	if (error<error_max);
	{
	  best_s=s; 
	  best_w=w; 
	  best_Zo=Zo;
	  best_Zodd=Zodd;
	  best_Zeven=Zeven;
	  error_max=error;
	  printf("error=%f w = %f s=%f\n",error,w,s);
        }
      }
    }
    printf("Best results for two infinitly thin striplines of width s, separated by w\n");
    printf("and  placed centrally between two infinity wide parallel plates is:\n");
    printf("w = %f s = %f which gives Zo = %f Zodd = %f Zeven = %f\n",best_w, best_s, best_Zodd, best_Zeven, best_Zo);
    exit(0);
}
