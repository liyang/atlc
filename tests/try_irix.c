/* Try to get data. This will work only on a IRIX machine. */

#ifdef HAVE_UNISTD_H 
#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_VID_H
#ifdef HAVE_INVENT_H
#ifdef _SC_NPROC_ONLN

#include <utsname.h>
#include <invent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#endif
#endif
#endif
#endif
#endif
#endif

#include "defs.h"

int try_irix(struct computer_data *data)

{

#ifdef HAVE_UNISTD_H 
#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_VID_H
#ifdef HAVE_INVENT_H
#ifdef _SC_NPROC_ONLN

  long max_CPUs=0, CPUs_online=0;
  int clock_speed_in_MHz;
  processor_info_t infop;
  double ram;

  /* Obtain the maximum number of CPUs supported on the IRIX system */

  /* Obtain the number of CPUs online on the IRIX system */
  CPUs_online=0;
  CPUs_online=(long) sysconf(_SC_NPROC_ONLN);
  if( CPUs_online >= 1 )
    sprintf(data->cpus,"%ld",CPUs_online);


  /* Obtain the of CPU and FPU on the IRIX box */

  /* Obtain the RAM on the IRIX system. */

  /* Obtain the manufacturer */
#ifdef SI_HW_PROVIDER
  if sysconf(SI_HW_PROVIDER) != -1)
    sprintf(data->hw_provider,"SGI");
#endif

  return(PROBABLY_IRIX);

#endif
#endif
#endif
#endif
#endif
#endif
  return(-1);
}
