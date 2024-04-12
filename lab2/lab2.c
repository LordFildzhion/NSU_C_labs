#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1000
#define CHECKSIZE 10


void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void printArray(int array[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%i", array[i]);
    printf("\n");
}

void reverse(int arr[], int start, int end)
{
    while (start < end)
    {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

void nextPermutation(int *arr, int n)
{
    int i = n - 2;

    while (i >= 0 && arr[i] >= arr[i + 1])
        i--;

    if (i == -1)
        return;

    if (i >= 0)
    {
        int j = n - 1;
        while (arr[j] <= arr[i])
        {
            j--;
        }
        swap(&arr[i], &arr[j]);
    }

    reverse(arr, i + 1, n - 1);

    printArray(arr, n);
}

int main()
{
    int n;

    char p[MAXSIZE] = "";

    if (fgets(p, sizeof(p) / sizeof(char), stdin) == NULL || scanf("%i", &n) <= 0)
        return 1;

    int arr[MAXSIZE] = {0}, check[CHECKSIZE] = {0}, size = strlen(p) - 1;

    for (int i = 0; i < size; i++)
    {
        if (p[i] < '0' || p[i] > '9')
        {
            printf("bad input");
            return 0;
        }

        arr[i] = p[i] - '0';

        if (check[arr[i]])
        {
            printf("bad input");
            return 0;
        }

        check[p[i] - '0'] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        int j = size - 2;

        while (j >= 0 && arr[j] >= arr[j + 1])
            j--;

        if (j == -1)
            return 0;

        nextPermutation(arr, size);
    }
}
