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

/* This is my first attempt at multi-processing, beyond simple examples
in books. Hence I suspect it is not efficient */

#ifdef ENABLE_MP /*file only needed on MP systems. */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef HAVE_THREAD_H
#include <thread.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

extern int coupler;
extern int width, height;
extern double **Vij, **Er;
extern char **cell_type;
extern int dielectrics_to_consider_just_now;
extern int max_threads; 
extern double r;

pthread_t *threads;
void *do_columns(void *thread_arg)
{
  int inc, z, i, y=1, k;
  int *thread = (int *) thread_arg;
  inc=(width-max_threads)/max_threads; /* is this okay? I'm not sure */
  z=inc;
  for(k=0;k<(*thread);++k)
  {
    y+=inc+1;
    z+=inc+1;
  }
  if(*thread==max_threads-1)
    z=width-1; 
  //for(i=y; i<=z; ++i) /* this could have cuased a crash. 
  for(i=y; i<=z; ++i)
  {
    //printf("i=%d y=%d z=%d in do cols\n",i,y,z);
    /* the following is a bit of a hack and needs clearing up. Basically
    the formual used for computing v(i,j) in the routine
    update_voltage_arrary breaks down when i==width-1. However, I've
    added a hack to that, to take care of the situation when i==width-2.
    to compute v(i==width-1) */
    if(i!=width-1)
      update_voltage_array(i,1);
  }
}

/* There are two versions of finite_difference. Both take the same 
arguments and are both return the same data. One is signle threaded, the
other multi-threaded. */

double finite_difference(int accuracy)
{
  int i, j, a, y, z, thread_number, *id_arg, ret;
  int inc;
  double capacitance_per_metre=0.0, energy_per_metre;
  /* We split the width into max_threads regions, and calculate the voltage at
  each point using a different thread for each. To do this safely, a single line
  of calculations must be missed between each set. ie with a 256 wide image, we
  would do 1 to 63, 65 to 127, 129 to 191 and 193 to 255. We later do the 
  missing ones sequentially */
  /* allocate space for threads  */
  threads = (pthread_t *) malloc(max_threads*sizeof(pthread_t));
  id_arg = ivector(0,max_threads-1);
  if(threads == NULL)
  {
    fprintf(stderr,"malloc failed for threads in finite .. .c\n");
    exit_with_msg_and_exit_code("alloc failed for threads in finite_difference_multi_threaded.c",MALLOC_FAILED);
  }
  y=1;
  inc=(width-max_threads)/max_threads;
  z=inc;
  for(a=1; a<=accuracy; ++a)
  {
    /* Perform the calculations on each column in parallel, missing
    out one column for each thread eneabled. */

    for(thread_number=0;thread_number<max_threads;thread_number++)
    {   
      id_arg[thread_number] = thread_number;
      if ((ret=pthread_create(&(threads[thread_number]),NULL,\
      do_columns,(void *)&(id_arg[thread_number])))!=0)
        perror("pthread_create"), exit(7);
    } 
    /* Wait for each thread to join - i.e. once they are all finished.*/
    for(thread_number=0;thread_number<max_threads;++thread_number)
    {
      if (pthread_join(threads[thread_number], NULL) != 0)
        perror("pthread_join"),exit(8);
    }
    /* All threads have now finished, so most of the voltages have 
    been calculated - just a few remain. 

    We now complete the accuracy calculation of the missing lines.
    If the arrary width was 256, these would be the lines 
    64, 128 and 192. */
    i=0;
    for(thread_number=0;thread_number<max_threads-1;++thread_number)
    {
      i+=inc+1;
      update_voltage_array(i,1);
    }
    /* Now the voltage matrix has been calculated once. Note the
    voltages calculated are slightly different from those of the
    single threaded case. We need to know the voltage at all
    points around where we are calculationg (ie to find v(i,j), we
    need v(i+1,j), v)i-1,j), v(i,j+1) and v(i,j-1). Hence by splitting
    the matrix up as we have done here, the values will be different.
    However, the difference shluld be slight. */
  } /* end of accuracy loop */
  /* The energy in the matrix has now been minimised a number
  (accuracy) times, so we now calcuate the capacitance to see if it is
  converging */
  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
    { 
	energy_per_metre+=find_energy_per_metre(i,j);
    }
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else if (coupler==TRUE)
    capacitance_per_metre=energy_per_metre;

  return(capacitance_per_metre);
}
#endif
