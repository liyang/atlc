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

#include "defs.h"

extern int errno;

int try_portable(struct computer_data *data)
{
#ifdef HAVE_UNAME
  struct utsname operating_system;
  int ret, i, string_length;

  ret=uname(&operating_system);
  if (ret == -1)
  {
#ifdef HAVE_ERRNO_H
    fprintf(stderr,"failure in call to uname in try_portable.c errno=%d\n", errno);
#else
    fprintf(stderr,"failure in call to uname in try_portable.c\n");
#endif
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
    return(0);
  }
#endif
  return(1);
}
