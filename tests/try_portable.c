/* Try to get data. This should work on just about any 
system going. However, the amount of data collected 
is not very much, so other C files, that try to 
get more information are about. */

#ifdef HAVE_STRING_H
#include <string.h>
#endif  

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_SYS_UTSNAME_H
#include <sys/utsname.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "defs.h"

extern int errno;
#define BYTES_PER_MB  1048576

int try_portable(struct computer_data *data)
{
  int ret, i, string_length;

#ifdef _SC_PHYS_PAGES
#ifdef _SC_PAGESIZE
  double ram;
#endif
#endif

#ifdef HAVE_UNAME
  struct utsname operating_system;

  ret=uname(&operating_system);
  if (ret == -1)
  {
#ifdef HAVE_ERRNO_H
    fprintf(stderr,"failure in call to uname in try_portable.c errno=%d\n", errno);
#else
    fprintf(stderr,"failure in call to uname in try_portable.c\n");
#endif /* #ifdef HAVE_ERRNO_H */
    return(ret);
  }
  else
  {
    /* There is a distint posibility that some data in the operating
    system structure will have spaces in it. This will screw things
    up, since benchmark.test is expect a fixed number of arguments.
    Hence to avoid this, any spaces are replaced by underscores */

    strcpy(data->sysname,operating_system.sysname);
    string_length=strlen(data->sysname);
    for(i=0;i<string_length; ++i)
    {
      if (data->sysname[i] == ' ')
        data->sysname[i]='_';
    }

    /* nodename should be safe, but I'll take no chances */
    strcpy(data->nodename,operating_system.nodename);
    string_length=strlen(data->nodename);
    for(i=0;i<string_length; ++i)
    {
      if (data->nodename[i] == ' ')
        data->nodename[i]='_';
    }

    /* not so with release */
    strcpy(data->release,operating_system.release);
    string_length=strlen(data->release);
    for(i=0;i<string_length; ++i)
    {
      if (data->release[i] == ' ')
        data->release[i]='_';
    }

    /* or version */
    strcpy(data->version,operating_system.version);
    string_length=strlen(data->version);
    for(i=0;i<string_length; ++i)
    {
      if (data->version[i] == ' ')
        data->version[i]='_';
    }

    strcpy(data->machine,operating_system.machine);
    string_length=strlen(data->machine);
    for(i=0;i<string_length; ++i)
    {
      if (data->machine[i] == ' ')
        data->machine[i]='_';
    }

#endif /* End of #ifdef HAVE_UNAME */

/* Try to get the number of processors online. This seems to be 
at least semi portable, as its used by both AIX and Solaris.
*/

#ifdef HAVE_SYSCONF  /* many systems seem to have sysconf(), 
which takes an integer argument and returns a long. The 
arugment detemines what gets returned. */

#ifdef _SC_NPROCESSORS_ONLN  /* Get the CPUs online */
    if(sysconf(_SC_NPROCESSORS_ONLN) >= 1)
      sprintf(data->cpus,"%ld",sysconf(_SC_NPROCESSORS_ONLN));
#endif

  /* Obtain the RAM. This is a bit of a hack using doubles for 
  this, but longs overflow and long long is not strictly 
  in the ANSI standard. */

#ifdef _SC_PHYS_PAGES
#ifdef _SC_PAGESIZE

/* This might look a bit of a hack to use a double to compute
memory size in Mb, when any machine now will have an
integer multiple of Mb. However, the problem is that the
way to do this (multiplying the size of a memory page in 
bytes by the number of memory pages), produce the ram in bytes.
That will likely overflow a long on a 32-bit machine. So a 
double is used, divided by the number of  bytes per Mb, then
printed as a long. 

I hope that makes some sense */

  if ((long) sysconf(_SC_PHYS_PAGES) > 0L)
  {
    if ((long) sysconf(_SC_PAGESIZE) > 0L)
    {
      ram=(double) sysconf(_SC_PAGESIZE);
      ram*= (double) sysconf(_SC_PHYS_PAGES);
      {
        ram=ram/BYTES_PER_MB;
        sprintf(data->memory,"%ld",(long) (ram+0.05));
      }
    }
  }
#endif /* End of HAVE__SC_PHYS_PAGES */
#endif  /* End of  HAVE__SC_PHYS_PAGES */

#endif /* End of #ifdef HAVE_SYSCONF */
    return(0);
  }
}
