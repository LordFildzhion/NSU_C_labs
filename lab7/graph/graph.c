#include "graph.h"

node **create_graph(uint16_t *n)
{
    int check_n;
    if (scanf("%i", &check_n) != 1)
        bad_number_of_lines();

    if (!(0 <= check_n && check_n <= MAX_N))
        bad_number_of_vertices();
        
    *n = check_n;
    node **graph = (node **) malloc(sizeof(node *) * (*n));
    for (uint16_t i = 0; i < *n; i++)
    {
        graph[i] = (node *) malloc(sizeof(node));
        graph[i]->visited = 0;
        graph[i]->to = (uint8_t *) malloc(sizeof(uint8_t) * ((*n + 7) / 8));
        for (int j = 0; j < (*n + 7) / 8; j++)
            graph[i]->to[j] = 0;
    }
    return graph;
}


void delete_graph(node **graph, uint16_t n)
{
    for (uint16_t i = 0; i < n ; i++)
    {
        free(graph[i]->to);
        free(graph[i]);
    }
    free(graph);
}


void initialization(node **graph, uint16_t n)
{
    int m;
    if (scanf("%i", &m) != 1)
        bad_number_of_lines();

    if (!(0 <= m && m <= MAX_M(n)))
        bad_number_of_edges();
    
    while(m--)
    {
        int to, from;

        if (scanf("%i%i", &from, &to) != 2)
        {
            delete_graph(graph, n);
            bad_number_of_lines();
        }

        if (!(1 <= to && to <= (int)n) || !(1 <= from && from <= (int)n))
        {
            delete_graph(graph, n);
            bad_vertex();
        }
        
        to--, from--;
        graph[from]->to[to / 8] |= (1 << (to % 8));
    }
}

bool dfs(node **graph, uint16_t n, uint16_t v, uint16_t *answer, uint16_t *answer_iterator)
{
    if (graph[v]->visited == 1)
        return true;

    if (graph[v]->visited == 2)
        return false;

    graph[v]->visited = 1;

    for (uint8_t i = 0; i < (uint8_t)((n + 7) / 8); i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (graph[v]->to[i] & (1 << j))
            {
                if (dfs(graph, n, i * 8 + j, answer, answer_iterator))
                    return true;
            }
        }
    }

    graph[v]->visited = 2;
    answer[(*answer_iterator)++] = v + 1;

    return false;
}

void topological_sort(node **graph, uint16_t n)
{
    uint16_t *answer = (uint16_t *) malloc(n * sizeof(uint16_t));
    uint16_t answer_iterator = 0;

    for (uint16_t i = 0; i < n; i++)
    {
        if (!graph[i]->visited && dfs(graph, n, i, answer, &answer_iterator))
        {
            printf("Impossible to sort");
            delete_graph(graph, n);
            free(answer);
            exit(EXIT_SUCCESS);
        }
    }

    for (uint16_t i = n - 1; i > 0; i--)
        printf("%i ", (int)answer[i]);
    printf("%i", (int)answer[0]);

    delete_graph(graph, n);
    free(answer);
}
