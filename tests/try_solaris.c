/* Try to get data. This will work only on a Solaris machine. */

#ifdef HAVE_SYS_PARAM_H     /* This looks for header files that should be     */
#ifdef HAVE_SYS_PROCESSOR_H /* present on Solaris. If they are all present    */
#ifdef HAVE_STDIO_H         /* it does ***not** necessarily mean it's Solaris */
#ifdef HAVE_STDLIB_H        /* but it will define some variables that we      */
#ifdef HAVE_SYS_TYPES_H     /* later check for, to confirm it's Solaris       */
#ifdef HAVE_STRING_H
#ifdef HAVE_SYS_UNISTD_H
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_SYS_UTSNAME_H
#ifdef HAVE_SYS_SYSTEMINFO_H

#include <sys/param.h>    /* Include the header files */
#include <sys/processor.h>    /* Include the header files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/unistd.h>
#include <sys/utsname.h>
#include <sys/systeminfo.h>

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif  
#endif
#endif  /* End of including header files likely to be on Solaris system */

#include "defs.h"

int try_solaris(struct computer_data *data)

{
#ifdef HAVE_SYS_SYSTEMINFO_H
#ifdef HAVE_SYS_PARAM_H     
#ifdef HAVE_SYS_PROCESSOR_H 
#ifdef HAVE_STDIO_H         
#ifdef HAVE_STDLIB_H       
#ifdef HAVE_SYS_TYPES_H   
#ifdef HAVE_STRING_H
#ifdef HAVE_SYS_UNISTD_H
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_SYS_UTSNAME_H
#ifdef HAVE_PROCESSOR_INFO
#ifdef HAVE_SYSCONF

#ifdef _SC_NPROCESSORS_MAX

  long max_CPUs=0;
  int clock_speed_in_MHz;
  processor_info_t infop;

  /* Obtain the maximum number of CPUs supported on the Solaris system */
  max_CPUs=0;
  max_CPUs=(long) sysconf(_SC_NPROCESSORS_MAX);
  if(max_CPUs >=1 )
    sprintf(data->max_cpus,"%ld",max_CPUs);

  /* Obtain the of CPU and FPU on the Solaris box */
  if( processor_info((processorid_t) 0, &infop) == 0)
  {
    strcpy(data->cpu_type,infop.pi_processor_type);
    strcpy(data->fpu_type,infop.pi_fputypes);
    clock_speed_in_MHz=(int) infop.pi_clock;
    if(clock_speed_in_MHz > 1)
      sprintf(data->mhz,"%d",clock_speed_in_MHz);
  }


  /* Obtain operating system informaton, which should have 
  been found with try_portable.c */

  /* Obtain the manufacturer */
  sysinfo(SI_HW_PROVIDER,data->hw_provider,MAX_SIZE);

  /* Obtain the Platform */
  sysinfo(SI_PLATFORM,data->hw_platform,MAX_SIZE);

  return(PROBABLY_SOLARIS);

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
#else  
  return(-1);
#endif
}
