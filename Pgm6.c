#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double *vectorAddition(double *a, double *b, double *c, int n)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }
}

int main()
{
    double a[] = {1, 2, 3, 4, 5};
    double b[] = {6, 7, 8, 9, 10};
    double c[5];

    int n = 5;

    vectorAddition(a, b, c, n);

    for (int i = 0; i < n; i++)
        printf("%f\n", c[i]);

    return 0;
}