/* Try to get data. This will work only on a Linux machine. */

#ifdef HAVE_STDIO_H         /* it does ***not** necessarily mean it's Linux */
#ifdef HAVE_STDLIB_H        /* but it will define some variables that we      */
#ifdef HAVE_SYS_TYPES_H     /* later check for, to confirm it's Linux       */
#ifdef HAVE_SYS_UTSNAME_H   /* later check for, to confirm it's Linux       */
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_LONG_LONG 

#include <sys/param.h>    /* Include the header files */
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>

#endif
#endif
#endif
#endif
#endif
#endif  /* End of including header files likely to be on Linux system */

#include "defs.h"
#define BYTES_PER_MB  1048576

int try_linux(struct computer_data *data)

{

#ifdef HAVE_STDIO_H         /* it does ***not** necessarily mean it's Linux */
#ifdef HAVE_STDLIB_H        /* but it will define some variables that we      */
#ifdef HAVE_SYS_TYPES_H     /* later check for, to confirm it's Linux       */
#ifdef HAVE_SYS_UTSNAME_H   /* later check for, to confirm it's Linux       */
#ifdef HAVE_UNISTD_H 
#ifdef HAVE_LONG_LONG 

  struct utsname operating_system;
  long long ram;

  /* Obtain the maximum number of CPUs supported on the Linux system */

  /* Obtain the number of CPUs online on the Linux system */


  /* Obtain the of CPU and FPU on the Linux box */


  /* Obtain the RAM on the Linux system if possible */

#ifdef _SC_PHYS_PAGES
#ifdef _SC_PAGESIZE
  if ((long) sysconf(_SC_PHYS_PAGES) > 0L)
  {
    if ((long) sysconf(_SC_PAGESIZE) > 0L)
    {
      ram=(long long) sysconf(_SC_PAGESIZE);
      ram*= (long long) sysconf(_SC_PHYS_PAGES);
      {
        ram=ram/(long long) BYTES_PER_MB;
        sprintf(data->memory,"%lld",ram);
      }
    }
  }
#endif
#endif


  /* Obtain operating system informaton */
  uname(&operating_system);
  strcpy(data->sysname,operating_system.sysname);
  strcpy(data->nodename,operating_system.nodename);
  strcpy(data->release,operating_system.release);
  strcpy(data->version,operating_system.version);
  strcpy(data->machine,operating_system.machine);

  /* Obtain the manufacturer */
  sysinfo(SI_HW_PROVIDER,data->hw_provider,MAX_SIZE);

  /* Obtain the Platform */
  sysinfo(SI_PLATFORM,data->hw_platform,MAX_SIZE);

  return(PROBABLY_LINUX);

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
#endif
  return(-1);
}
