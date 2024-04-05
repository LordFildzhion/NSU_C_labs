#include "graph/graph.h"

int main()
{
    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);

    uint16_t n;

    node **graph = create_graph(&n);

    initialization(graph, n);

    topological_sort(graph, n);

    return 0;
}
