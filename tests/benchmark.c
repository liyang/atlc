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

#ifdef HAVE_PROCESSOR_INFO /* function processor_info() is in Solaris */
#include <sys/processor.h> /* But not on Tru64 */
#endif

#ifdef HAVE_UNISTD_H 
#include <unistd.h>
#endif


#ifdef HAVE_SYS_PARAM_h /* Try this on HP-UX */
#include  <sys/param.h>
#endif

#ifdef HAVE_SYS_PSTAT_H
#include <sys/pstat.h>
#endif

#ifdef HAVE_SYS_UNISTD_H 
#include <sys/unistd.h>
#endif

#ifdef HAVE_GETSYSINFO /* Only in Tru64 UNIX */

#ifdef HAVE_SYS_SYSINFO_H
#include <sys/sysinfo.h>
#endif

#ifdef HAVE_MACHINE_HAL_SYSINFO_H
#include <machine/hal_sysinfo.h>
#endif

#endif 

#define BYTES_PER_MB  1048576
int main(int argc, char **argv)
{
  time_t start1, finished1;
  int t1; 
  long num_cpus=0;
  char *mhz, *eff, *cpus, *str, *max_cpus;
  char *cpu_type, *fpu_type, *memory;
  long max_CPUs=0;
  FILE *fp;
#ifdef HAVE_LONG_LONG
  long long ram=0;
#endif

#ifdef PSTAT_STATIC /* Try this on HP-UX */
#ifdef HAVE_LONG_LONG 
#ifdef HAVE_PSTAT
  struct pst_static pst;
  union pstun pu;
#endif
#endif
#endif

/* Unless the code is multi-threaded, the terms speedup and efficiency have no 
meaning. There's no point in running the benchmark twice (once as single threaded,
once as multi-threaded */

#ifdef ENABLE_POSIX_THREADS
  time_t start2, finished2;
  double speedup;
  int t2;
#endif /* ENABLE_POSIX_THREADS */

/* If we have the function processor_info, we will obtain the number of cpus, 
and if possible their type and speed */

#ifdef HAVE_PROCESSOR_INFO
  int  speed=0;
  processorid_t id;  /* defined as a integer in solaris */
  processor_info_t infop;
#endif /* HAVE_PROCESSOR_INFO */

#ifdef HAVE_GETSYSINFO /* Only in Tru64 UNIX */
  int  cpuid;
  struct cpu_state cpu_state_buffer;
  struct cpu_info  cpu_info_buffer;
  long  ramsize_kb=0, ramsize_mb=0;
#endif /* HAVE_GETSYSINFO */

  mhz = (char *) malloc(100);
  cpu_type = (char *) malloc(100);
  fpu_type = (char *) malloc(1000);
  max_cpus = (char *) malloc(100);
  cpus = (char *) malloc(100);
  memory = (char *) malloc(100);
  eff = (char *) malloc(100);

  strcpy(mhz,"unknown");
  strcpy(cpu_type,"unknown");
  strcpy(fpu_type,"unknown");
  strcpy(max_cpus,"unknown");
  strcpy(cpus,"unknown");
  strcpy(memory,"unknown");
  strcpy(eff,"unknown");

#ifdef HAVE_GETSYSINFO /* Only in Tru64 UNIX */

  getsysinfo(GSI_CPU,(caddr_t)&cpuid,sizeof(cpuid),0,0);
  sprintf(cpu_type,"%d (whatever that is!)",cpuid);

  //getsysinfo(GSI_CPU_STATE,(caddr_t)&cpu_state_buffer,sizeof(cpu_state_buffer),0,0);
  //num_cpus=() cpu_state_buffer.cs_running;

  getsysinfo(GSI_CPU_INFO,(caddr_t)&cpu_info_buffer,sizeof(cpu_info_buffer),0,0);
  if( cpu_info_buffer.mhz > 1) 
  sprintf(mhz,"%d",(int) cpu_info_buffer.mhz);

#ifdef GSI_PHYSMEM
#ifdef HAVE_LONG_LONG
  getsysinfo(GSI_PHYSMEM, (caddr_t)&ramsize_kb, sizeof(ramsize_kb), 0, 0); /* in kb */
  ramsize_mb=ramsize_kb/1024L; /* Mb */
  sprintf(memory,"%lld",(long long) ramsize_mb);
#endif /* HAVE_LONG_LONG */
#endif /* GSI_PHYSMEM */

#endif /* HAVE_GETSYSINFO */
  
#ifdef _SC_NPROCESSORS_ONLN /* Should be portable */
  num_cpus= (long) sysconf(_SC_NPROCESSORS_ONLN);
  sprintf(cpus,"%ld",num_cpus);
#endif

#ifdef _SC_NPROCESSORS_MAX
  max_CPUs=(long) sysconf(_SC_NPROCESSORS_MAX);
  if(max_CPUs >=1 )
    sprintf(max_cpus,"%ld",max_CPUs);
#endif


#ifdef HAVE_CPU_GET_MAX  /* Tru64 */
  max_CPUs=(long) cpu_get_max();
  if(max_CPUs >=1 )
    sprintf(max_cpus,"%ld",max_CPUs);
#endif

/* Find the ram if possible, but taking care not to use a long, as 
this could be overflowed on a 32-bit system. Hence use a long long */

#ifdef _SC_PHYS_PAGES
#ifdef _SC_PAGESIZE
#ifdef HAVE_LONG_LONG
  if ((long) sysconf(_SC_PHYS_PAGES) > 0L)
  {
    if ((long) sysconf(_SC_PAGESIZE) > 0L)
    {
      ram=(long long) sysconf(_SC_PAGESIZE);
      ram*= (long long) sysconf(_SC_PHYS_PAGES);
      {
        ram=ram/(long long) BYTES_PER_MB;
        sprintf(memory,"%lld",ram);
      }
    }
  }
#endif
#endif
#endif

#ifdef PSTAT_STATIC /* Try this on HP-UX */
#ifdef HAVE_LONG_LONG 
#ifdef HAVE_PSTAT
  pu.pst_static=&pst;
  if( pstat(PSTAT_STATIC,pu,(size_t) sizeof(pst),(size_t) 0, 0) != -1)
  {
    ram=(long long) pst.physical_memory;
    ram*=(long long) pst.page_size;
    ram=ram/(long long) BYTES_PER_MB;
    sprintf(memory,"%lld",ram);
  }
#endif
#endif
#endif


#ifdef HAVE_PROCESSOR_INFO
  num_cpus=0;
  for(id=0; id<1024; ++id)
  {
    if( processor_info(id, &infop) == 0)
    {
      if(infop.pi_state == P_ONLINE)
      {
        num_cpus++;
        strcpy(cpu_type,infop.pi_processor_type);
        strcpy(fpu_type,infop.pi_fputypes);
        speed=infop.pi_clock;
        if(speed > 1)
          sprintf(mhz,"%d",speed);
      }
    }
  }
  sprintf(cpus,"%ld",num_cpus);
#endif

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
run the benchmark once - but possibly twice */

  sprintf(str,"%s -s -S -t0 %s > /dev/null 2> /dev/null \n", argv[1], argv[2]);
  time(&start1);
  //system(str);
  pclose(popen(str, "w"));
  time(&finished1);
  t1 = (int) (finished1 - start1);

/* If the code is multi-threaded, run the bencharmark for a second time. We can
always calculate a speedup in these circumstances */
#ifdef ENABLE_POSIX_THREADS
  sprintf(str,"%s -s -S %s > /dev/null\n", argv[1], argv[2]);
  time(&start2);
  pclose(popen(str, "w"));
  time(&finished2);
  t2 = (int) (finished2 - start2);
  speedup=(double)t1/t2;
#endif

/* Whether or not we can calculate the efficieny depends on whether we have managed
to obtain the number of processors present in the system. If the number of procesors
found is zero (i.e. we have been unable to determine them, due to a lack of
processor_information, or that not working properly, then we can't compute the efficiency,
so will leave it at the default value of "unknown". */

  if(num_cpus != 0)
    sprintf(cpus,"%ld",num_cpus);
    

#ifdef ENABLE_POSIX_THREADS
  if(num_cpus != 0)
    sprintf(eff,"%.3f",(double)speedup/num_cpus);
#endif

  
#ifdef ENABLE_POSIX_THREADS
  printf("0 %d %d %.2f %s %s %s %s %s %s %s\n",t1, t2, speedup, cpus, mhz, eff, cpu_type,fpu_type,max_cpus,memory );
  return(0);
#else 
  strcpy(eff,"1");
  printf("0 %d %d %.2f %s %s %s %s %s %s %s \n",t1, t1, 1.0 , cpus, mhz, eff, cpu_type, fpu_type, max_cpus, memory);
  return(0);
#endif

}


