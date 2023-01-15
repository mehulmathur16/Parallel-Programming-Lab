#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define numSteps 1000000

int main()
{
    double pi = 0;

    // serial
    double start = omp_get_wtime();

    for (int k = 0; k < numSteps; k++)
    {
        pi += (pow(-1, k)) / (2 * k + 1);
    }

    pi = 4 * pi;

    double end = omp_get_wtime();

    printf("The value of Pi in serial execution is %lf and time taken is %lf \n", pi, end - start);

    // parallel
    pi = 0;
    start = omp_get_wtime();
    omp_set_num_threads(4);

    int size = omp_get_num_threads();
    double thread[size];

#pragma omp parallel for
    for (int k = 0; k < numSteps; k++)
    {
        int t = omp_get_thread_num();
        thread[t] += (pow(-1, k)) / (2 * k + 1);
    }

    for (int i = 0; i < size; i++)
    {
        pi += thread[i];
    }

    pi = 4 * pi;

    end = omp_get_wtime();

    printf("The value of Pi in Parallel execution is %lf and time taken is %lf \n", pi, end - start);

    return 0;
}