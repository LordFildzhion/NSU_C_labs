#include "pair.h"

void swap(pair_ui_32 *a, pair_ui_32 *b)
{
    pair_ui_32 c = *a;
    *a = *b;
    *b = c;
}

int partition(pair_ui_32 *arr, int low, int hight)
{
    int mid = arr[(low + hight) / 2].a, i = low, j = hight;

    while (1)
    {
        while (arr[i].a > mid && i < hight)
            i++;
        while (arr[j].a < mid && j > low)
            j--;

        if (i >= j)
            return j;

        swap(&arr[i++], &arr[j--]);
    }
}

void quicksort(pair_ui_32 *arr, int low, int hight)
{
    if (low < hight)
    {
        int part = partition(arr, low, hight);
        quicksort(arr, low, part);
        quicksort(arr, part + 1, hight);
    }
}

pair_ui_32 make_pair(uint32_t a, uint32_t b)
{
    pair_ui_32 p;
    p.a = a;
    p.b = b;
    return p;
}