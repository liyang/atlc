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

/* desgin_coupler does two very different things in the one program
1) Given a frequency range, the required coupling factor, it calcuates
the odd and even mode impedances needed for a coupler. It does this
assuming the length of the coupler is lambda/4, although you can vary
that on the command line with the -l option. 

2) Once the optimal values for the even and odd mode impedances are
found, it itteratively looks up the odd and even mode impedances for two
think lines of various widths (w) and spacings (s), looking for the
combination that gives the best rms error between the required
impedances and those that will result with the coupler design as
presented. 

It is assumed by default that the height of the box is of one unit (1
mm, 1" etc, but this may be changed on the command line. It only scales
the paramters w and s. 

*/

int main(int argc, char **argv) /* Read parameters from command line */
{
  int q;
  int calculate_physical_dimensions=FALSE;
  double lq, lolq, er, Zo=-1, lambda, length=-1, fmin, fmax, fmean, fstep=-1, cf,  Zodd, Zeven; 
  double f, fq, c, cq, w, s, error, error_max=1e30;
  double wanted_coupling_factor_in_dB, step=0.05;
  double Zo_x=-1, Zeven_x=-1, Zodd_x=-1, best_s=-1, best_w=-1, height_of_box=1.0;
  double best_Zodd=-1, best_Zeven=-1, best_Zo=-1;
  while((q=get_options(argc,argv,"cPL:s:Z:H:")) != -1)
  switch (q) 
  {
    case 'c':
    calculate_physical_dimensions=TRUE;
    case 'P':
    print_copyright((char *) "2002");
    exit(1);
    break;
    case 'L':
    length=atof(my_optarg);
    break;
    case 'H':
    height_of_box=atof(my_optarg);
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
  printf("length=%f\n",length);
  if(fstep <0 )
    fstep=(fmax-fmin)/4.0;
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
    length=75.0/fmean;  /* By default, make it a quarter wave long */
  fq=fmean;
  lq=300/fmean;
  //lolq=length/lq;
  lolq=lq/length;

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
  c=cq;

  /* After mucking around with Mathematica a bit, I found it was
  possible to invert the equations */
  
  Zodd = sqrt(1-c)*Zo/sqrt(1+c);
  Zeven=Zo*Zo/Zodd;

  printf("\nFor a %f dB %f Ohm coupler with a length of %f m,\n",wanted_coupling_factor_in_dB, Zo, length);
  printf("you need Zodd to be %f Ohms and Zeven to be %f Ohms\n\n",Zodd,Zeven);
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
  for(f=fmin; f<=fmax; f+=fstep)
  {
    fq=65/fmean;

    cf=20*log10(c);
    cf=20*log10(cq*pow(sin(0.5*M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */

    //cf=20*log10(cq*pow(sin(0.5*M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */
    //cf=20*log10(cq*pow(sin(0.5*M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */
    //cf=20*log10(c*pow(sin(0.5*M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */
    //f*=
    cf=20*log10(cq*pow(sin(0.5*M_PI*f/fq),2.0)); /* This is what is now needed for some given length (and so fq) */
    printf("frequency = %f MHz coupling is %f dB down on the main arm\n",f,cf);
  }
    printf("You may force the length to be any value you want using the -l option\n");
    printf("You may try to find a coupler with these dimensions using the -c option\n");
    printf("Currently the -c option is not that fast, as it uses a brain-dead algorithm\n");
    if(calculate_physical_dimensions==TRUE)
    {
    er=1.0;
    for(s = 0.02; s<=100; s+=step)
    {
      for(w = 0.02; w<= 11.0; w += step)
      {
	/* Results are calculated assuming the box is one unit (mm, inch
	etc) high and later scaled */
        calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, 1.0, s, er);
	error=pow(Zodd-Zodd_x,2.0) + pow(Zeven-Zeven_x,2.0);
	if( error < error_max )
	{
	  best_s=s; 
	  best_w=w; 
	  best_Zo=sqrt(best_Zo * best_Zeven);
	  best_Zodd=Zodd;
	  best_Zeven=Zeven;
	  error_max=error;
	  //printf("error=%f error_max =%f w = %f s=%f Zodd_x =%f Zo_even=%f Zo_x=%f\n",error,error_max,w*height_of_box,s*height_of_box,Zodd_x,Zeven_x, Zo_x);
        }
      }
    }
    printf("w = %f s = %f which gives Zo = %f Zodd = %f Zeven = %f\n",best_w, best_s, best_Zo, best_Zodd, best_Zeven);
    printf("done stage 1\n");
    /* Now try to get closer */
    for(s = best_s-step; s<=best_s+step; s+=step/1000)
    {
      for(w = best_w-step; w<= best_w+step; w += step/1000)
      {
	/* Results are calculated assuming the box is one unit (mm, inch
	etc) high and later scaled */
	//printf("w=%f height_of_box=%f s=%f er=%f\n",w, 1.0, s,er);
        calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, 1.0, s, er);
	error=fabs(Zodd-Zodd_x) + fabs(Zeven-Zeven_x);
	if( error < error_max )
	{
	  best_s=s; 
	  best_w=w; 
	  best_Zodd=Zodd;
	  best_Zeven=Zeven;
	  error_max=error;
	  printf("error=%f error_max =%f w = %f s=%f Zodd_x =%f Zo_even=%f Zo_x=%f\n",error,error_max,w*height_of_box,s*height_of_box,Zodd_x,Zeven_x, Zo_x);
        }
      }
    }
    best_Zo=sqrt(best_Zo * best_Zeven);
    printf("Best results for two infinitly thin striplines of width s, separated by w\n");
    printf("and  placed centrally between two infinity wide parallel plates of height H is:\n");
    printf("H =%f w = %f s = %f which gives Zo = %f Zodd = %f Zeven = %f\n",height_of_box, height_of_box*best_w, height_of_box*best_s, best_Zo, best_Zodd, best_Zeven);
    }
    exit(0);
}
