/* Try to get data. This will work only on a HP-UX machine. */

#ifdef HAVE_SYS_PARAM_H   /* This looks for header files that should be  */
#ifdef HAVE_SYS_PSTAT_H   /* present on HP-UX. If they are all present */
#ifdef HAVE_STDIO_H       /* it does ***not** necessarily mean it's HP-UX */
#ifdef HAVE_STDLIB_H      /* but it will define some variables that we */
#ifdef HAVE_SYS_TYPES_H   /* later check for, to confirm it's HP-UX */
#ifdef HAVE_STRING_H
#ifdef HAVE_SYS_UNISTD_H
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_SYS_UTSNAME_H
#ifdef HAVE_LONG_LONG 

#include <sys/param.h>    /* Include the header files */
#include <sys/pstat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/unistd.h>
#include <sys/utsname.h>

#endif
#endif
#endif
#endif
#endif
#endif  
#endif
#endif
#endif  
#endif  /* End of including header files likely to be on HP-UX system */

#define BYTES_PER_MB  1048576

int try_hpux(char *mhz, char *cpus, char *max_cpu, char *sysname, \
char *nodename, char *release, char *version, char *machine, \
char *cpu_type, char *fpu_type, char *memory,char *manufacturer, char *hw_platform)
{

#ifdef HAVE_SYS_PARAM_H 
#ifdef HAVE_SYS_PSTAT_H
#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_TYPES_H
#ifdef HAVE_STRING_H
#ifdef HAVE_SYS_UNISTD_H
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_SYS_UTSNAME_H

#ifdef HAVE_LONG_LONG      /* I'll insist on long long being present */

#ifdef HAVE_PSTAT_GETDYNAMIC /* Check for some HP-UX specific bits now */
#ifdef HAVE_PSTAT_GETPROCESSOR
#ifdef HAVE_PSTAT
#ifdef PSTAT_STATIC 

  long num_cpus=0;
  long long clock_speed_in_Hz;
  int clock_speed_in_MHz;

  struct pst_dynamic dynamic_hpux;
  struct pst_processor psp;

  /* Obtain the number of CPUs on the HP-UX system */

  pstat_getdynamic(&dynamic_hpux,(size_t) sizeof(dynamic_hpux),1,0);
  num_cpus=(long) dynamic_hpux.psd_proc_cnt; ;
  max_CPUs=(long) dynamic_hpux.psd_max_proc_cnt;
  sprintf(max_cpus,"%ld",max_CPUs);
  sprintf(cpus,"%ld",num_cpus);

  /* Obtain the RAM on the HP-UX system */

  pstat_getdynamic(&dynamic_hpux,(size_t) sizeof(dynamic_hpux),1,0);

  pu.pst_static=&pst;
  if( pstat(PSTAT_STATIC,pu,(size_t) sizeof(pst),(size_t) 0, 0) != -1)
  {
    ram=(long long) pst.physical_memory;
    ram*=(long long) pst.page_size;
    ram=ram/(long long) BYTES_PER_MB;
    sprintf(memory,"%lld",ram);
  }

  pstat_getprocessor(&psp, sizeof(psp), 1, 0);
  scclktick=sysconf(_SC_CLK_TCK);
  clock_speed_in_Hz = psp.psp_iticksperclktick * scclktick;
  if(clock_speed_in_Hz > 1)
    sprintf(mhz,"%ld",clock_speed_in_Hz);
  return(0);
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
  return(1);
}
