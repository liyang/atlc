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
#define SLOW

#ifndef ENABLE_POSIX_THREADS 

/* If we are not comiling for multi-threaded use, a function
is defined, but it is not used. This keeps the linker happy */

double finite_difference_multi_threaded(int number_of_iterations)
{
  return(0.0);
}
#endif


#ifdef ENABLE_POSIX_THREADS 

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_SEMAPHORE_H
#include <semaphore.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <pthread.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

extern int coupler;
extern int width, height;
extern double **Vij, **Vij2, **Er;
extern char **cell_type;
extern int dielectrics_to_consider_just_now;
extern int number_of_workers; 
extern int errno;


/* The algorithm for this is based on one in the book 'Foundations of Multithraded, 
Parallel and Distributed Programming' by G. A. Andrews, (2000). Especially 
chapter 11, Fig 11.6, "Red/Black Gauss-Seidel using shared vairables'. 

Basically the array is a considered a chess board. Since we only use in the computation the
values above, below, to the left and the right of the current pixel, these will all be the
same colour on the chess board (black or white). So we compute all the white squares, which
can all be done in parallel, since they don't depend on each other. Once the white squares
are done, the black ones can be done. Again, these don't depend on the white squares, but
only the black ones. So the algorithm does

1) Covers the array with a large chess board with black and white squares. 


B W B W B W B W B W B W B W B W B W B W B W B W B W B W
W B W B W B W B W B W B W B W B W B W B W B W B W B W B
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B


2) Split the array into a number of columns, one for each CPU.

B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B

3) Do all columns in parallel on the black squares. 

B   B   B   B     B   B   B     B   B   B   B     B   B   B  
  B   B   B     B   B   B   B     B   B   B     B   B   B   B
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B

Thread 0          Thread 1        Thread 2         Thread 3

4) Wait until all the black squares are done.

5) Compute all the white squares in parallel. 

  W   W   W     W   W   W   W     W   W   W     W   W   W   W
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
Thread 0          Thread 1        Thread 2         Thread 3


6) Repeat a large number (typically 100) times. 

7) Check for convergence. 

8) Stop if the solution has converged. 
*/

extern double r;

pthread_mutex_t barrier;  /* mutex semaphore for the barrier */
pthread_cond_t go;        /* condition variable for leaving */
int numArrived = 0;       /* count of the number who have arrived */

void Barrier() {
  pthread_mutex_lock(&barrier);
  numArrived++;
  if (numArrived == number_of_workers) {
    numArrived = 0;
    pthread_cond_broadcast(&go);
  } else
    pthread_cond_wait(&go, &barrier);
  pthread_mutex_unlock(&barrier);
}


/* Each Worker computes values in one strip of the grids.
   The main worker loop does two computations to avoid copying from
   one grid to the other.  */

void *worker(void *arg) {
  int myid = (int) arg;
  double maxdiff, temp, r_over_4,a,b,c,d,e,f,g,h;
  double one_minus_r;
  int i, j, iters, jstart;
  int firstcol, lastcol;
  int strip_width=width/number_of_workers;

  firstcol = myid*strip_width+1;
  lastcol = firstcol + strip_width - 1;
  r_over_4=r/4.0;
  one_minus_r=1-r;
  if(myid == number_of_workers -1) 
    lastcol=width-2;
  // printf("firstcol=%d lastcol=%d width=%d height=%d \n",firstcol,lastcol,width,height);
  Barrier();
  for (iters = 1; iters <= ITERATIONS; iters++) 
  {
    for(i= firstcol ; i <= lastcol; ++i){
      if(i%2 ==1 )
	jstart=1;
      else
	jstart=2;
      for(j=jstart ; j < height-1 ; j+=2){
        if(cell_type[i][j] == DIELECTRIC) /* Same dielectric all around */
          Vij[i][j]=r_over_4*(Vij[i][j+1]+Vij[i+1][j]+Vij[i][j-1]+Vij[i-1][j])+one_minus_r*Vij[i][j];
        else if(cell_type[i][j] > DIELECTRIC) /* only update dielectrics, not conductors */
        {
          a=(Er[i][j] * Er[i][j-1] * Vij[i][j-1])/(Er[i][j] + Er[i][j-1]);
          b=(Er[i][j] * Er[i][j+1] * Vij[i][j+1])/(Er[i][j] + Er[i][j+1]);
          c=(Er[i][j] * Er[i-1][j] * Vij[i-1][j])/(Er[i][j] + Er[i-1][j]);
          d=(Er[i][j] * Er[i+1][j] * Vij[i+1][j])/(Er[i][j] + Er[i+1][j]);
    
          e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
          f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
          g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
          h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
          Vij[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*Vij[i][j];
        }
      }
    }
    Barrier();
    //printf("all done top half id = %d\n",myid);
    for(i= firstcol ; i <= lastcol; ++i){
      if(i%2 ==1 )
	jstart=2;
      else
	jstart=1;
      for(j=jstart ; j < height -1; j+=2){
        if(cell_type[i][j] == DIELECTRIC) /* Same dielectric all around */
          Vij[i][j]=r_over_4*(Vij[i][j+1]+Vij[i+1][j]+Vij[i][j-1]+Vij[i-1][j])+one_minus_r*Vij[i][j];
        else if(cell_type[i][j] > DIELECTRIC) /* only update dielectrics, not conductors */
        {
          a=(Er[i][j] * Er[i][j-1] * Vij[i][j-1])/(Er[i][j] + Er[i][j-1]);
          b=(Er[i][j] * Er[i][j+1] * Vij[i][j+1])/(Er[i][j] + Er[i][j+1]);
          c=(Er[i][j] * Er[i-1][j] * Vij[i-1][j])/(Er[i][j] + Er[i-1][j]);
          d=(Er[i][j] * Er[i+1][j] * Vij[i+1][j])/(Er[i][j] + Er[i+1][j]);
    
          e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
          f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
          g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
          h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
          Vij[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*Vij[i][j];
        }
      }
    }
    Barrier();
    //printf("all done bot half id = %d\n",myid);
  }
  Barrier();
  //printf("XXXXXXXXXXX %d\n",myid);
  return(0);
}

double finite_difference_multi_threaded(int number_of_iterations)
{
  int i, j, ret, thread_number;
  pthread_attr_t attr;
  pthread_t thread_id[MAXIMUM_PROCESSING_DEVICES];


  double capacitance_per_metre, energy_per_metre;


  /* set global thread attributes */
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  /* initialize mutex and condition variable */
  pthread_mutex_init(&barrier, NULL);
  pthread_cond_init(&go, NULL);
  //do{
  for(thread_number=0;thread_number<number_of_workers;thread_number++){   
    ret=pthread_create(&thread_id[thread_number],&attr, worker,(void *)thread_number);
    if(ret != 0)
      exit_with_msg_and_exit_code("failed to create thread in finite_difference_multi_threaded.c",THREAD_CREATION_FAILED);
  } 
  /* Wait for each thread to join - i.e. once they are all finished. */
  for(thread_number=0;thread_number<number_of_workers;thread_number++)
  {
    ret=pthread_join(thread_id[thread_number], NULL);
    if(ret != 0)
      exit_with_msg_and_exit_code("failed to join thread in finite_difference_multi_threaded.c",THREAD_FAILED_TO_JOIN);
      }
  //} while (check_convergence(Vij,Vij2,width,height) > 1e-3);
  /* The energy in the matrix has now been minimised a number
  (number_of_iterations) times, so we now calcuate the capacitance to see if it
  has converged */
  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
	energy_per_metre+=find_energy_per_metre(i,j);
 
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else 
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
#endif
