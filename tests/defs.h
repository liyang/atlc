

#define MAX_SIZE        40 
#define SLEEPTIME       80

#define PROBABLY_AIX       1         /* As used on IBM's                 */
#define PROBABLY_FREEBSD   2         /* Runs on a number of systems      */
#define PROBABLY_HPUX      3         /* As used on HP's                  */
#define PROBABLY_IRIX      4         /* As used on SGI's                 */
#define PROBABLY_LINUX     5         /* Run on a number of systems       */
#define PROBABLY_NETBSD    6         /* Runs on a HUGE range of systems  */
#define PROBABLY_OPENBSD   7         /* Runs on a number of systems      */
#define PROBABLY_SOLARIS   8         /* Runs on Suns and PCs             */
#define PROBABLY_TRU64     9         /* Runs on Decs, Compaqs and HPs    */
#define PROBABLY_UNICOS   10         /* Runs on Cray supercomputers      */

typedef struct computer_data{
char mhz[MAX_SIZE];                  /* Speed in MHz. Note its a string */
char cpus[MAX_SIZE];                 /* Number of CPUs running          */
char max_cpus[MAX_SIZE];             /* Maximum number of CPUs support by system */
char sysname[MAX_SIZE];              /* System name - got by uname */
char nodename[MAX_SIZE];             /* nodename - got via uname            */
char release[MAX_SIZE];              /* Got via uname, but often wrong      */
char version[MAX_SIZE];              /* Version of the OS. Sometimes wrong. */
char machine[MAX_SIZE];              /* Machine name                        */
char cpu_type[MAX_SIZE*3];           /* The CPU type                        */
char fpu_type[MAX_SIZE*3];           /* The FPU type                        */
char memory[MAX_SIZE];               /* The memory in Mb                    */ 
char hw_provider[MAX_SIZE];          /* The hardware provider - Sun, IBM etc */
char hw_platform[MAX_SIZE];          /* The hardware platform - eg sun4u    */
char t1[MAX_SIZE];                   /* Time in s to run benchmark single threaded */
char t2[MAX_SIZE];                   /* Time in s to run benchmark multi threaded */
char speedup[MAX_SIZE];              /* t1/t2 */
char eff[MAX_SIZE];                  /* The efficiency - t1/(t2*cpus)     */
char L1data[MAX_SIZE];               /* Size of level 1 data cache in kb  */
char L1instruction[MAX_SIZE];        /* Size of level 1 instuction cache in kb */
char L2[MAX_SIZE];                   /* Size of L2 cache                  */ 
}a;

/* The following functions try to fill in the structure above. Note the first
try_portable(), will use uname to get what information it can in a portable
manner. Any information it can't obtain it will replace with 'unknown'. The
fuctions below it then attempt to fill in the data for aix, solaris etc, having
verified the system is indeed a and AIX, Solaris or whatever machine. Note
that the fuctions that exist for obtaining data on Linux boxes is very
sparten and I could do with some help in improving the information 
gathered there. */

int try_portable(struct computer_data *data); /* Gather data using 'uname' */

int try_aix(struct computer_data *data);  /* Gather data IBM's AIX machines */
int try_irix(struct computer_data *data);
int try_hpux(struct computer_data *data);
int try_linux(struct computer_data *data);  /* THIS NEEDS IMPROVING !!!! */
int try_solaris(struct computer_data *data);
int try_tru64(struct computer_data *data);
int try_unicos(struct computer_data *data);
