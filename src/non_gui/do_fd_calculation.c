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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern int verbose;
extern int append_flag;
extern double found_this_dielectric; 

void do_fd_calculation(double *capacitance, double *inductance, double *Zo, double *Zodd, double *Zeven, int whichZ, double *velocity,double *vf,FILE *where_to_print, double cutoff, int dielectrics_to_consider_just_now, char * filename ,
int a_requirement_for_fd_calculations_Q)
{
  double c_old, c, impedance;
  FILE *appendfile_fp;
  char *appendfile;
  appendfile=(char *) malloc(100);
  
    *capacitance=VERY_LARGE; /* Can be anything large */
    do /* Start a finite calculation */
    {
      c_old=*capacitance; 

      /* Calculate the capacitance, using 100 iterations in a finite
      difference loop. There are two routines called finite_difference,
      one in the file finite_difference_multi_threaded.c and another 
      in the file finite_difference_single_threaded.c. The function has
      the same name in each, but is difference, depending on whether or
      not the programme is using multiple processors */
      *capacitance=finite_difference(100);
      if(dielectrics_to_consider_just_now == 1)
        *inductance=MU_0*EPSILON_0/(*capacitance);
      /* Once the capacitance is know, we can calculate L, Zo  and the
      velocity of propogation */
      impedance=sqrt((*inductance)/(*capacitance));
      *velocity=1.0/pow((*inductance)*(*capacitance),0.5);
      c=1.0/(sqrt(MU_0 * EPSILON_0)); /* approx 3x10^8 m/s */
      *vf=(*velocity)/c;  /* Velocity factor */

      /* If the -v option is given on the command line, more data is
      produced */
      
      if(whichZ==Z0)  
	*Zo=impedance;
      else if(whichZ==Z_ODD)
        *Zodd=impedance;
      /* In this case Zodd is alreadly known, so Zeven must be
      calculated, but also Zo, which is the geometric mean of the two
      */
      else if (whichZ==Z_ALL)
      {
	*Zeven=impedance;
        *Zo=sqrt((*Zodd)*(*Zeven));
      }
      if(verbose)
      {
        print_data(stdout,filename,1.0,*capacitance,*inductance,*Zo,*Zodd,*Zeven,whichZ,\
	  *velocity,*vf);
        if(append_flag==TRUE)
        {
           appendfile_fp=fopen(appendfile,"a");
	   if(appendfile_fp==NULL)
	   {
	     fprintf(stderr,"Error #6. Can't open file for appending data in atlc.c\n");
	     exit(6);
           }
	   print_data(appendfile_fp,filename,1.0,*capacitance,\
	   *inductance,*Zo,*Zodd,*Zeven,whichZ,*velocity,*vf);
           fclose(appendfile_fp);
	}
      }
    } while (fabs((c_old-*capacitance)/c_old) > cutoff); /* end of FD loop */
}
