#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Edge
{
    uint16_t from;
    uint16_t to;
    uint32_t number;
    int32_t length;
} edge;

void delete_edges(edge *edges);

edge *scan_edges(uint16_t n, uint32_t m);

