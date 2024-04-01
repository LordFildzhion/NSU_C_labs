#ifndef LAB7_GRAPH_H
#define LAB7_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "../errors/errors.h"


#define MAX_N (short)2000
#define MAX_M(x) (int)(x * (x - 1) / 2)


typedef struct node{
    char visited; // 0 - not visited | 1 - visited, but don't out | 2 - visited and out
    char *to;
    short it_to;
    short value;
}node;

void destroy_graph(node **graph, short *n);

void topological_sort(node **graph, short *n);

node **initialization(short *n, int *m);

#endif
