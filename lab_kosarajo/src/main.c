#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "graph/graph.h"

int main()
{
    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);


    int32_t n, m;
    if (scanf("%i%i", &n, &m) != 2)
    {
        bad_number_of_lines();
        exit(EXIT_SUCCESS);
    }

    if (!(0 <= n && n <= MAX_VERTEX))
    {
        bad_number_of_vertices();
        exit(EXIT_SUCCESS);
    }

    if (!(0 <= m && m <= (n * (n - 1) / 2)))
    {   
        bad_number_of_edges();
        exit(EXIT_SUCCESS);
    }

    node **graph = create_graph(n);

    initialization(graph, n, m);

    node **reversion_graph = reverse_graph(n, graph);

    uint32_t *sort_origin = top_sort(n, graph);

    delete_graph(graph, n);

    print_CSC(reversion_graph, sort_origin, n);

    delete_graph(reversion_graph, n);

    free(sort_origin);

    return 0;
}
