#include "edge.h"

void delete_edges(edge **edges, edge *tops, uint32_t m)
{
    free(edges);
    edges = NULL;

    free(tops);
    tops = NULL;
}

edge **scan_edges(edge *tops,uint16_t n, uint32_t m)
{
    edge **edges = (edge **)malloc(sizeof(edge *) * m);

    for (uint32_t i = 0; i < m; i++)
        edges[i] = NULL;
    
    tops = (edge *) malloc(sizeof(edge) * m);

    bool *prikol = (bool *) malloc(sizeof(bool) * m);
    for (uint32_t i = 0; i < m; i++)
        prikol[i] = false;

    for (uint32_t i = 0; i < m; i++)
    {
        edges[i] = &tops[i];

        unsigned long long check_from, check_to, check_length;

        if (scanf("%llu%llu%llu", &check_from, &check_to, &check_length) < 3)
        {
            delete_edges(edges, tops, m);
            printf("Bad number of lines\n");
            return NULL;
        }

        if (!(check_from <= n) || !(check_to <= n))
        {
            delete_edges(edges, tops, m);
            printf("Bad vertex\n");
            return NULL;
        }

        if (!(check_length <= INT32_MAX))
        {
            delete_edges(edges, tops, m);
            printf("Bad length\n");
            return NULL;
        }

        if (prikol[i])
            if (edges[i]->length < (int32_t)check_length)
                continue;
        
        prikol[i] = true;
        edges[i]->from = (uint16_t)check_from - 1;
        edges[i]->to = (uint16_t)check_to - 1;
        edges[i]->length = (int32_t)check_length;

    }
    
    free(prikol);

    return edges;
}