#include "graph.h"

node *tops;
node **create_graph(short *n)
{
    tops = (node *) malloc(*n * sizeof(node));
    node **graph = (node **) malloc(*n * sizeof(node*));
    for (short i = 0; i < *n; i++)
    {
        graph[i] = &(tops[i]);
        graph[i]->it_to = 0;
        graph[i]->value = (short)(i + 1);
        graph[i]->visited = 0;
        graph[i]->to = (char *) malloc((*n + 7) / 8 * sizeof(char));
    }
    return graph;
}

void destroy_graph(node **graph, short *n)
{
    for (int i = 0; i < *n; i++)
        free(graph[i]->to);
    free(tops);
    free(graph);
}

short *ans, ans_it;
char dfs(node *nd, node **graph)
{
    if (nd->visited == 1)
    {
        printf("impossible to sort");
        return 1;
    }
    if (nd->visited == 2)
        return 0;
    nd->visited = 1;

    for (short i = 0; i < nd->it_to; i++)
    {
        if(dfs(graph[nd->to[i]], graph))
            return 1;
    }
    nd->visited = 2;
    ans[ans_it++] = nd->value;
    return 0;
}

void topological_sort(node **graph, short *n)
{
    ans = (short *)malloc(*n * sizeof(short));
    for (short i = 0; i < *n; i++)
    {
        if (graph[i]->visited == 0)
            if (dfs(graph[i], graph))
            {
                destroy_graph(graph, n);
                free(ans);
                exit(EXIT_SUCCESS);
            }
    }
    destroy_graph(graph, n);

    for (short i = *n - 1; i >= 0; i--)
        printf("%hu ", ans[i]);

    free(ans);
}

node **initialization(short *n, int *m)
{
    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);


    if (scanf("%hi%i", n, m) != 2)
        bad_number_of_lines();

    if (!(0 <= *n && *n <= MAX_N))
        bad_number_of_vertices();

    if (!(0 <= *m && *m <= MAX_M(*n)))
        bad_number_of_edges();

    node **graph = create_graph(n);

    for (int i = 0; i < *m; i++)
    {
        short to, from;
        if (scanf("%hi%hi", &from, &to) != 2)
        {
            destroy_graph(graph, n);
            bad_number_of_lines();
            return NULL;
        }

        if (!(1 <= to && to <= *n) || !(1 <= from && from <= *n))
        {
            destroy_graph(graph, n);
            bad_vertex();
            return NULL;
        }

        graph[from - 1]->to[graph[from - 1]->it_to++] = to - 1;
    }

    return graph;
}