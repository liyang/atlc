/* Times two commands entered on the command line, to make
sure the second takes less time than the first. */

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif  

#ifdef HAVE_STRING_H
#include <string.h>
#endif  

#ifdef HAVE_UNISTD_H
#include <unistd.h> /* sleep on Solaris needs this */
#endif

#include "defs.h"


int main(int argc, char **argv)
{
  time_t start1, finished1;
  struct computer_data data;
  int operating_system=0;

  int t1; 
  char *str;
  FILE *fp;

#ifdef ENABLE_POSIX_THREADS
  time_t start2, finished2;
  int t2;
#endif /* ENABLE_POSIX_THREADS */

  strcpy((char *) data.mhz,"unknown");
  strcpy((char *) data.cpu_type,"unknown");
  strcpy((char *) data.fpu_type,"unknown");
  strcpy((char *) data.max_cpus,"unknown");
  strcpy((char *) data.cpus,"unknown");
  strcpy((char *) data.memory,"unknown");
  strcpy((char *) data.eff,"unknown");
  strcpy((char *) data.sysname,"unknown");
  strcpy((char *) data.nodename,"unknown");
  strcpy((char *) data.release,"unknown");
  strcpy((char *) data.version,"unknown");
  strcpy((char *) data.machine,"unknown");
  strcpy((char *) data.hw_provider,"unknown");
  strcpy((char *) data.hw_platform,"unknown");
  strcpy((char *) data.speedup,"N/A    ");

  /*get_portable_data(data);*/
  /*try_hpux(&data);*/
  operating_system=try_solaris(&data);
  /*try_tru64(&data); */


/* Whatever happens (single-threaded or multi-theraded, we will check that all the 
files (the executable atlc and bitmap are both present). */
  if(argc !=3 )
  {
    fprintf(stderr,"Usage: path_to_atlc path_to_bitmap\n");
    exit(1);
  }
  if( (str=malloc(2000)) == NULL) 
  {
    fprintf(stderr,"Memory allocation failure in benchmark.c\n");
    exit(1);
  }
  if ((fp=fopen(argv[1],"r")) == NULL)
  {
    fprintf(stderr,"Can't open the binary file %s for reading\n",argv[1]);
    exit(2);
  }
  if ((fp=fopen(argv[2],"r")) == NULL)
  {
    fprintf(stderr,"Can't open the bitmap %s for reading\n",argv[2]);
    exit(3);
  }
/* Assuming we have not exited due to a lack of suitable files present, 
run the benchmark at least once - but possibly twice if code is   
multi-threaded */

  sprintf(str,"%s -s -S -t0 %s > /dev/null 2> /dev/null \n", argv[1], argv[2]);
  time(&start1);
  pclose(popen(str, "w"));
  time(&finished1);
  t1 = (int) (finished1 - start1);

/* If the code is multi-threaded, run the benchmark for a second time. We can
always calculate a speedup in these circumstances */

#ifdef ENABLE_POSIX_THREADS
  sprintf(str,"%s -s -S %s > /dev/null\n", argv[1], argv[2]);
  time(&start2);
  pclose(popen(str, "w"));
  time(&finished2);
  t2 = (int) (finished2 - start2);
  sprintf(data.speedup,"%.3f\n",(double)t1/t2); /* other N/A */

  /* Whether or not we can calculate the efficieny depends on whether we have managed
  to obtain the number of processors present in the system. If the number of procesors
  found is zero (i.e. we have been unable to determine them, due to a lack of
  processor_information, or that not working properly, then we can't compute the efficiency,
  so will leave it at the default value of "unknown". */

  if(data.cpus != 0)
    sprintf(data.eff,"%.3f",(double)atof(data.speedup)/atoi(data.cpus)); /* otherwise unknown */
#endif

  printf("0 %d %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",t1, t1, data.speedup, data.cpus, data.mhz, data.eff, data.cpu_type,data.fpu_type,data.max_cpus,data.memory,data.sysname,data.nodename,data.release,data.version,data.machine,data.hw_provider, data.hw_platform);
  return(0);
}


