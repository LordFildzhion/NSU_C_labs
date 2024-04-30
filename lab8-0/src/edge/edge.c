#include "edge.h"

void delete_edges(edge **edges, edge *tops)
{
    free(tops);
    tops = NULL;

    free(edges);
    edges = NULL;
}

edge **scan_edges(edge *tops, uint16_t n, uint32_t m)
{
    edge **edges = (edge **)malloc(sizeof(edge *) * m);

    tops = (edge *) malloc(sizeof(edge) * m);

    for (uint32_t i = 0; i < m; i++)
        edges[i] = NULL;

    for (uint32_t i = 0; i < m; i++)
    {
        edges[i] = &tops[i];

        unsigned long long check_length, check_from, check_to;

        if (scanf("%llu%llu%llu", &check_from, &check_to, &check_length) < 3)
        {
            delete_edges(edges, tops);
            printf("Bad number of lines\n");
            return NULL;
        }

        if (!(check_from <= n) || !(check_to <= n))
        {
            delete_edges(edges, tops);
            printf("Bad vertex\n");
            return NULL;
        }

        if (!(check_length <= INT32_MAX))
        {
            delete_edges(edges, tops);
            printf("Bad length\n");
            return NULL;
        }

        edges[i]->from = (uint16_t)check_from - 1;
        edges[i]->to = (uint16_t)check_to - 1;
        edges[i]->length = (int32_t)check_length;

    }

    return edges;
}
