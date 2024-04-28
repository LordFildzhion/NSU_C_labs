#include "edge.h"

void delete_edges(edge **edges, uint32_t m)
{
    for (uint32_t i = 0; i < m; i++)
    {
        if (edges[i] != NULL)
            free(edges[i]);
        edges[i] = NULL;
    }

    if (edges != NULL)
        free(edges);
}

void swap_edges(edge *a, edge *b)
{
    edge c = *a;
    *a = *b;
    *b = c;
}

edge *remove_min(edge **heap, uint32_t *heap_size)
{
    edge *res = heap[0];
    uint32_t i = 0;
    heap[0] = heap[--(*heap_size)];

    while (1)
    {
        uint32_t j = i;

        if (2 * i + 1 < *heap_size && heap[2 * i + 1]->length < heap[j]->length)
            j = 2 * i + 1;

        if (2 * i + 1 < *heap_size && heap[2 * i + 2]->length < heap[j]->length)
            j = 2 * i + 2;

        if (i == j)
            break;

        swap_edges(heap[i], heap[j]);
    }

    return res;
}

void insert(edge **heap, edge *element, uint32_t number)
{
    uint32_t i = number;
    element->number = number;
    heap[number] = element;

    while (i > 0 && heap[i]->length < heap[(i - 1) / 2]->length)
    {
        swap_edges(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

edge **scan_edges(uint16_t n, uint32_t m)
{
    edge **edges = (edge **)malloc(sizeof(edge *) * m);

    for (uint32_t i = 0; i < m; i++)
        edges[i] = NULL;

    for (uint32_t i = 0; i < m; i++)
    {
        edge *e = (edge *)malloc(sizeof(edge));

        unsigned long long check_from, check_to, check_length;

        if (scanf("%llu%llu%llu", &check_from, &check_to, &check_length) < 3)
        {
            delete_edges(edges, m);
            printf("Bad number of lines\n");
            return NULL;
        }

        if (!(check_from <= n) || !(check_to <= n))
        {
            delete_edges(edges, m);
            printf("Bad vertex\n");
            return NULL;
        }

        if (!(check_length <= INT32_MAX))
        {
            delete_edges(edges, m);
            printf("Bad length\n");
            return NULL;
        }

        e->use = false;
        e->from = (uint16_t)check_from - 1;
        e->to = (uint16_t)check_to - 1;
        e->length = (uint32_t)check_length;

        insert(edges, e, i);
    }

    return edges;
}