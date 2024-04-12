#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#define DELTA_STACK_SIZE (size_t)1000

typedef struct vector
{
    int *data;
    int data_size;
    int count;
} vector;

void insert(vector *v, int x);

int pop(vector *v);

int back(vector *v);

int is_empty(vector *v);

void delete_vector(vector *v);

vector new_vector();

#endif