#include "UFS/UFS.h"
#include "edge/edge.h"

void kruskal_algorithm(edge **edges, ufs_node **UFS, uint16_t n, uint32_t m)
{

    bool *ans = (bool *) malloc(sizeof(bool) * m), key = false;
    for (uint32_t i = 0; i < m; i++)
        ans[i] = false;

    for (uint32_t i = 0; i < m; i++)
    {
        if (!same(UFS, edges[i]->from, edges[i]->to))
        {
            unite(UFS, edges[i]->from, edges[i]->to);
            ans[i] = true;
        }

        if (UFS[find(UFS, edges[i]->from)]->size == n)
        {
            key = true;
            break;
        }
    }

    if (key)
    {
        for (uint32_t i = 0; i < m; i++)
            if (ans[i])
                printf("%i %i\n", edges[i]->from + 1, edges[i]->to + 1);
    }
    else
        printf("No spanning tree\n");

    free(ans);
}

enum {MAX_N = 5000};
#define MAX_M(N) (N * (N + 1) / 2)

int compare(const void *first, const void *second)
{
    return (*(edge **)first)->length - (*(edge **)second)->length;
}

int main()
{

    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);

    int16_t check_n;
    int32_t check_m;

    if (scanf("%hi%i", &check_n, &check_m) < 2)
    {
        printf("Bad number of lines\n");
        return 0;
    }

    if (check_n == 0 || (check_m == 0 && check_n > 1))
    {
        printf("No spanning tree\n");
        return 0;
    }

    if (check_m == 0)
        return 0;

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

    ufs_node *ufs = NULL;
    ufs_node **UFS = create_UFS(n, ufs);

    edge *tops = NULL;
    edge **edges = scan_edges(tops, n, m);

    if (edges == NULL)
    {
        delete_UFS(UFS, ufs);
        return 0;
    }

    qsort(edges, m, sizeof(edge*), compare);

    kruskal_algorithm(edges, UFS, n, m);

    delete_edges(edges, tops);

    delete_UFS(UFS, ufs);

    return 0;
}

#undef MAX_M