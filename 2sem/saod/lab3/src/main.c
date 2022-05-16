#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct graph* g;
    g = graph_create(10);
    graph_set_edge(g, 1, 2, 1);
    graph_set_edge(g, 1, 4, 1);
    /* ... */
    printf("DFS :\n");
    graph_dfs(g, 2);
    printf("BFS :\n");
    graph_bfs(g, 2);
    graph_free(g);
    return 0;
}