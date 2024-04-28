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

edge **scan_edges(uint16_t n, uint32_t m)
{
    edge **edges = (edge **)malloc(sizeof(edge *) * m);

    for (uint32_t i = 0; i < m; i++)
        edges[i] = NULL;

    for (uint32_t i = 0; i < m; i++)
    {
        edges[i] = (edge *)malloc(sizeof(edge));

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

        edges[i]->from = (uint16_t)check_from - 1;
        edges[i]->to = (uint16_t)check_to - 1;
        edges[i]->length = (uint32_t)check_length;

    }

    return edges;
}