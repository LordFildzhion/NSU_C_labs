#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector/vector.h"
#include "calc/calc.h"

#define MAX_SIZE (size_t)2000


int main()
{
    char str[MAX_SIZE] = "";
    if (fgets(str, MAX_SIZE * sizeof(char), stdin) == NULL)
        return 0;

    int n = strlen(str);
    str[n--] = '\0';

    if (checker(str, n))
        printf("syntax error\n");
    else
    {
        vector opn = op(str);
        printf("%i", calc(opn));
        delete_vector(&opn);
    }

    return 0;
}