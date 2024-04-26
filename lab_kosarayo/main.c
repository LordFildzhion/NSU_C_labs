#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "src/graph/graph.h"

int main()
{
    int32_t n, m;
    scanf("%i%i", &n, &m);

    node **graph = create_graph(n);

    initialization(graph, m);

    node **reversion_graph = reverse_graph(n, graph);

    uint32_t *sort_origin = sort_vertexes(get_value(n, graph), n);

    delete_graph(graph, n);

    print_CSC(reversion_graph, sort_origin, n);

    delete_graph(reversion_graph, n);

    free(sort_origin);

    return 0;
}
