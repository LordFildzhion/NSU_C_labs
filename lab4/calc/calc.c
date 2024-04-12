#include "calc.h"

#define MAX_SIZE (size_t)2000

int is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int get_priority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;

    return 0;
}

static int operators[MAX_SIZE] = {0};

vector op(char *str)
{
    vector operation_vector = new_vector();
    vector output_vector = new_vector();
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
        {
            char num[MAX_SIZE] = "";
            int num_null = i;

            while (isdigit(str[i]))
            {
                num[i - num_null] = str[i];
                i++;
            }

            i--;
            insert(&output_vector, atoi(num));
        }
        else if (is_operator(str[i]))
        {
            while (!is_empty(&operation_vector) && get_priority(back(&operation_vector)) >= get_priority(str[i]))
            {
                operators[output_vector.count + 1] = 1;
                insert(&output_vector, (int)pop(&operation_vector));
            }

            insert(&operation_vector, (int)str[i]);
        }
        else if (str[i] == '(')
            insert(&operation_vector, (int)str[i]);
        else if (str[i] == ')')
        {
            while (back(&operation_vector) != '(')
            {
                operators[output_vector.count + 1] = 1;
                insert(&output_vector, (int)pop(&operation_vector));
            }

            pop(&operation_vector);
        }
    }

    while (!is_empty(&operation_vector))
    {
        operators[output_vector.count + 1] = 1;
        insert(&output_vector, (int)pop(&operation_vector));
    }
    delete_vector(&operation_vector);

    return output_vector;
}

int calc(vector v)
{
    vector calc_vector = new_vector();

    for (int i = 0; i <= v.count; i++)
    {
        if (!operators[i])
            insert(&calc_vector, v.data[i]);
        else
        {
            int b = pop(&calc_vector);
            int a = pop(&calc_vector);
            switch (v.data[i])
            {
            case '/':
                if (b == 0)
                {
                    printf("division by zero\n");
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    insert(&calc_vector, a / b);
                }
                break;
            case '*':
                insert(&calc_vector, a * b);
                break;
            case '-':
                insert(&calc_vector, a - b);
                break;
            case '+':
                insert(&calc_vector, a + b);
                break;
            }
        }
    }

    int r = back(&calc_vector);
    delete_vector(&calc_vector);
    
    return r;
}

int checker(char *str, int size)
{
    int bracket = 0, check_num = 0;

    for (int i = 0; i < size; i++)
    {
        if (isdigit(str[i]))
            check_num = 1;

        if ((!isdigit(str[i])) && !is_operator(str[i]) && str[i] != '(' && str[i] != ')')
            return 1;

        if (str[i] == '(')
        {
            bracket++;

            if (i == size - 1)
                return 1;
            if (is_operator(str[i + 1]))
                return 1;
            if (i != 0 && isdigit(str[i - 1]))
                return 1;
        }

        else if (str[i] == ')')
        {
            bracket--;

            if (bracket < 0)
                return 1;
            if (i == 0)
                return 1;
            if (i != size - 1 && isdigit(str[i + 1]))
                return 1;
            if (isdigit(str[i + 1]))
                return 1;
        }

        else if (is_operator(str[i]))
        {
            if (i == 0 || i == size - 1)
                return 1;
            if (is_operator(str[i + 1]))
                return 1;
        }
    }

    if (check_num == 0)
        return 1;
    if (bracket != 0)
        return 1;

    return 0;
}