#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "../../src/non_gui/exit_codes.h"
#include "../../src/non_gui/definitions.h"

int main(int argc, char **argv)
{
  FILE *fp;
  int length;

  if(argc!=2)
  {
    printf("-1\n"); /* Length is considered -1 */
    exit(1);
  }
  if ( (fp=fopen(argv[1],"r")) == NULL)
  {
    printf("-1\n"); /* Length is considered -1 */
    exit(1);
  }
  fseek(fp,0,SEEK_END);
  length=ftell(fp);
  printf("%d\n",length);
  exit_with_msg_and_exit_code("",OKAY);
}
