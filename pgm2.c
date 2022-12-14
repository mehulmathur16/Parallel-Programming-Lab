#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, des, source, tag1 = 1, tag2 = 2, rc, count;

    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char outmsg[100] = "Hey There!";
    char inmsg[100];

    if (rank == 0)
    {
        des = 1;
        source = 1;

        rc = MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, des, tag1, MPI_COMM_WORLD);

        rc = MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, source, tag2, MPI_COMM_WORLD, &stat);
    }
    else if (rank == 1)
    {
        source = 0;
        des = 0;

        rc = MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, des, tag2, MPI_COMM_WORLD);

        rc = MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, source, tag1, MPI_COMM_WORLD, &stat);
    }

    rc = MPI_Get_count(&stat, MPI_CHAR, &count);

    printf("Task %d has reveived %d chars from task %d, with tag %d and msg is %s \n", rank, count, stat.MPI_SOURCE, stat.MPI_TAG, inmsg);

    MPI_Finalize();
}