#include "UFS.h"

ufs_node **create_UFS(uint16_t n, ufs_node *ufs)
{
    ufs_node **UFS = (ufs_node **)malloc(sizeof(ufs_node *) * n);
    ufs = (ufs_node *) malloc(sizeof(ufs_node) * n);
    for (uint16_t i = 0; i < n; i++)
    {
        UFS[i] = &ufs[i];

        UFS[i]->link = i;
        UFS[i]->size = 1;
    }

    return UFS;
}

void delete_UFS(ufs_node **UFS, ufs_node *ufs)
{
    free(UFS);
    UFS = NULL;

    free(ufs);
    ufs = NULL;
}

uint16_t find(ufs_node **UFS, uint16_t x)
{
    if (x == UFS[x]->link)
        return x;
    return UFS[x]->link = find(UFS, UFS[x]->link);
}

bool same(ufs_node **UFS, uint16_t a, uint16_t b)
{
    return find(UFS, a) == find(UFS, b);
}

void swap(uint16_t *a, uint16_t *b)
{
    uint16_t c = *a;
    *a = *b;
    *b = c;
}

void unite(ufs_node **UFS, uint16_t a, uint16_t b)
{
    a = find(UFS, a);
    b = find(UFS, b);

    if (UFS[a]->size < UFS[b]->size)
        swap(&a, &b);

    UFS[a]->size += UFS[b]->size;
    UFS[b]->link = UFS[a]->link;
}