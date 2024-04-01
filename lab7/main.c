#include "graph/graph.h"

int main() {

    short n;
    int m;
    node **graph = initialization(&n, &m);

    topological_sort(graph, &n);

    return 0;
}
