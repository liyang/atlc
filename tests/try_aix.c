/* Try to get data. This will work only on an IBM running AIX */

#include "defs.h"
#define BYTES_PER_MB  1048576

#ifdef HAVE_AIXFONT_H
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#endif

int try_aix(struct computer_data *data)
{
#ifdef HAVE_AIXFONT_H
#ifdef HAVE_UNISTD_H
  long ram_in_kb;
  strcpy(data->hw_provider,"IBM");
  strcpy(data->cpus,"%d",sysconf(_SC_NPROCESSORS_ONLN));
  ram_in_kb=sysconf(_SC_PAGESIZE)/4;
  ram_in_kb*=1;
  sprintf(data->memory,"%ld",ram_in_kb/1024);
  return(PROBABLY_AIX);
#endif
#endif
  return(-1);
}
