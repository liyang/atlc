#ifndef ENABLE_MP

#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif 

#include "definitions.h"


extern int width, height;
extern double **Vij, **Er;
extern int  **cell_type;
extern int dielectrics_to_consider_just_now;
extern double r; 
extern int coupler;

#include "exit_codes.h"

double finite_difference_single_threaded()
{
  int i, j, iteration, type;
  int number_of_iterations=100;
  int start_column, end_column;
  double capacitance_per_metre, energy_per_metre;
  double a, b, c, d, e, f, g, h;
  double **V_to, **V_from;

  V_to=Vij;
  V_from=Vij;


  /* The following might not look very neat, with a whole load of code being 
  written twice, when it would be posible to make it easier to read if the 
  'if(dielectrics_in_bitmap > 1)' was in an inner loop. However, the 
  following is almost certainly more efficient. It is not a good idea to 
  have any more than necessary in the inner loop. 

  The option to avoid the faster convergence algorithm has been didtched
  too, as this was in an inner loop. The faster covergence method seems
  to work fine, so there is no need to avoid using it */
  
  start_column=0; 
  end_column=width-1;

  for(iteration=1; iteration<=number_of_iterations/4; ++iteration) {

#define LOOP_ORDER_A
#include "update_voltage_array.c"
#undef LOOP_ORDER_A

#define LOOP_ORDER_B
#include "update_voltage_array.c"
#undef LOOP_ORDER_B

#define LOOP_ORDER_C
#include "update_voltage_array.c"
#undef LOOP_ORDER_C

#define LOOP_ORDER_D
#include "update_voltage_array.c"
#undef LOOP_ORDER_D

  }
  /* Once the voltage distribution is found, the energy in the field may be 
  OP_ORDER=B
  found. This can be shown to be Energy = 0.5 * integral(E.D) dV, when 
  integrated over a volume V, and D.E is the vector dot product of E and
  D. 
  
  Energy per metre is 0.5 * D.E or (0.5*Epsilon)* E.E. Now E.E is given
  by Ex^2 + Ey^2 (by definition of a dot product. */

  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
    { 
      energy_per_metre+=find_energy_per_metre(i,j);
    }
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
#endif /* #endif to #ifndef ENABLE_MP */

