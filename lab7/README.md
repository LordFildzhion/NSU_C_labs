# Topological sort

Realize topological sort of graph

**Time for sort: 3 seconds**

**Memory: executable + data no more then sizeof(void \*) + sizeof(void \*) \* M + 1024Kb**

## Input
*   String №1:

    > Integer **N** from 0 to 1000 - quantity of vertex.

*   String №2:

    > Integer **M** from 0 to **N** \* (**N** - 1) / 2 - quantity of edges.

*   From string №3 for **M** + 2:

    > Integer from 1 to **N** - start and end of the edge.

## Output
	
*   If **N** is not from 0 to 1000, then *"Bad number of vertices"*
	
*    If **M** is not from 0 to N \* (N + 1) / 2, then *"Bad number of edges"*
	
*    If the vertex number is not from 1 to **N**, then *"Bad vertex"*
	
*    If the lines are less than **M** + 2, then *"Bad number of lines"*

*    If the graph allows topological sorting, then the vertices of the graph after topological sorting

*    If the graph does not allow topological soration, then *"Impossible to sort"*

## ```Example 1```

Input:

    3
    2
    1 2
    1 3

Output:

    1 2 3

## ```Example 2```

Input:

    3
    3
    1 2
    2 3
    3 1

Output:
    
    Impossible to sort

## ```Example 3```

Input:

    4

Output:
    
    Bad number of lines
