#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern int verbose;
extern int append_flag;
void do_fd_calculation(double *capacitance, double *inductance, double *Zo, FILE *where_to_print, double cutoff,
int dielectrics_to_consider_just_now, char * filename)
{
  double c_old, velocity, c, vf;
  FILE *appendfile_fp;
  char *appendfile;
  appendfile=(char *) malloc(100);
  
    *capacitance=VERY_LARGE; /* Can be anything large */
    do /* Start a finite calculation */
    {
      c_old=*capacitance; 

      /* Calcuate the capacitance, using 100 iterations in a finite
      differnce loop. There are two routines called finite_difference,
      one in the file finite_difference_multi_threaded.c and another 
      in the file finite_difference_single_threaded.c. The function has
      the same name in each, but is difference, depending on whether or
      not the programme is using multiple processors */
      dielectrics_to_consider_just_now=1;
      *capacitance=finite_difference(100);

      /* Once the capacitance is know, we can calculate L, Zo  and the
      velocity of propogation */

      *inductance=MU_0*EPSILON_0/(*capacitance);
      *Zo=sqrt((*inductance)/(*capacitance));
      velocity=1.0/pow((*inductance)*(*capacitance),0.5);
      c=1.0/(sqrt(MU_0 * EPSILON_0)); /* approx 3x10^8 m/s */
      vf=velocity/c;  /* Velocity factor */

      /* If the -v option is given on the command line, more data is
      produced */

      if(verbose)
      {
        print_data(stdout,filename,1.0,*capacitance,*inductance,*Zo,\
	velocity,vf);
        if(append_flag==TRUE)
        {
           appendfile_fp=fopen(appendfile,"a");
	   if(appendfile_fp==NULL)
	   {
	     fprintf(stderr,"Error #6. Can't open file for appending data in atlc.c\n");
	     exit(6);
           }
	   print_data(appendfile_fp,filename,1.0,*capacitance,\
	   *inductance,*Zo,velocity,vf);
           fclose(appendfile_fp);
	}
      }
    } while (fabs((c_old-*capacitance)/c_old) > cutoff); /* end of FD loop */
}
