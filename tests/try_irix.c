/* Try to get data. This will work only on a IRIX machine. */

#ifdef HAVE_UNISTD_H 
#ifdef HAVE_STDIO_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_SYS_VID_H
#ifdef HAVE_INVENT_H 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <invent.h>
#include <sys/types.h>

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

  long CPUs_online;
  inventory_t *pinv;

  /* Obtain the maximum number of CPUs supported on the IRIX system */

  /* Obtain the number of CPUs online on the IRIX system */
  CPUs_online=0;
  CPUs_online=(long) sysconf(_SC_NPROC_ONLN);
  if( CPUs_online >= 1 )
    sprintf(data->cpus,"%ld ",CPUs_online);


  /* Obtain the of CPU and FPU on the IRIX box */

  /* Obtain the RAM on the IRIX system. */

  setinvent(); /* Always call before starting to call getinvt() */
  while ((pinv = getinvent()))
  {
    if (pinv->inv_class == INV_MEMORY && (pinv->inv_type == INV_MAIN_MB))
      sprintf(data->memory,"%d", pinv->inv_state);
    if (pinv->inv_class == INV_MEMORY && (pinv->inv_type == INV_DCACHE))
      sprintf(data->L1data,"%d", pinv->inv_state/1024);
    if (pinv->inv_class == INV_MEMORY && (pinv->inv_type == INV_ICACHE))
      sprintf(data->L1instruction,"%d", pinv->inv_state/1024);
    if (pinv->inv_class == INV_MEMORY && (pinv->inv_type == INV_SIDCACHE))
      sprintf(data->L2,"%d", pinv->inv_state/1024);
  }


  /* Obtain the manufacturer */
  sprintf(data->hw_provider,"SGI");

  return(PROBABLY_IRIX);
#endif
#endif
#endif
#endif
#endif
  return(-1);
}
