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
  int q, Hflag=FALSE;
  int calculate_physical_dimensions=FALSE;
  double er, Zo=-1, length=-1, fmin, fmax, fmean, fstep=-1, cf,  Zodd, Zeven; 
  double f, vcf, vcf_for_quarter_wave_line, w, s, error, error_max=1e30;
  double wanted_coupling_factor_in_dB, step=0.02, fq;
  double Zo_x=-1, Zeven_x=-1, Zodd_x=-1, best_s=-1, best_w=-1, height_of_box=1.0;
  double best_Zodd=-1, best_Zeven=-1, best_Zo=-1;
  while((q=get_options(argc,argv,"dCL:s:Z:H:")) != -1)
  switch (q) 
  {
    case 'd':
    calculate_physical_dimensions=TRUE;
    break;
    case 'C':
    print_copyright((char *) "2002");
    exit(1);
    break;
    case 'L':
    length=atof(my_optarg);
    break;
    case 'H':
    height_of_box=atof(my_optarg);
    Hflag=TRUE;
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
  
  /* vfc stands for 'voltage coupling factor' */

  /* When the line is a quarter wave, one can get any amount of coupling
  you want, including a vfc of 1, in which case all the power transfers
  to the coupled port. Normally, the vcf will be less than 1.0. for a 20
  dB couplier is it 0.1 */

  vcf_for_quarter_wave_line=1.0/pow(10,wanted_coupling_factor_in_dB/20.0); 

  fq=75/length; /* frequency at which line is a quarter wave long */

  /* If the line is less than a quarter wave long, then less power is
  coupled, so to compensate we need to increase the voltage coupling
  factor 'vcf above that of the value for a quarter wave line.
  Since the 'vcf' varies as sin(0.5 *PI * f/fq)^2, where 
  fq is the frequency at which the line is a quarter-wave long, we must
  divide the vcf_for_quarter_wave_line by sin(0.5 *PI*f/fq)^2 to get
  the required vcf. */

  vcf=vcf_for_quarter_wave_line/pow(sin(0.5*M_PI*fmean/fq),2.0);
  
  /* Check that the voltage coupling factor does not exceed one */
  if ( vcf > 1.0 )
  {
    fprintf(stderr,"\n*****ERROR****\n");
    fprintf(stderr,"Sorry, you can't make a %6.3f dB coupler with a coupled line of %7.4f m long.\n",wanted_coupling_factor_in_dB, length);
    fprintf(stderr,"Either couple off a smaller fraction of the main power to the coupled port,\n");
    fprintf(stderr,"or make the line closer to an odd multiple of a quarter wave.\n");
    fprintf(stderr,"Odd mulitples of a quarter wave are: %.4f, %.4f, %.4f, %.4f .. m\n", 75/fmean, 3*75/fmean, 5*75/fmean, 7*75/fmean);
    exit(1);
  }

  /* After mucking around with Mathematica a bit, I found it was
  possible to invert the equations */
  
  Zodd = sqrt(1-vcf)*Zo/sqrt(1+vcf);
  Zeven=Zo*Zo/Zodd;

  printf("\nFor a %.3f dB %.3f Ohm coupler with a length of %.4f m,\n",wanted_coupling_factor_in_dB, Zo, length);
  printf("you need to have an odd-mode impedance Zodd to be %.3f Ohms and \n",Zodd);
  printf("an even mode impedance Zeven to be %.3f Ohms\n\n",Zeven);
  printf("%7.3f dB down <-- ************************** ---> %3.3f Ohm termination\n\n",wanted_coupling_factor_in_dB,Zo);
  printf("Drive this port --> ************************** ---> %3.3f Ohm termination\n",Zo);
  printf("                    <------- %8.4f m ----->\n",length);
  printf("\nDrive Port 1, coupler out of port 2 and terminate the other ports in Zo\n");
  printf("Such a coupler will have the response indicated below.\n\n");
  //printf("length =%.4f mean=%.3f vcf=%.3f vcf_for_quarter_wave_line=%.3f \n",length, fmean, vcf, vcf_for_quarter_wave_line);
  for(f=fmin; f<=fmax; f+=fstep)
  {
    cf=20*log10(vcf*pow(sin(0.5*M_PI*f/fq),2.0) ); /* This is what is now needed for some given length (and so fq) */
    printf("frequency = %.3f MHz coupling is %.3f dB down on the main arm\n",f,cf);
  }
  printf("\nYou may force the length to be any value you want using the -L option - it does\nnot have to be %.4f metres long\n",length);
  if(calculate_physical_dimensions==FALSE)
  {
    printf("You may try to find a coupler with these dimensions using the -d option\n\n");
    printf("Currently the -d option is not that fast, as it uses a brain-dead algorithm\n");
    printf("Hopefully one day the algorithm will be speeded up.\n");
  }
  if(calculate_physical_dimensions==TRUE)
  {
    er=1.0;
    printf("Please be patient - this will take a few minutes or so\n");
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
        }
      }
    }
    //printf("w = %.4f s = %.4f which gives Zo = %.4f Zodd = %.4f Zeven = %.4f\n",best_w, best_s, best_Zo, best_Zodd, best_Zeven);
    /* Now try to get closer */
    /*
    for(s = best_s-step; s<=best_s+step; s+=step/1000)
    {
      for(w = best_w-step; w<= best_w+step; w += step/1000)
      {
        calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, 1.0, s, er);
	error=fabs(Zodd-Zodd_x) + fabs(Zeven-Zeven_x);
	if( error < error_max )
	{
	  best_s=s; 
	  best_w=w; 
	  best_Zodd=Zodd;
	  best_Zeven=Zeven;
	  error_max=error;
        }
      }
    }
    */
    best_Zo=sqrt(best_Zodd * best_Zeven);

    printf("|-----------^------------------------------------------------------------------|\n");
    printf("|           |                                                                  |\n");
    printf("|           |              <---w---><-----s----><---w-->                       |\n");
    printf("|           H              ---------            --------                       |\n");
    printf("|           |                                                                  |\n");
    printf("|           |   Er=1.0 (air)                                                   |\n");
    printf("------------v------------------------------------------------------------------\n");
    printf("<-----------------------------------------W----------------------------------->\n");
    printf("H =%.4f w = %.4f s = %.4f\n",height_of_box, height_of_box*best_w, height_of_box*best_s);
    printf("W must be *at least* %.4f, but larger does not matter.\n",5*height_of_box+ 2*best_w*height_of_box + height_of_box*best_s);
    printf("These dimensions give Zo = %.4f Zodd = %.4f Zeven = %.4f Ohms\n", best_Zo, best_Zodd, best_Zeven);
    if(Hflag==FALSE)
    {
      printf("****NOTE ****\n");
      printf("Although H is shown as 1.0, it can be 1 mm, 1 cm or even 1 m. It is important\n");
      printf("that w is %.4f times whatever H is, and that s is %.4f times whatever H is, but the absolute numbers are irrelavant.\n",best_w, best_s);
      printf("If you know the height H of your enclosure, use the -H option to indicate\n");
      printf("its value. This will ensure all the dimensions are scaled automatically for you.\n"); 
    }
    printf("****NOTE 2****\n");
    printf("The length *must* be %.4f m if you use these dimensions for W, H, w and s.\n",length); 
    printf("If %.4f m is inconvenient, change it with the -L option and recalculate\n to get new values of W, H, w and s\n",length);
    printf("See: http://atlc.sourceforge.net\n");
    printf("See: http://atlc.sourceforge.net/couplers.html\n");
  }
  exit(0);
}
