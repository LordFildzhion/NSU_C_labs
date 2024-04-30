#include "UFS/UFS.h"
#include "edge/edge.h"

void kruskal_algorithm(edge *edges, ufs_node *UFS, uint16_t n, uint32_t m);

bool checker(uint16_t *n, uint32_t *m);

int compare(const void *first, const void *second);

int main()
{
    uint16_t n;
    uint32_t m;
    if (checker(&n, &m))
        return 0;

    ufs_node *UFS = create_UFS(n);

    edge *edges = scan_edges(n, m);

    if (edges == NULL)
    {
        delete_UFS(UFS);
        return 0;
    }

    qsort(edges, m, sizeof(edge), compare);
    kruskal_algorithm(edges, UFS, n, m);

    delete_edges(edges);

    delete_UFS(UFS);

    return 0;
}

int compare(const void *first, const void *second)
{
    return (*(edge *)first).length - (*(edge *)second).length;
}

#define MAX_N 5000
#define MAX_M(N) (N * (N + 1) / 2)

bool checker(uint16_t *n, uint32_t *m)
{
    if (!freopen("in.txt", "r", stdin))
        exit(EXIT_FAILURE);

    /*if (!freopen("out.txt", "w", stdout))
        exit(EXIT_FAILURE);*/

    int16_t check_n;
    int32_t check_m;

    if (scanf("%hi%i", &check_n, &check_m) < 2)
    {
        printf("Bad number of lines\n");
        return true;
    }

    if (check_n == 0 || (check_m == 0 && check_n > 1))
    {
        printf("No spanning tree\n");
        return true;
    }

    if (check_m == 0)
        return true;

    if (!(0 <= check_n && check_n <= MAX_N))
    {
        printf("Bad number of vertices\n");
        return true;
    }

    if (!(0 <= check_m && check_m <= MAX_M(check_n)))
    {
        printf("Bad number of edges\n");
        return true;
    }

    *n = (uint16_t)check_n;
    *m = (uint32_t)check_m;

    return false;
}

#undef MAX_M
#undef MAX_N

void kruskal_algorithm(edge *edges, ufs_node *UFS, uint16_t n, uint32_t m)
{
    FILE *out = fopen("out.txt", "w");

    bool key = true;

    for (uint32_t i = 0; i < m; i++)
    {
        if (!same(UFS, edges[i].from, edges[i].to))
        {
            unite(UFS, edges[i].from, edges[i].to);
            fprintf(out, "%i %i\n", edges[i].from + 1, edges[i].to + 1);
        }

        if (UFS[find(UFS, edges[i].from)].size == n)
        {
            key = false;
            break;
        }
    }

    if (key)
    {
        fseek(out, 0, SEEK_SET);
        fprintf(out, "No spanning tree\n");
    }

    fclose(out);
}

