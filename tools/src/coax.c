/*
atlc - arbitrary transmission line calculator, for the analysis of
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

Dr. David Kirkby, e-mail drkirkby at ntlworld.com 

*/


/* coax finds the properties of a standard coaxial cable - useful as a test for atlc */

#include "config.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#define MU_0 4*M_PI*1e-7
#define EPSILON_0 8.854187817e-12 /* Data taken from NPL */


int main (int argc, char **argv)
{
  double velocity, velocity_factor, r0, r1, er, c, l, zo;

  if (argc != 4)
  {
    fprintf(stderr,"Find properties of a coaxial cable \n\n");

    fprintf(stderr,"                              *****************\n"); 
    fprintf(stderr,"                          ****                 ****\n");                        
    fprintf(stderr,"                       ****                       ****\n");                     
    fprintf(stderr,"                     ***                             ***\n");                   
    fprintf(stderr,"                   ***                                 ***\n");                 
    fprintf(stderr,"                 ***                                     ***\n");               
    fprintf(stderr,"                ***                                       ***\n");              
    fprintf(stderr,"               ***                                         ***\n");             
    fprintf(stderr,"              ***                                           ***\n");            
    fprintf(stderr,"             ***                     ***                     ***\n");           
    fprintf(stderr,"             **                    *******                    **\n");           
    fprintf(stderr,"            ***                   *********                   ***\n");          
    fprintf(stderr,"            **         Er        ***********                   **\n");          
    fprintf(stderr,"            *                    ***********                    *\n");          
    fprintf(stderr,"            **                    *********                    **\n");          
    fprintf(stderr,"            **                     *******                     **\n");          
    fprintf(stderr,"            **                       ****                      **\n");          
    fprintf(stderr,"            ***                                               ***\n");          
    fprintf(stderr,"             **                                               **\n");           
    fprintf(stderr,"             ***                                             ***\n");           
    fprintf(stderr,"              **                 <----d--->                  **\n");            
    fprintf(stderr,"               **                                           **\n");             
    fprintf(stderr,"                **                                         **\n");              
    fprintf(stderr,"                 ***                                     ***\n");               
    fprintf(stderr,"                  ****                                 ****\n");                
    fprintf(stderr,"                    ****                             ****\n");                  
    fprintf(stderr,"                      *****                       *****\n");                    
    fprintf(stderr,"                         ******               ******\n");                       
    fprintf(stderr,"                             *******************\n");                           
    fprintf(stderr,"                                     ***\n\n");
    fprintf(stderr,"             <------------------------D----------------------->\n\n");
    fprintf(stderr,"Usage: coax d  D Er\n");
    fprintf(stderr,"dualcoax %s: arguments are:\n",PACKAGE_VERSION);
    fprintf(stderr,"       d  is the diameter of the inner conductor\n"); 
    fprintf(stderr,"       D  is the inner diameter of the outer conductor\n"); 
    fprintf(stderr,"       Er is the permittivity of the dielectric\n"); 
    exit(1);
  }
  r0=atof(argv[1])/2.0;
  r1=atof(argv[2])/2.0;
  er=atof(argv[3]);
  if ( r0 >= r1){
    fprintf(stderr,"Sorry, the diameter of the inner conductor (d) must be\n");
    fprintf(stderr,"less than the inner diameter of the outer conductor (D)\n");
    exit(1);
  }
  if (er < 1.0 ){
    fprintf(stderr,"Sorry, the permittivity of the dielectric Er must be >=1");
    exit(1);
  }
  c=2*M_PI*er*EPSILON_0/log(r1/r0);
  l=MU_0*log(r1/r0)/(2*M_PI);
  zo=sqrt(l/c);
  velocity_factor=1/sqrt(er);
  velocity=velocity_factor/(sqrt(MU_0 * EPSILON_0));
  printf("Zo = %8.3f Ohms C= %8.3f pF/m L= %8.3f nH/m v= %g m/s v_f= %8.6f\n", zo,c*1e12,l*1e9, velocity, velocity_factor);
  return(0);

}
