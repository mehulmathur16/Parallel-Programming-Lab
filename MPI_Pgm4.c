#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
    int size, rank;
    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 7, root = 0, global;

    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

    int localprod = 1;
    int len = (n / size) + 1;

    for (int i = (rank * len) + 1; i <= ((rank + 1) * len); i++)
    {
        if (i > n)
            break;

        localprod *= i;
    }

    printf("LocalProd : %d \n", localprod);

    MPI_Reduce(&localprod, &global, 1, MPI_INT, MPI_PROD, root, MPI_COMM_WORLD);

    if (rank == root)
    {
        printf("The factorial of %d is %d\n", n, global);
    }

    MPI_Finalize();
}