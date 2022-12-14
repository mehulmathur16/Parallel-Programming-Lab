#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
    char outmsg[100] = "Welcome to ise";
    char inmsg[100];

    int numtasks, rank, dest, source, count, tag = 1, rc;

    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        dest = 1;
        rc = MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        source = 0;
        rc = MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, source, tag, MPI_COMM_WORLD, &stat);
    }

    rc = MPI_Get_count(&stat, MPI_CHAR, &count);

    printf("Task %d received %d chars from task %d with tag %d and message %s\n", rank, count, stat.MPI_SOURCE, stat.MPI_TAG, inmsg);

    MPI_Finalize();
}