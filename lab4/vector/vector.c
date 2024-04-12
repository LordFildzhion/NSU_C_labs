#include "vector.h"

void insert(vector *v, int x)
{
    if (v->data_size == v->count + 1)
    {
        v->data_size += DELTA_STACK_SIZE;
        v->data = (int *)realloc(v->data, v->data_size + DELTA_STACK_SIZE);
    }
    v->data[++v->count] = x;
}

int pop(vector *v)
{
    v->count--;
    return v->data[v->count + 1];
}

int back(vector *v)
{
    return v->data[v->count];
}

int is_empty(vector *v)
{
    return (v->count == -1);
}

void delete_vector(vector *v)
{
    free(v->data);
}

vector new_vector()
{
    vector v;
    v.count = -1;
    v.data_size = DELTA_STACK_SIZE;
    v.data = (int *)malloc(sizeof(int) * v.data_size);
    return v;
}
