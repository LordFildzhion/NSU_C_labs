#ifndef GRAPH_H
#define GRAPH_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../errors/errors.h"

#define MAX_VERTEX 2000

#define CAN_VISITED(graph, f, t) ((bool)(graph[f]->to[t / 8] & (1 << (t % 8))))

enum conditions
{
    NOT_VISITED,
    VISITED
};

typedef struct Node
{
    uint8_t visited;
    uint8_t to_iterator;
    uint8_t *to;
} node;

node **create_graph(uint32_t n);

bool initialization(node **graph, uint32_t n, uint32_t m);

node **reverse_graph(uint32_t n, node **original_graph);

uint32_t *top_sort(uint32_t n, node **graph);

void print_CSC(node **graph, uint32_t *vertexes, uint32_t n);

void delete_graph(node **graph, uint32_t n);

void print_graph(node **graph, uint32_t n);

#endif
