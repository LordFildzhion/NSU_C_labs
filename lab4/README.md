```Lab №7```

Input:

    A string of no more than 1000 characters

Output:

	If the input is not an integer arithmetic expression, then "Syntax error"

	If the input is an integer arithmetic expression and its calculation results in division by 0, then "Division by zero"

	Otherwise the meaning of the arithmetic expression


```Example 1```

Input:

    (((((

Output:

    Syntax error

```Example 2```

Input:
    
    1/0
Output:

    Division by zero

```Example 3```

Input:
    
    2*2

Output:

    4

```Example 4```

Input:
    
    bad input

Output:
    
    syntax error


```Example 5```

Input:

    2.0*2.0

Output:
    
    syntax error

```Example 6```

Input:

    123()

Output:
    
    syntax error

```Example 7```

Input:

    1*2+3/4

Output:
    
    2

```Example 8```

Input:

    1*(2+3)/4

Output:

    1
