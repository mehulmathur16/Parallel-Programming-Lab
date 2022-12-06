#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int isPrime(int x)
{
    for (int i = 2; i <= x / 2; i++)
    {
        if (x % i == 0)
            return 0;
    }

    return 1;
}

void serialPrime(int n)
{
    int x = 2;

    while (x <= n)
    {
        if (isPrime(x))
        {
            printf("%d ", x);
        }

        x++;
    }
}

void parallelPrime(int n)
{
    int x = 2;

#pragma omp parallel
    while (x <= n)
    {
        if (isPrime(x))
        {
            printf("%d ", x);
        }

#pragma omp atomic
        x++;
    }
}

int main(int argc, char *argv[])
{
    double start = omp_get_wtime();
    parallelPrime(100);
    double end = omp_get_wtime();

    printf("\n Time taken by Parallel execution is %f \n", end - start);

    start = omp_get_wtime();
    serialPrime(100);
    end = omp_get_wtime();

    printf("\n Time taken by Serial execution is %f \n", end - start);

    return 0;
}