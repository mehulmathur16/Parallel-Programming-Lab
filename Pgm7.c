#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define max 100

int main()
{

    int sum = 0;

#pragma omp parallel for
    for (int i = 1; i <= max; i++)
#pragma omp critical
        sum += i;

    printf("Sum : %d", sum);
    return 0;
}