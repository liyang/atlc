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
 
*/

/*
void update_voltage_array(int start_row, int end_row, double **V_from, double **V_to)
{
  int i, j, type;
  double a, b, c, d, e, f, g, h;
*/

#ifdef LOOP_ORDER_A
  for(i= start_column; i <=end_column; ++i){
    for(j=0; j<=height-1; ++j) {
#endif

#ifdef LOOP_ORDER_B
  for(i= end_column; i >=start_column; --i){
    for(j=0; j<=height-1; ++j) {
#endif

#ifdef LOOP_ORDER_C
  for(i= start_column; i <=end_column; ++i){
    for(j=height-1; j>=0; --j) {
#endif

#ifdef LOOP_ORDER_D
  for(i= end_column; i >=start_column; --i){
    for(j=height-1; j>=0; --j) {
#endif
      type = cell_type[i][j];
      if(type >=DIELECTRIC) { /*only update dielectrics, not conductors*/
	/* normal internal position, dielectric */
        if(type == DIELECTRIC && i > 0 && j > 0 && i < width-1 && j < width-1)
          V_to[i][j]=r*(V_from[i][j+1]+V_from[i+1][j]+V_from[i][j-1]+V_from[i-1][j])/4.0+(1-r)*V_from[i][j];
	  /* normal internal position, but non-uniform dielectric */
        else if( i > 0 && j > 0 && i < width-1 && j < width-1 && type != DIELECTRIC) {
          a=(Er[i][j] * Er[i][j-1] * V_from[i][j-1])/(Er[i][j] + Er[i][j-1]);
          b=(Er[i][j] * Er[i][j+1] * V_from[i][j+1])/(Er[i][j] + Er[i][j+1]);
          c=(Er[i][j] * Er[i-1][j] * V_from[i-1][j])/(Er[i][j] + Er[i-1][j]);
          d=(Er[i][j] * Er[i+1][j] * V_from[i+1][j])/(Er[i][j] + Er[i+1][j]);
     
          e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
          f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
          g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
          h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
          V_to[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*V_from[i][j];
        }
        /* the following few lines calculate the voltages at the edges.
        They are not accurate, but better than no calculation at all 


        if(i==1 && cell_type[0][j]>=0)
          Vij[0][j]=(Vij[0][j+1]+Vij[0][j-1])/2.0; 
        if(i==width-2 && cell_type[width-1][j] >= DIELECTRIC)
          Vij[width-1][j]=(Vij[width-1][j+1]+Vij[width-1][j-1])/2.0;
        if(j==1 && cell_type[i][0]>=0)
          Vij[i][0]=(Vij[i][j-1]+Vij[i][j+1])/2.0;
        if(j==height-2 && cell_type[i][width-1]>=DIELECTRIC)
          Vij[i][height-1]=(Vij[i][j-1]+Vij[i][j+1])/2.0; */

	else if( i == 0 && j == 0 && cell_type[i][j] >= DIELECTRIC) /* top left */
	{
          V_to[i][j]=(V_from[1][0]+V_from[0][1])/2.0;                                        /* top left  */
        }
	else if ( i == width-1 && j == 0 && cell_type[i][j] >= DIELECTRIC) {
          V_to[i][j]=(V_from[width-2][0]+V_from[width-1][1])/2.0;                      /* top right */
        }
        else if(i == 0 && j == height-1 && cell_type[i][j] >= DIELECTRIC){
          V_to[i][j]=(V_from[0][height-2]+V_from[1][height-1])/2.0;                   /* bottom left */
        }
	else if( i == width-1 && j == width-1 && cell_type[i][j] >= DIELECTRIC){
          V_to[i][j]=(V_from[width-2][height-1]+V_from[width-1][height-2])/2.0; /* bottom right */
	}

	else if( i == 0 && j > 0 && j < height-1 && cell_type[i][j] >= DIELECTRIC) { /* left hand side  */
	  V_to[i][j]=0.25*(V_from[0][j-1]+V_from[0][j+1] + 2*V_from[1][j]);
        }

	else if( i == width-1 && j > 0 && j < height-1 && cell_type[i][j] >= DIELECTRIC){                              /* right hand side */
	  V_to[i][j]=0.25*(V_from[width-1][j+1]+V_from[width-1][j-1]+2*V_from[width-2][j]);
        }
        
	else if( j == 0 && i > 0 &&  i < width-1 && cell_type[i][j] >= DIELECTRIC){                                   /* top row */ 
	  V_to[i][j]=0.25*(V_from[i-1][0]+V_from[i+1][0]+2*V_from[i][1]);
        }

	else if( j == height-1 && i > 0 &&  i < width-1 && cell_type[i][j] >= DIELECTRIC){                            /* bottom row */ 
	  V_to[i][j]=0.25*(V_from[i-1][height-1]+V_from[i+1][height-1]+2*V_from[i][height-2]);
        }
	else {
	  fprintf(stderr,"Internal error in update_voltage_array.c\n");
	  fprintf(stderr,"i=%d j=%d cell_type[%d][%d]=%d\n",i,j,i,j,cell_type[i][j]);
	  exit(INTERNAL_ERROR);
        }
      }
    }
  }
/* } */
