#include "defs.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

int try_unicos(struct computer_data *data)
{
#ifdef _SC_CRAY_NCPU
  static char *mftype[] = {"?", "?", "?", "X-MP", "?", \
  "Y-MP", "2","C90???","C90_or_Y16","T4_or_T16_or_T32"};

  long CPUs_online=0, cpu_cycle_time_in_ps;
  double clock_speed_in_MHz;
  double ram;

  /* Obtain the maximum number of CPUs supported on the UNICOS system */

  /* Obtain the number of CPUs online on the UNICOS system */
  CPUs_online=0;
  CPUs_online=sysconf(_SC_CRAY_NCPU);
  if( CPUs_online >= 1 )
    sprintf(data->cpus,"%ld",CPUs_online);


  /* Obtain the speed of the Cray machine. */
#ifdef _SC_CRAY_CPCYCLE
  if((cpu_cycle_time_in_ps=sysconf(_SC_CRAY_CPCYCLE)) > 0)
  {
      sprintf(data->mhz,"%.1f",1e6/cpu_cycle_time_in_ps);
  }
#endif

  /* Obtain the RAM on the UNICOS system */


  /* Obtain the manufacturer */
  strcpy(data->hw_provider,"Cray");

  /* Obtain the Platform */
#ifdef _SC_CRAY_MFTYPE
  if (sysconf(_SC_CRAY_MFTYPE) <= 9L)
    strcpy(data->hw_platform,mftype[sysconf(_SC_CRAY_MFTYPE)] );
#endif

  return(PROBABLY_UNICOS);
#endif
  return(-1);
}
