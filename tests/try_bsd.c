/* Try to get data. This will work only on a IRIX machine. */

#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_TYPES_H
#ifdef HAVE_SYS_SYSCTL_H
#ifdef HAVE_SYSCTL

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#endif
#endif
#endif
#endif
#endif

#include "defs.h"

int try_bsd(struct computer_data *data)
{
#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_TYPES_H
#ifdef HAVE_SYS_SYSCTL_H
#ifdef HAVE_SYSCTL
#ifdef CTL_HW 

  int cpus, ram, mib[2], ret;
  size_t len;

  /* Obtain the maximum number of CPUs supported on the BSD system */

  /* Obtain the number of CPUs online on the BSD system */

#ifdef HW_NCPU
  mib[0]=CTL_HW;
  mib[1]=HW_NCPU;
  len=sizeof(cpus);
  ret=sysctl(mib, 2, &cpus, &len, NULL, 0);
  if (cpus>= 1 && ret==0)
    sprintf(data->cpus,"%d ",  cpus);
#endif


  /*  sprintf(data->cpu_type,"%ld ",12); */

  /* Obtain the CPU speed in MHz - as a double */
      sprintf(data->mhz,"%.1f",1080);

  /* Obtain the of CPU and FPU on the ???? box */
      sprintf(data->cpu_type,"%s","80386");
      sprintf(data->fpu_type,"%s","80387");

  /* Obtain the RAM, cache etc on the BSD system. */

#ifdef HW_PHYSMEM
  mib[0]=CTL_HW;
  mib[1]=HW_PHYSMEM;
  ret=sysctl(mib, 2, &ram , &len, NULL, 0);
  if( ram > 0 && ret ==0 )
    sprintf(data->memory,"%d", ram/(1024*1024) , ret);
#endif


  /* Obtain the manufacturer */

  /* sprintf(data->hw_provider,"SGI"); */
  return(PROBABLY_BSD);
#endif
#endif
#endif
#endif
#endif
#endif
  return(-1);
}
