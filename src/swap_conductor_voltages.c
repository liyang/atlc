/* When calculationg the properties of couplers it is necessary to swap
around the voltages on the conductors. First we consider the voltages as
present, which will be positive and negative. Next the negative pixels
must be changed to positive, to calculate the even mode impedance. This
routine does the swapping around, based on the value of the parameter
cell_type, which will be set to CONDUCTOR_PLUS_ONE_V or

CONDUCTOR_MINUS_ONE_V in definitions.h */

#include "definitions.h"

extern int width, height, **cell_type;
extern double **Vij;
extern int **cell_type;

void swap_conductor_voltages(int way_to_swap)
{
  int i, j, pixel;
  for(i=0;i<width;++i)
  {
    for(j=0;j<height;++j)
    {
      pixel=cell_type[i][j];
      if(way_to_swap==NEG_TO_POS && pixel==CONDUCTOR_MINUS_ONE_V)
        Vij[i][j]=+1.0;
      else if(way_to_swap==NEG_TO_POS && pixel >= 0)
        Vij[i][j]=0.0;
      else if(way_to_swap==POS_TO_NEG && pixel==CONDUCTOR_PLUS_ONE_V)
        Vij[i][j]=-1.0;
      else if(way_to_swap==POS_TO_NEG && pixel >= 0)
        Vij[i][j]=0.0;
    }
  }
}
