/*
The code below for calculating the voltage at a point i,j, given the
voltages and permittivities at the four adjacent points (i,j+1),
(i,j-1), (i-1,j), and (i+1,j), is I belive correct. However, it was
derrived by assuming 2 series  capacitors between each of the 4 centres
of the points and the point (i,j). The code is valid for any 
permittivity (I believe).

A document giving the proof may be found in the docs subdirecory, with
the name thoery.pdf

Here's the results from Mathematica, which was used to derrive the
equation for the new voltage v[i][j]

In[9]:= y=(eijm1*eij*(vijm1 - vij))/(eij + eijm1) 
+ (eijp1*eij*(vijp1 - vij))/(eij + eijp1) 
+ (eim1j*eij*(vim1j - vij))/(eij + eim1j) 
+ (eip1j*eij*(vip1j - vij))/(eij + eip1j)        

        eij eijm1 (-vij + vijm1)   eij eijp1 (-vij + vijp1)
Out[9]= ------------------------ + ------------------------ + 
              eij + eijm1                eij + eijp1
 
     eij eim1j (-vij + vim1j)   eij eip1j (-vij + vip1j)
>    ------------------------ + ------------------------
           eij + eim1j                eij + eip1j

In[10]:= Solve[y==0,vij]

Out[10]= {{vij -> 
 
         eij eijm1 vijm1   eij eijp1 vijp1   eij eim1j vim1j   eij eip1j vip1j
         --------------- + --------------- + --------------- + ---------------
           eij + eijm1       eij + eijp1       eij + eim1j      eij + eip1j
          
        ---------------------------------------------------------------------
                  eij eijm1      eij eijp1     eij eim1j     eij eip1j
                ----------- + ----------- + ----------- + -----------
                 eij + eijm1    eij + eijp1   eij + eim1j   eij + eip1j
 

The eij's can all be cancelled (FullSimplify[] does this)
*/


#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif 

#include "definitions.h"


extern int width, height;
extern double **Er;
extern unsigned char  **oddity;
extern int dielectrics_to_consider_just_now;
extern double r; 
extern int coupler;

#include "exit_codes.h"

/* The following function updates the voltage on the matrix V_to given data about the 
oddity of the location i,j and the voltages in the matrix V_from. It does this for n interations
between rows jmin and jmax inclusive and between columns imain and imax inclusive */

