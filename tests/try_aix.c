/* Try to get data. This will work only on an IBM running AIX */

#include "defs.h"
#define BYTES_PER_MB  1048576

#ifdef HAVE_AIXFONT_H
#ifdef HAVE_UNISTD_H
#ifdef HAVE_STRING_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_STDIO_H  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#endif
#endif
#endif
#endif
#endif

int try_aix(struct computer_data *data)
{
#ifdef HAVE_AIXFONT_H
#ifdef HAVE_UNISTD_H
#ifdef HAVE_STRING_H
#ifdef HAVE_STDLIB_H
#ifdef HAVE_STDIO_H  
  long ram_in_kb;
  char *model;
  model=malloc(12);
  strcpy(data->hw_provider,"IBM");
  strncpy(model,data->machine,10);
  model+=8;
  if(strcmp(model,"02") == 0)
  {
    strcpy(data->hw_platform,"7015-930");
    strcpy(data->mhz,"25");
    strcpy(data->cpu_type,"Power");
    strcpy(data->max_cpus,"1");
  }
  if(strcmp(model,"10") == 0)
  {
    strcpy(data->hw_platform,"7015-930_or_7016-730");
    strcpy(data->mhz,"25");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"11") == 0)
  {
    strcpy(data->hw_platform,"7013-540");
    strcpy(data->mhz,"30");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"14") == 0)
  {
    strcpy(data->hw_platform,"7013-540");
    strcpy(data->mhz,"30");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"18") == 0)
  {
    strcpy(data->hw_platform,"7013-53H");
    strcpy(data->mhz,"33");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"1C") == 0)
  {
    strcpy(data->hw_platform,"7013-550");
    strcpy(data->mhz,"41.6");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"20") == 0)
  {
    strcpy(data->hw_platform,"7015-930");
    strcpy(data->mhz,"25");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"2E") == 0)
  {
    strcpy(data->hw_platform,"7015-950");
    strcpy(data->mhz,"41");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"30") == 0)
  {
    strcpy(data->hw_platform,"7013-520");
    strcpy(data->mhz,"20");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"31") == 0)
  {
    strcpy(data->hw_platform,"7012-320");
    strcpy(data->mhz,"20");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"34") == 0)
  {
    strcpy(data->hw_platform,"7013-52H");
    strcpy(data->mhz,"25");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"35") == 0)
  {
    strcpy(data->hw_platform,"7012-32H");
    strcpy(data->mhz,"25");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"37") == 0)
  {
    strcpy(data->hw_platform,"7012-340");
    strcpy(data->mhz,"33");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"38") == 0)
  {
    strcpy(data->hw_platform,"7012-350");
    strcpy(data->mhz,"41");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"41") == 0)
  {
    strcpy(data->hw_platform,"7011-220");
    strcpy(data->mhz,"33");
    strcpy(data->cpu_type,"RSC");
  }
  if(strcmp(model,"43") == 0)
  {
    strcpy(data->hw_platform,"7008-M20_or_7008-M2A");
    strcpy(data->mhz,"33");
    strcpy(data->cpu_type,"Power");
  }
  if(strcmp(model,"46") == 0)
  {
    strcpy(data->hw_platform,"7011-250");
    strcpy(data->mhz,"66");
    strcpy(data->cpu_type,"PowerPC");
  }
  if(strcmp(model,"47") == 0)
  {
    strcpy(data->hw_platform,"7011-230");
    strcpy(data->mhz,"45");
    strcpy(data->cpu_type,"RSC");
  }
  if(strcmp(model,"48") == 0)
  {
    strcpy(data->hw_platform,"7009-C10");
    strcpy(data->mhz,"80");
    strcpy(data->cpu_type,"PowerPC");
  }
  if(strcmp(model,"57") == 0)
  {
    strcpy(data->hw_platform,"9076-SP2_Thin_or_9076-SP2_Thin");
    strcpy(data->mhz,"67");
    strcpy(data->cpu_type,"Power2");
  }
  if(strcmp(model,"58") == 0)
  {
    strcpy(data->hw_platform,"7012-380_or_7030-3AT");
    strcpy(data->mhz,"59");
    strcpy(data->cpu_type,"Power2");
  }
  if(strcmp(model,"59") == 0)
  {
    strcpy(data->hw_platform,"9076-SP2_Thin_w-L2");
    strcpy(data->mhz,"67");
    strcpy(data->cpu_type,"Power2");
  }
#ifdef _SC_NPROCESSORS_ONLN
  sprintf(data->cpus,"%ld",sysconf(_SC_NPROCESSORS_ONLN));
#endif

#ifdef _SC_AIX_REALMEM
  sprintf(data->memory,"%ld",sysconf(_SC_AIX_REALMEM)/1024);
#endif

  return(PROBABLY_AIX);
#endif
#endif
#endif
#endif
#endif
  return(-1);
}
