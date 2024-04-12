#ifndef CALC_H
#define CLAC_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../vector/vector.h"

#define MAX_SIZE (size_t)2000


vector op(char *str);

int calc(vector v);

int checker(char *str, int size);

#endif