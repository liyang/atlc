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

Dr. David Kirkby, e-mail drkirkby at ntlworld.com 

*/
#include "config.h"
#include <stdlib.h>
#include "definitions.h"

extern int width, height;
extern double **Vij, **Er;
extern signed char **oddity;
extern int dielectrics_to_consider_just_now;
extern double r; 

extern int coupler;

double finite_difference_single_threaded()
{
  int i, j, iteration;
  double capacitance_per_metre, energy_per_metre;
  double Vnew;

  /* The following symbols, Va, Vb, Vc, Vd and Ke have the same meaning as
  the do in the following paper:
  "The Numerical Solution ot Some Important Transmission-Line Problems"
  Harry E. Green, IEEE Transactions on Microwave Theory and Techniques, 
  VOL MITT-13, Number 5, pp 676-692, September 1965 */
  
  double Va, Vb, Vc, Vd, Ke;
  Va=0.5; Vb=0.5; Vc=0.5; Vd=0.5;

  for (iteration = 1; iteration <= ITERATIONS; iteration++){
    for(i=0; i < width; ++i){
      for(j=0; j < height; ++j){
        
        /* The voltage at the point (io,j) is computed in the manner described
        in the paper:

        "The Numerical Solution ot Some Important Transmission-Line Problems"
        Harry E. Green, IEEE Transactions on Microwave Theory and Techniques, 
        VOL MITT-13, Number 5, pp 676-692, September 1965.

        At an ordinary point, not near any corners, edges, changes of 
        dielectric etc, the new voltage at a point i,j is just given by
        Vnew=(Va+Vb+Vc+Vd)/4.0, but near edges, corners, changes of 
        dielectric this is not so and other equations must be used. There
        are 29 cases (28 + the ordinary one) which are numbered 1 to 29
        in Green's paper. The numbering used here is the same as in Green's
        paper. Obviously if the voltage is fixed, no changes must be made, so
        those cases are first tested. */


	if( i > 0)
          Va=Vij[i-1][j]; 
        if( i < width-1)
          Vb=Vij[i+1][j];
        if( j >  0 )
          Vc=Vij[i][j-1];
        if ( j < height-1 )
          Vd=Vij[i][j+1];
        Ke=Er[i][j];
   
        if( oddity[i][j] == CONDUCTOR_ZERO_V)
          Vnew=0.0;
        else if (oddity[i][j] == CONDUCTOR_PLUS_ONE_V)
          Vnew=1.0;
        else if (oddity[i][j] == CONDUCTOR_MINUS_ONE_V )
          Vnew=-1.0;

#ifdef ONE
        /* This is the normal equation valid in an interior node */
        else if(oddity[i][j] == ORDINARY_INTERIOR_POINT)  /* 1 */
          Vnew=(Va+Vb+Vc+Vd)/4.0;
#endif

#ifdef TWO
        else if (oddity[i][j] == ORDINARY_POINT_BOTTOM_EDGE)  /* 2 */
          Vnew=(Va+Vb+2*Vd)/4.0;
#endif

#ifdef THREE
        else if (oddity[i][j] == ORDINARY_POINT_TOP_EDGE) /* 3 */
          Vnew=(Vb+Va+2*Vc)/4.0;
#endif

#ifdef FOUR
        else if (oddity[i][j] == ORDINARY_POINT_LEFT_HAND_EDGE) /* 4 */
          Vnew=(Vd+Vc+2*Vb)/4.0;
#endif

#ifdef FIVE
        else if (oddity[i][j] == ORDINARY_POINT_RIGHT_HAND_EDGE) /* 5 */
          Vnew=(Vc+Vd+2*Va)/4.0;
#endif

#ifdef SIX
        else if (oddity[i][j] == CORNER_POINT_BOTTOM_LEFT_HAND_EDGE) /* 6 */
          Vnew=(Vb+Vd)/2.0;
#endif

#ifdef SEVEN
        else if (oddity[i][j] == CORNER_POINT_BOTTOM_RIGHT_HAND_EDGE) /* 7 */
          Vnew=(Va+Vd)/2.0;
#endif

#ifdef EIGHT 
        else if (oddity[i][j] == CORNER_POINT_TOP_LEFT_HAND_EDGE) /* 8 */
          Vnew=(Vb+Vc)/2.0;
#endif

#ifdef NINE
        else if (oddity[i][j] == CORNER_POINT_TOP_RIGHT_HAND_EDGE) /* 9 */
          Vnew=(Va+Vc)/2.0;
#endif

#ifdef TEN
        else if (oddity[i][j] == DIELECTRIC_ROW_INTERFACE_DIELECTRIC_TO_TOP ) /* 10 */
          Vnew=( (1+Ke)*Va+(1+Ke)*Vb+2*Vc+2*Ke*Vd )/(4*(1+Ke));
#endif

#ifdef ELEVEN
        else if (oddity[i][j] == DIELECTRIC_ROW_INTERFACE_DIELECTRIC_TO_BOTTOM ) /* 11 */
          Vnew=( (1+Ke)*Va+(1+Ke)*Vb+2*Vd+2*Ke*Vc )/(4*(1+Ke));
#endif

#ifdef TWELVE 
        else if (oddity[i][j] == DIELECTRIC_COLUMN_INTERFACE_DIELECTRIC_TO_LEFT_HAND_EDGE ) /* 12 */
          Vnew=( (1+Ke)*Vc+(1+Ke)*Vd+2*Vb+2*Ke*Va )/(4*(1+Ke));
#endif

#ifdef THIRTEEN
        else if (oddity[i][j] == DIELECTRIC_COLUMN_INTERFACE_DIELECTRIC_TO_RIGHT_HAND_EDGE ) /* 13 */
          Vnew=( (1+Ke)*Vd+(1+Ke)*Vc+2*Va+2*Ke*Vb )/(4*(1+Ke));
#endif

#ifdef FOURTEEN
        else if (oddity[i][j] == ANGLE_DIELECTRIC_ACUTE_FIRST_QUADRANT)
          Vnew=( 2*Va+(Ke+1)*Vb+2*Vc+(Ke+1)*Vd) / (2*(Ke+3));
#endif

#ifdef FIFTEEN
        else if (oddity[i][j] == ANGLE_DIELECTRIC_ACUTE_SECOND_QUADRANT)
          Vnew=( 2*Vc+(Ke+1)*Vd+2*Vb+(Ke+1)*Va) / (2*(Ke+3));
#endif

#ifdef SIXTEEN
        else if (oddity[i][j] == ANGLE_DIELECTRIC_ACUTE_THIRD_QUADRANT)
          Vnew=( 2*Vb+(Ke+1)*Va+2*Vd+(Ke+1)*Vc) / (2*(Ke+3));
#endif

#ifdef ggg
        else if (oddity[i][j] == ANGLE_DIELECTRIC_ACUTE_FOURTH_QUADRANT)
          Vnew=( 2*Vd+(Ke+1)*Vc+2*Va+(Ke+1)*Vd) / (2*(Ke+3));

        else if (oddity[i][j] == ANGLE_DIELECTRIC_OBTUSE_FIRST_QUADRANT)
          Vnew=( 2*Ke*Va + (Ke+1)*Vb + 2*Ke*Vc+(Ke+1)*Vd)/(2*(3*Ke+1));
        else if (oddity[i][j] == ANGLE_DIELECTRIC_OBTUSE_SECOND_QUADRANT)
          Vnew=( 2*Ke*Vc + (Ke+1)*Vd + 2*Ke*Vb+(Ke+1)*Va)/(2*(3*Ke+1));
        else if (oddity[i][j] == ANGLE_DIELECTRIC_OBTUSE_THIRD_QUADRANT)
          Vnew=( 2*Ke*Vb + (Ke+1)*Va + 2*Ke*Vd+(Ke+1)*Vc)/(2*(3*Ke+1));
        else if (oddity[i][j] == ANGLE_DIELECTRIC_OBTUSE_FOURTH_QUADRANT)
          Vnew=( 2*Ke*Vd + (Ke+1)*Vc + 2*Ke*Va+(Ke+1)*Vb)/(2*(3*Ke+1));

        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_BOTTOM_EDGE_DIELECTRIC_TO_LEFT_HAND_EDGE)
          Vnew=(-Ke*Va-Vb-(Ke+1)*Vd) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_BOTTOM_EDGE_DIELECTRIC_TO_RIGHT_HAND_EDGE)
          Vnew=(-Ke*Vb-Va-(Ke+1)*Vd) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_TOP_EDGE_DIELECTRIC_TO_LEFT_HAND_EDGE)    
          Vnew=(-Ke*Va-Vb-(Ke+1)*Vc) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_TOP_EDGE_DIELECTRIC_TO_RIGHT_HAND_EDGE)
          Vnew=(-Ke*Vb-Va-(Ke+1)*Vc) /(2*(Ke+1));

        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_LEFT_HAND_EDGE_DIELECTRIC_TO_TOP)        
          Vnew=(-Ke*Vd-Vc-(Ke+1)*Vb) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_LEFT_HAND_EDGE_DIELECTRIC_TO_BOTTOM)     
          Vnew=(-Ke*Vd-Vc-(Ke+1)*Vb) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_RIGHT_HAND_EDGE_DIELECTRIC_TO_TOP)       
          Vnew=(-Ke*Vc-Vd-(Ke+1)*Va) /(2*(Ke+1));
        else if (oddity[i][j] == DIELECTRIC_INTERFACE_TO_RIGHT_HAND_EDGE_DIELECTRIC_TO_BOTTOM)    
          Vnew=(-Ke*Vc-Vd-(Ke+1)*Va) /(2*(Ke+1));

