#ifndef PAIR_H
#define PAIR_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pair_ui_32
{
    uint32_t a;
    uint32_t b;
} pair_ui_32;

void quicksort(pair_ui_32 *arr, int low, int hight);

pair_ui_32 make_pair(uint32_t a, uint32_t b);

#endif