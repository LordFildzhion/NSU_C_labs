#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../errors/errors.h"

#define MAX_N (int32_t)2000
#define MAX_M(x) (int32_t)(x * (x - 1) / 2)

typedef struct Node
{
    uint8_t visited;
    uint8_t *to;
} node;

node **create_graph(uint16_t *n);

void initialization(node **graph, uint16_t n);

void topological_sort(node **graph, uint16_t n);

void delete_graph(node **graph, uint16_t n);
