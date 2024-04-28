#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Edge
{
    bool use;
    uint16_t from;
    uint16_t to;
    uint32_t number;
    uint32_t length;
} edge;

void delete_edges(edge **edges, uint32_t m);
edge *remove_min(edge **heap, uint32_t *heap_size);
void insert(edge **heap, edge *element, uint32_t number);
edge **scan_edges(uint16_t n, uint32_t m);