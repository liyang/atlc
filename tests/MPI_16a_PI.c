#ifdef ENABLE_MPI
#include <mpi.h>
#endif

#include <stdio.h>
#include <math.h>

#ifdef ENABLE_MPI
double f(double);

double f(double a)
{
    return (4.0 / (1.0 + a*a));
}
#endif

int main(int argc,char *argv[])
{
#ifdef ENABLE_MPI
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);


    n = 0;
    while (!done)
    {
        if (myid == 0)
        {
/*
            printf("Enter the number of intervals: (0 quits) ");
            scanf("%d",&n);
*/
	    if (n==0) n=10000; else n=0;

	    startwtime = MPI_Wtime();
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
            h   = 1.0 / (double) n;
            sum = 0.0;
	    /* A slightly better approach starts from large i and works back */
            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0)
	    {
                /* printf("pi is approximately %.16f, Error is %.16f\n",
                       pi, fabs(pi - PI25DT)); */
                if (fabs(pi - PI25DT) > 0.00000001 )
		{
		  MPI_Finalize();
		  return 1;
                }
		endwtime = MPI_Wtime();
		//printf("wall clock time = %f\n", endwtime-startwtime);	       
		fflush( stdout );
	    }
        }
    }
    MPI_Finalize();
    return 0;
#endif
    return 77;
}
