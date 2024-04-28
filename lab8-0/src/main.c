#include "src/UFS/UFS.h"
#include "src/edge/edge.h"

void kruskal_algorithm(edge **edges, ufs_node **UFS, uint16_t n, uint32_t m)
{
    uint32_t heap_size = m, answer_size = 0;
    edge **answer = (edge **) malloc(sizeof(edge *) * m);

    for (uint32_t i = 0; i < m; i++)
    {
        edge *e = remove_min(edges, &heap_size);
        if (!same(UFS, e->from, e->to))
        {
            answer[answer_size++] = e;
            unite(UFS, e->from, e->to);
        }
    }

    bool key = false;

    for (uint16_t i = 0; i < n; i++)
        if (UFS[i]->size == n)
            key = true;

    if (key)
    {
        for (uint32_t i = 0; i < answer_size; i++)
        {
            printf("%i %i\n", answer[i]->from + 1, answer[i]->to + 1);
        }
    }
    else
    {
        printf("No spanning tree\n");
    }
}

enum {MAX_N = 5000};
#define MAX_M(N) (N * (N + 1) / 2)

int main()
{

    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    /*if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);*/

    int32_t check_n, check_m;

    if (scanf("%i%i", &check_n, &check_m) < 2)
    {
        printf("Bad number of lines\n");
        return 0;
    }

    if (check_n == 0 || (check_m == 0 && check_n > 1))
    {
        printf("No spanning tree\n");
        return 0;
    }
    else if (check_m == 0)
    {
        return 0;
    }

    if (!(0 <= check_n && check_n <= MAX_N))
    {
        printf("Bad number of vertices\n");
        return 0;
    }

    if (!(0 <= check_m && check_m <= MAX_M(check_n)))
    {
        printf("Bad number of edges\n");
        return 0;
    }

    uint16_t n = (uint16_t)check_n;
    uint32_t m = (uint32_t)check_m;

    ufs_node **UFS = create_UFS(n);

    edge **edges = scan_edges(n, m);

    if (edges == NULL)
    {
        delete_UFS(UFS, n);
        return 0;
    }

    kruskal_algorithm(edges, UFS, n, m);

    return 0;
}

#undef MAX_M