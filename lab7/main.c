#include "graph/graph.h"

int main() {

    short n;
    int m;
    node **graph = initialization(&n, &m);

    topological_sort(graph, &n);

    return 0;
}

/*
6 10
5 4
2 4
6 1
5 2
6 4
2 1
5 6
3 1
6 2
5 1

*/
// 5 6 3 2 4 1
