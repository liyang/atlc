

#define MAX_SIZE        40
#define SLEEPTIME       80

#define PROBABLY_LINUX   1
#define PROBABLY_HPUX    2
#define PROBABLY_AIX     3
#define PROBABLY_TRU64   4
#define PROBABLY_OPENBSD 5
#define PROBABLY_NETBSD  6
#define PROBABLY_IRIX    7
#define PROBABLY_SOLARIS 8

typedef struct computer_data{
char mhz[MAX_SIZE], cpus[MAX_SIZE], max_cpus[MAX_SIZE];
char sysname[MAX_SIZE];
char nodename[MAX_SIZE], release[MAX_SIZE];
char version[MAX_SIZE], machine[MAX_SIZE];
char cpu_type[MAX_SIZE], fpu_type[MAX_SIZE];
char memory[MAX_SIZE], hw_provider[MAX_SIZE];
char hw_platform[MAX_SIZE], eff[MAX_SIZE], speedup[MAX_SIZE];
}a;
int try_solaris(struct computer_data *data);
