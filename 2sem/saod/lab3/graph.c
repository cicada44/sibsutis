#include "func.h"
#include <stdio.h>
#include <stdlib.h>

#include "queue_array.h"

struct graph {
    int nvertices; // Число вершин
    int* m;        // Матрица n x n
    int* visited;
};

struct graph* graph_create(int nvertices)
{
    struct graph* g;
    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    g->visited = malloc(sizeof(int) * nvertices);
    graph_clear(g); // Опционально, O(n^2)
    return g;
}

void graph_clear(struct graph* g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
        g->visited[i] = 0;
        for (j = 0; j < g->nvertices; j++) {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

void graph_free(struct graph* g)
{
    free(g->m);
    free(g->visited);
    free(g);
}

void graph_set_edge(struct graph* g, int i, int j, int w)
{
    g->m[(i - 1) * g->nvertices + j - 1] = w;
    g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(struct graph* g, int i, int j)
{
    return g->m[(i - 1) * g->nvertices + j - 1];
}