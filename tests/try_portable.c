/* Try to get data. This will work only on a Solaris machine. */

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


#include "defs.h"

int try_portable(struct computer_data *data)
{
#ifdef HAVE_UNAME
  struct utsname name;
  uname(&name);
  strcpy(data->sysname,name.sysname);
  strcpy(data->nodename,name.nodename);
  strcpy(data->release,name.release);
  strcpy(data->version,name.version);
  strcpy(data->machine,name.machine);
  return(0);
#endif
  return(1);
}
