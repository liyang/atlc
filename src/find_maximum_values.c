#include "definitions.h"

extern int width, height, **cell_type;
extern double **Er, **Vij;

void find_maximum_values(struct max_values *maximum_values)
{
  double U, V, Ex, Ey, E, permittivity;
  int i, j;
  maximum_values->E_max=0.0;
  maximum_values->Ex_or_Ey_max=0.0;
  maximum_values->V_max=0.0;
  maximum_values->U_max=0.0;
  maximum_values->permittivity_max=0.0;
  for(i=0;i<width;++i)
  {
    for(j=0;j<height;++j)
    {
      V=Vij[i][j];
      U=find_energy_per_metre(i,j);
      if(cell_type[i][j]>=DIELECTRIC)
      {
	if(i==0)       
	  Ex=2*Er[i+1][j]*(Vij[i][j]-Vij[i+1][j])/(Er[i+1][j]+Er[i][j]);
        else if (i==width-1) 
    	  Ex=2*Er[i-1][j]*(Vij[i-1][j]-Vij[i][j])/(Er[i-1][j]+Er[i][j]);
        else /* This is the best estimate, but can't be done on boundary */
	{
    	  Ex=Er[i-1][j]*(Vij[i-1][j]-Vij[i][j])/(Er[i-1][j]+Er[i][j]);
	  Ex+=Er[i+1][j]*(Vij[i][j]-Vij[i+1][j])/(Er[i+1][j]+Er[i][j]);
        }
	if(j==0)
	  Ey=2*Er[i][j+1]*(Vij[i][j]-Vij[i][j+1])/(Er[i][j+1]+Er[i][j]);
	else if (j==height-1)
	  Ey=2*Er[i][j-1]*(Vij[i][j-1]-Vij[i][j])/(Er[i][j-1]+Er[i][j]);
	else
	{
	  Ey=Er[i][j-1]*(Vij[i][j-1]-Vij[i][j])/(Er[i][j-1]+Er[i][j]);
	  Ey+=Er[i][j+1]*(Vij[i][j]-Vij[i][j+1])/(Er[i][j+1]+Er[i][j]);
        }
        E=sqrt(Ex*Ex+Ey*Ey);
        permittivity=Er[i][j];
      }
      else
      {
        Ex=0;
	Ey=0;
	E=0;
	permittivity=0;
      }
      if(U> 1.0)             
        printf("U=%f v=%f Er=%f at %d %d\n",U,V,Er[i][j],i, j);

      if(E>maximum_values->E_max)
        maximum_values->E_max=E;

      if(fabs(Ex) > maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ex);

      if(fabs(Ey)>maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ey);
      if(fabs(Ex)>maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ex);
      if(fabs(Ey)>maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ey);
      if(fabs(V) > maximum_values->V_max)
        maximum_values->V_max=fabs(V); 
      if(U > maximum_values->U_max)
        maximum_values->U_max=U; 
      if(permittivity >maximum_values->permittivity_max )
      {
        maximum_values->permittivity_max=permittivity; 
      }
    }
  }
}
