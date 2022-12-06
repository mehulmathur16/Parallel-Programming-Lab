#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{

    int iterations;
    scanf("%d", &iterations);

#pragma omp parallel for schedule(static, 2)
    for (int i = 1; i <= iterations; i++)
    {
        int t = omp_get_thread_num();

        printf("Thread %d is running iteration %d \n", t, i);
    }

    return 0;
}