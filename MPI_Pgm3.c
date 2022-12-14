#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
    int size, rank, root = 0;

    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 10;

    int a[100], b[100], c[100];

    printf("Array A : \n");
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 10;
        printf("%d ", a[i]);
    }

    printf("\n");

    printf("Array B : \n");
    for (int i = 0; i < n; i++)
    {
        b[i] = rand() % 10;
        printf("%d ", b[i]);
    }

    printf("\n");

    int subsize = n / size;

    int *ap = malloc(subsize * sizeof(int));
    int *bp = malloc(subsize * sizeof(int));
    int *cp = malloc(subsize * sizeof(int));

    MPI_Scatter(a, subsize, MPI_INT, ap, subsize, MPI_INT, root, MPI_COMM_WORLD);

    MPI_Scatter(b, subsize, MPI_INT, bp, subsize, MPI_INT, root, MPI_COMM_WORLD);

    for (int i = 0; i < subsize; i++)
    {
        cp[i] = ap[i] + bp[i];
    }

    MPI_Gather(cp, subsize, MPI_INT, c, subsize, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root)
    {
        printf("\n");

        printf("Res : \n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", c[i]);
        }

        printf("\n");
    }
}