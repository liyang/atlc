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
  struct utsname name;
  int ret;

  ret=uname(&name);
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
    strcpy(data->sysname,name.sysname);
    strcpy(data->nodename,name.nodename);
    strcpy(data->release,name.release);
    strcpy(data->version,name.version);
    strcpy(data->machine,name.machine);
    return(0);
  }
#endif
  return(1);
}
