#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int arr1[n1];
    int arr2[n2];

    for (int i = 0; i < n1; i++)
        arr1[i] = arr[low + i];

    for (int i = 0; i < n2; i++)
        arr2[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
    {
        if (arr1[i] <= arr2[j])
        {
            arr[k] = arr1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
            k++;
        }
    }

    while (i < n1)
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int low, int high)
{
    if (low == high)
        return;

    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void mergeSortParallel(int *arr, int low, int high)
{
    if (low == high)
        return;

    int mid = low + (high - low) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        mergeSort(arr, low, mid);
#pragma omp section
        mergeSort(arr, mid + 1, high);
    }
    merge(arr, low, mid, high);
}

int main()
{
    int n;
    printf("Enter the number of elements : ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    printf("Array before sorting : ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    double start = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    double end = omp_get_wtime();

    printf("\nArray after sorting : ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n Time taken in serial execution is %f \n", end - start);

    start = omp_get_wtime();
    mergeSortParallel(arr, 0, n - 1);
    end = omp_get_wtime();

    printf("\n Time taken in parallel execution is %f \n", end - start);
}