void update_voltage_array(int nmax, int imin, int imax, int jmin, int jmax, double **V_from, double **V_to)
{
  int k, i, j, n;  
  unsigned char oddity_value;
  double Va, Vb, Vc, Vd, ERa, ERb, ERc, ERd;
  double a, b, c, d, e, f, g, h;
  double vnew;

  for(n=0; n  < nmax; ++n)
    for(k=0; k < 4; ++k)
      for (i = k&1 ? imax : imin;   k&1 ? i >=imin : i <= imax ;  k&1 ? i-- : i++)
        for (j = (k==0 || k ==3) ? jmin : jmax; (k ==0 || k == 3)  ? j <= jmax : j >= jmin ; (k == 0 || k ==3) ?  j++ : j--){
        oddity_value=oddity[i][j];
        
        if(oddity_value == ORDINARY_INTERIOR_POINT)  {
          //V_to[i][j]=r*(V_from[i][j+1]+V_from[i+1][j]+V_from[i][j-1]+V_from[i-1][j])/4.0+(1-r)*V_from[i][j];
          vnew=(V_from[i][j+1]+V_from[i+1][j]+V_from[i][j-1]+V_from[i-1][j])/4.0;
        }
        else if (i > 1 && j > 0 && i < width-1 && j < height-1) {

        a=(Er[i][j-1] * V_from[i][j-1])/(Er[i][j] + Er[i][j-1]);
        b=(Er[i][j+1] * V_from[i][j+1])/(Er[i][j] + Er[i][j+1]);
        c=(Er[i-1][j] * V_from[i-1][j])/(Er[i][j] + Er[i-1][j]);
	d=(Er[i+1][j] * V_from[i+1][j])/(Er[i][j] + Er[i+1][j]);

        e=(Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
        f=(Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
        g=(Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
        h=(Er[i+1][j])/(Er[i][j]+Er[i+1][j]);


          Va=V_from[i-1][j]; 
          Vb=V_from[i+1][j];
          Vc=V_from[i][j+1];
          Vd=V_from[i][j-1];

          ERa=V_from[i-1][j]; 
          ERb=V_from[i+1][j];
          ERc=V_from[i][j+1];
          ERd=V_from[i][j-1];

          // V_to[i][j]=(Va+Vb)/4.0 + (Vb-Va)*(ERb-ERa)/(16*Er[i][j]) + (Vd+Vc)/4.0 + (Vc-Vd)*(ERc-ERd)/(16.0*Er[i][j]);
	  //V_to[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*V_from[i][j];
	  vnew=(a+b+c+d)/(e+f+g+h);
        }
	V_to[i][j]=r*vnew+(1-r)*V_from[i][j];

#define gg

#ifdef gg
        /* the following lines calculate the voltages at the edges and the corners */

        if( oddity_value == TOP_LEFT_CORNER ) {  /* top left */
          V_to[i][j]=0.5*(V_from[1][0]+V_from[0][1]);               
	  // printf("done top left corner %d %d \n",i,j);
        }
        else if( oddity_value == TOP_RIGHT_CORNER ) {
          V_to[i][j]=0.5*(V_from[width-2][0]+V_from[width-1][1]);         /* top right */
	  // printf("done top right corner %d %d \n",i,j);
        }

        else if(oddity_value == BOTTOM_LEFT_CORNER) {
          V_to[i][j]=0.5*(V_from[0][height-2]+V_from[1][height-1]);       /* bottom left */
	  // printf("done bottomleft corner %d %d \n",i,j);
        }

        else if( oddity_value == BOTTOM_RIGHT_CORNER) {   
          V_to[i][j]=0.5*(V_from[width-2][height-1]+V_from[width-1][height-2]); /* bottom right */
	  // printf("done bottom right corner %d %d \n",i,j);
        }

        /* Now the sides */

        else if( oddity_value == ORDINARY_POINT_LEFT_EDGE )  /* left hand side  */
          V_to[i][j]=0.25*(V_from[0][j-1]+V_from[0][j+1] + 2*V_from[1][j]);

        else if( oddity_value == ORDINARY_POINT_RIGHT_EDGE)   /* right hand side */
          V_to[i][j]=0.25*(V_from[width-1][j+1]+V_from[width-1][j-1]+2*V_from[width-2][j]);
        
        else if( oddity_value == ORDINARY_POINT_TOP_EDGE ){ /* top row */ 
          V_to[i][j]=0.25*(V_from[i-1][0]+V_from[i+1][0]+2*V_from[i][1]);
        }

        else if( oddity_value == ORDINARY_POINT_BOTTOM_EDGE ){   /* bottom row */ 
          V_to[i][j]=0.25*(V_from[i-1][height-1]+V_from[i+1][height-1]+2*V_from[i][height-2]);
        }


#endif

#ifdef metal
        /* Now those with metal around */ 
        else if( oddity_value == METAL_LEFT  ){   /* metal left */ 
          V_to[i][j]=0.50*(V_from[i-1][height]+V_from[i][height]);
        }
        else if( oddity_value == METAL_RIGHT  ){   /* metal right*/ 
          V_to[i][j]=0.50*(V_from[i-1][height]+V_from[i][height]);
        }
        else if( oddity_value == METAL_ABOVE  ){   /* metal above */ 
          V_to[i][j]=0.50*(V_from[i-1][height]+V_from[i][height]);
        }
        else if( oddity_value == METAL_BELOW  ){   /* metal below*/ 
          V_to[i][j]=0.50*(V_from[i-1][height]+V_from[i][height]);
        }
#endif
        
	else if ( oddity[i][j] == UNDEFINED_ODDITY)  {
          fprintf(stderr,"Internal error in update_voltage_array.c\n");
          fprintf(stderr,"i=%d j=%d oddity[%d][%d]=%d\n",i,j,i,j,oddity[i][j]);
          exit(INTERNAL_ERROR);
        } /* end if if an internal error */
      } /* end of j loop */
} 
