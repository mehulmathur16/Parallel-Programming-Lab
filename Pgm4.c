#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n)
{
    int a = 0, b = 1, c;

#pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++)
    {
#pragma omp critical
        {
            c = a + b;
            a = b;
            b = c;
        }
    }

    return b;
}

int main()
{
    int n = 20;

    double start = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        int t = omp_get_thread_num();

        printf("Thread %d : fib(%d) is %d \n", t, i, fib(i));
    }

    double end = omp_get_wtime();

    printf("Time taken is %f \n", end - start);

    return 0;
}