# Connected components (Kosorajo's algorithm)

Realize a search for strongly connectivity components in a graph

**Time for searching: 1 seconds**

**Memory: executable + data no more then sizeof(void \*) + sizeof(void \*) \* M + 1024Kb**

## Input
*   String №1:

    > Integer **N** from 0 to 2000 - quantity of vertex.

*   String №2:

    > Integer **M** from 0 to **N** \* (**N** - 1) / 2 - quantity of edges.

*   From string №3 for **M** + 2:

    > Integer from 1 to **N** - start and end of the edge.

## Output
	
*   If **N** is not from 0 to 1000, then *"Bad number of vertices"*
	
*    If **M** is not from 0 to N \* (N + 1) / 2, then *"Bad number of edges"*
	
*    If the vertex number is not from 1 to **N**, then *"Bad vertex"*
	
*    If the lines are less than **M** + 2, then *"Bad number of lines"*

*   Else Otherwise, to derive the components of strong connectivity in the order of exit from the traversal to the depth of at least one vertex from it, if the vertices are in the same component of the connectivity - to derive their numbers in ascending order

## ```Example 1```

Input:

    3
    2
    1 2
    2 3

Output:

    3
    1
    2
    3

## ```Example 2```

Input:

    3
    3
    1 2
    2 3
    3 1

Output:

    1
    1 2 3

## ```Example 3```

Input:

    3
    2
    1 2
    2 -1

Output:

    Bad vertex
