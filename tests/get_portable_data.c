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

int get_portable_data(char *mhz, char *cpus, char *max_cpus, char *sysname, \
char *nodename, char *release, char *version, char *machine, \
char *cpu_type, char *fpu_type, char *memory,char *manufactuer, char *hw_platform)
{
#ifdef HAVE_UNAME
  struct utsname name;
  uname(&name);
  strcpy(sysname,name.sysname);
  strcpy(nodename,name.nodename);
  strcpy(release,name.release);
  strcpy(version,name.version);
  strcpy(machine,name.machine);
  return(0);
#endif
  return(1);
}
