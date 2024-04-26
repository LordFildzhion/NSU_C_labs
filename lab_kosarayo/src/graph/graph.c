#include "graph.h"

node **create_graph(uint32_t n)
{
    node **graph = (node **)malloc(sizeof(node *) * n);
    for (uint32_t i = 0; i < n; i++)
    {
        graph[i] = (node *)malloc(sizeof(node));
        graph[i]->visited = NOT_VISITED;
        graph[i]->to_iterator = 0;
        graph[i]->to = (uint8_t *)malloc(MAX_VERTEX / 8);

        for (uint32_t j = 0; j < MAX_VERTEX / 8; j++)
            graph[i]->to[j] = 0;
    }

    return graph;
}

void initialization(node **graph, uint32_t m)
{
    for (uint32_t i = 0; i < m; i++)
    {
        int32_t to, from;
        scanf("%i%i", &from, &to);

        from--, to--;

        graph[from]->to[to / 8] |= (1 << (to % 8));
    }
}

node **reverse_graph(uint32_t n, node **original_graph)
{
    node **reversion_graph = create_graph(n);

    for (uint32_t i = 0; i < n; i++)
        for (uint32_t j = 0; j < n; j++)
            if (CAN_VISITED(original_graph, i, j))
                reversion_graph[j]->to[i / 8] |= (1 << (i % 8));

    return reversion_graph;
}

uint32_t *sort_vertexes(uint32_t *values, uint32_t n)
{
    pair_ui_32 *pairs = (pair_ui_32 *) malloc(sizeof(pair_ui_32) * n);
    for (uint32_t i = 0; i < n; i++)
        pairs[i] = make_pair(values[i], i);

    quicksort(pairs, 0, n - 1);

    uint32_t *answer = (uint32_t *) malloc(sizeof(uint32_t) * n);
    for (uint32_t i = 0; i < n; i++)
        answer[i] = pairs[i].b;

    free(pairs);

    return answer;
}

void sorting_dfs(node **graph, uint32_t n, uint32_t from, uint32_t *deep, uint32_t *p)
{
    if (graph[from]->visited == VISITED)
        return;

    graph[from]->visited = VISITED;
    
    for (int32_t to = 0; to < n; to++)
    {
        if (CAN_VISITED(graph, from, to) && graph[to]->visited == NOT_VISITED)
        {
            sorting_dfs(graph, n, to, deep, p);
        }
    }
    deep[from] = (*p)++;
}

uint32_t *get_value(uint32_t n, node **graph)
{

    uint32_t *deep = (uint32_t *)malloc(sizeof(uint32_t) * n);
    for (uint32_t i = 0; i < n; i++)
        deep[i] = INT32_MAX;
    
    deep[0] = 0;

    uint32_t p = 0;

    for (uint32_t i = 0; i < n; i++)
        if (graph[i]->visited == NOT_VISITED)
            sorting_dfs(graph, n, i, deep, &p);

    return deep;
}

void print_dfs(node **graph, uint32_t n, uint32_t from, int32_t *condition, int32_t *cnds)
{
    if (graph[from]->visited == VISITED)
        return;

    cnds[from] = *condition;
    graph[from]->visited = VISITED;

    for (uint32_t to = 0; to < n; to++)
        if (CAN_VISITED(graph, from, to))
            print_dfs(graph, n, to, condition, cnds);

}

void print_CSC(node **graph, uint32_t *vertexes, uint32_t n)
{
    int32_t condition = 1;

    int32_t *cnds = (int32_t *) malloc(sizeof(int32_t) * n);
    for (int i = 0; i < n; i++)
        cnds[i] = -1;

    for (int i = 0; i < n; i++)
    {
        if (graph[vertexes[i]]->visited != VISITED)
        {
            print_dfs(graph, n, vertexes[i], &condition, cnds);
            condition++;
        }
    }
    printf("%i\n", condition - 1);
    for (uint32_t j = 1; j <= condition; j++)
    {
        for (uint32_t i = 0; i < n; i++)
            if (cnds[i] == j)
                printf("%i ", i + 1);
        printf("\n");
    }
}

void delete_graph(node **graph, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        if (graph[i]->to != NULL)
            free(graph[i]->to);
        graph[i]->to = NULL;

        if (graph[i] != NULL)
            free(graph[i]);
        graph[i] = NULL;
    }

    if (graph != NULL)
        free(graph);
    graph = NULL;
}

void print_graph(node **graph, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        printf("%i: ", i);
        for (uint32_t j = 0; j < n; j++)
            if (CAN_VISITED(graph, i, j))
                printf("%i ", j);
        printf("\n");
    }
}