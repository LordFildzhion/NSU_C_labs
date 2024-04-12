# Permutations

Implement permutation enumeration using the Dijkstra method.

## Input:
*   String №1:

    > Permutation **P**, containing from 1 to 10 characters from the set *0123456789*.

*   String №2:
        
    > Integer N - quantity of permutations from **P**.

## Output:

*   If the first line is not a permutation of characters from the set *0123456789*, then one line is *"Bad input"*. 

*   Otherwise, the first **N** (or however many there are) permutations after **P** in lexicographic order, one permutation per line.

*   If **P** is the last permutation in lexicographic order, then nothing should be inferred.

## ```Example 1```

Input:

    214
    2

Output:
    
    241
    412

## ```Example 2```

Input:
    
    111
    1

Output:

    Bad input

## ```Example 3```

Input:

    321
    1

Output:

``````
