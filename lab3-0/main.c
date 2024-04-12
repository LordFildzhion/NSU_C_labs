#include <stdio.h>
#include <stdlib.h>

/*
**Time Complexity:
** Worst-case: O(N log N)
** Average-case: O(N log N)
** Best-case: O(N log N)
*/

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int remove_min(int *heap, int *heap_size)
{
    int res = heap[0], i = 0;
    heap[0] = heap[--*heap_size];
    
    while (1)
    {
        int j = i;

        if (2 * i + 1 < *heap_size && heap[2 * i + 1] < heap[j])
            j = 2 * i + 1;

        if (2 * i + 1 < *heap_size && heap[2 * i + 2] < heap[j])
            j = 2 * i + 2;

        if (i == j)
            break;

        swap(&heap[i], &heap[j]);
    }

    return res;
}

void insert(int *heap, int element, int number)
{
    int i = number;
    heap[number++] = element;

    while (i > 0 && heap[i] < heap[(i - 1) / 2])
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main()
{

    int heap_size = 0;
    int *heap = (int *) malloc(sizeof(int) * heap_size);

    if (scanf("%i", &heap_size) <= 0)
    {
        free(heap);
        return 0;
    }

    for (int i = 0; i < heap_size; i++)
    {
        if (scanf("%i", &heap[i]) <= 0)
        {
            free(heap);
            return 0;
        }

        insert(heap, heap[i], i);
    }

    int n = heap_size;
    for (int i = 0; i < n; i++)
        printf("%i ", remove_min(heap, &heap_size));


    free(heap);
    return 0;
}