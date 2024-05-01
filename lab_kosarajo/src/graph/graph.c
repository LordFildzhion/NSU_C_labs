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

bool initialization(node **graph, uint32_t n, uint32_t m)
{
    for (uint32_t i = 0; i < m; i++)
    {
        int32_t to, from;
        if (scanf("%i%i", &from, &to) != 2)
        {
            delete_graph(graph, n);
            printf("Bad number of lines\n");
            return true;
        }

        if (!(1 <= from && from <= n) || !(1 <= to && to <= n))
        {
            delete_graph(graph, n);
            printf("Bad vertex\n");
            return true;
        }

        from--, to--;

        graph[from]->to[to / 8] |= (1 << (to % 8));
    }

    return false;
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

void sorting_dfs(node **graph, uint32_t n, uint32_t from, uint32_t *deep, uint32_t *p)
{
    if (graph[from]->visited == VISITED)
        return;

    graph[from]->visited = VISITED;
    
    for (int32_t to = 0; to < n; to++)
        if (CAN_VISITED(graph, from, to))
            sorting_dfs(graph, n, to, deep, p);

    deep[(*p)++] = from;
}

void swap(uint32_t *a, uint32_t *b)
{
    uint32_t c = *a;
    *a = *b;
    *b = c;
}

void reverse(uint32_t *arr, uint32_t start, uint32_t end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

uint32_t *top_sort(uint32_t n, node **graph)
{
    uint32_t *vertexes = (uint32_t *)malloc(sizeof(uint32_t) * n);

    uint32_t p = 0;

    for (uint32_t i = 0; i < n; i++)
        if (graph[i]->visited == NOT_VISITED)
            sorting_dfs(graph, n, i, vertexes, &p);

    reverse(vertexes, 0, n - 1);

    return vertexes;
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
