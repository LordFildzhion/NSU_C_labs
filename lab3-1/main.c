#include <stdio.h>
#include <stdlib.h>

/*
**Time Complexity:
** Worst-case: O(N^2)
** Average-case: O(N log N)
** Best-case: O(N log N)
**
** Auxiliary Space:
** Worst-case: O(N)
** Average-case: O(log N)
** Best-case: O(log N)
**
*/

#define MAXSIZE 2000000

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int *arr, int low, int hight)
{
    int mid = arr[(low + hight) / 2], i = low, j = hight;

    while (1)
    {
        while (arr[i] < mid)
            i++;
        while (arr[j] > mid)
            j--;

        if (i >= j)
            return j;

        swap(&arr[i++], &arr[j--]);
    }
}

void quicksort(int *arr, int low, int hight)
{
    if (low < hight)
    {
        int part = partition(arr, low, hight);
        quicksort(arr, low, part);
        quicksort(arr, part + 1, hight);
    }
}

int main()
{
    int n;

    if (scanf("%i", &n) <= 0)
        return 0;

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        if (scanf("%i", &arr[i]) <= 0)
            return 0;

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%i ", arr[i]);

    return 0;
}
