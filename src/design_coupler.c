/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

extern int errno;
int verbose=FALSE;

extern int main(int argc, char **argv) /* Read parameters from command line */
{
  int q;
  double Zo=-1, length=-1, fmin, fmax, fstep=-1, cf, c, Zodd, Zeven; 
  double quarter_wave;
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

  if(argc-my_optind != 4)  /* This should be so hopefully !! */
  {
    usage_design_coupler();
    exit(1);
  }
  cf=atof(argv[my_optind]);
  fmin=atof(argv[my_optind+1]);
  fmax=atof(argv[my_optind+2]);
  if (cf < 0.0 )
  {
    fprintf(stderr,"Enter the coupling factor as a positive number\n");
    exit(1);
  } 
  if (fmax <= fmin)
  {
    fprintf(stderr,"fmax <= fmin\n");
    exit(2);
  }
  quarter_wave=150.0/(fmax+fmin);
  if(length < 0)          /* by default assume a quarter wave */
    length=quarter_wave;
  if (Zo < 0.0)
    Zo=50.0; 
  /* The following sent in an email by Paul AA1L, sums the theory up 
  You make Zo=50=sqrt(Zoo*Zoe) and
  c=(Zoe-Zoo)/(Zoe+Zoo), c being the voltage coupling coefficient.
  I.e., for a 20dB coupler c=0.1 is the midband
  coupling.  

  Coupling varies as sin^2(f/fq), fq being frequency where the coupled
  length is a quarter wave.  
  */

  /* I need to find values for Zodd and Zeven to use, but first convert
  the coupling factor on the command line into the voltage coupling
  factor c */

  c=1.0/pow(10,cf/20.0);

  /* After mucking around with Mathematica a bit, I found it was
  possible to invert the equations */

  Zodd = sqrt(1-c)*Zo/sqrt(1+c);
  Zeven=Zo*Zo/Zodd;
  printf("Zo= %f Zodd= %f Zeven= %f length= %f\n",Zo, Zodd, Zeven,quarter_wave);
  printf("You may force the length to be any value you want using the -l option\n");
  exit(0);
}