#endif
        else{
	  Vnew=0;
	  fprintf(stderr,"oddity[%d][%d]=%d\n",i,j,oddity[i][j]);
	  exit_with_msg_and_exit_code("internal error in finite_difference_single_threaded.c",1);
        }
        Vij[i][j]=r*Vnew+(1-r)*Vij[i][j]; 
 /*         Vij[i][j]=Vnew; */
// #define DEBUG
#ifdef DEBUG
	if( Vnew > 1 || Vnew < 0.0 ) {
	  fprintf(stderr,"Internal error in finite_difference_single_threaded.c\n");
	  fprintf(stderr,"Vnew=%f i=%d j=%d oddity[i][j]=%d\n",Vnew,i,j,oddity[i][j]);
	  exit(1);
        }
#endif
      }
    }
  }
  /* Once the voltage distribution is found, the energy in the field may be 
  found. This can be shown to be Energy = 0.5 * integral(E.D) dV, when 
  integrated over a volume V, and D.E is the vector dot product of E and
  D. 
  
  Energy per metre is 0.5 * D.E or (0.5*Epsilon)* E.E. Now E.E is given
  by Ex^2 + Ey^2 (by definition of a dot product. */
  for(i=0;i<width;++i)
    for(j=0;j<height-1;++j){
      if(fabs(Vij[i][j]) > 1.0) {
	fprintf(stderr, "voltage is %f at %d,%d\n",Vij[i][j],i,j);
	fprintf(stderr,"Error in finite_difference_single_threaded()\n");  
	fprintf(stderr,"Reduce the value of r by using the option -r\n");  
	fprintf(stderr,"Try -r 1.7 and reduce if still  unstable.\n");  
	exit(1);
      }
    }


  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height-1;++j)
      energy_per_metre+=find_energy_per_metre(i,j);

  /* The capacitance C is relatated to the energy (U) by Energy=0.5*C*V^2 
  so C=2*U/(V^2). When there is a coupler, V is 2 V, not one, so the
  capciance C=0.5*U; */
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
