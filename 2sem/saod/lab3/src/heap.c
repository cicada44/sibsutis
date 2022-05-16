#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

struct heap* heap_create(int maxsize)
{
    struct heap* h;
    h = malloc(sizeof(*h));
    if (h != NULL) {
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->nodes = malloc(
                sizeof(*h->nodes)
                * (maxsize + 1)); /* Последний индекс - maxsize */
        if (h->nodes == NULL) {
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(struct heap* h)
{
    free(h->nodes);
    free(h);
}

void heap_swap(struct heapnode* a, struct heapnode* b)
{
    struct heapnode temp = *a;
    *a = *b;
    *b = temp;
}

struct heapnode* heap_max(struct heap* h)
{
    if (h->nnodes == 0)
        return NULL;
    return &h->nodes[1];
}

int heap_insert(struct heap* h, int key, char* value)
{
    if (h->nnodes >= h->maxsize) /* Переполнение кучи */
        return -1;

    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;

    /* HeapifyUp */
    for (int i = h->nnodes; i > 1 && h->nodes[i].key > h->nodes[i / 2].key;
         i = i / 2)
        heap_swap(&h->nodes[i], &h->nodes[i / 2]);
    return 0;
}

struct heapnode heap_extract_max(struct heap* h)
{
    if (h->nnodes == 0)
        return (struct heapnode){0, NULL};

    struct heapnode maxnode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes--];
    heap_heapify(h, 1);

    return maxnode;
}

void heap_heapify(struct heap* h, int index)
{
    while (1) {
        int left = 2 * index;
        int right = 2 * index + 1;
        int largest = index;
        if (left <= h->nnodes && h->nodes[left].key > h->nodes[largest].key)
            largest = left;
        if (right <= h->nnodes && h->nodes[right].key > h->nodes[largest].key)
            largest = right;
        if (largest == index)
            break;
        heap_swap(&h->nodes[index], &h->nodes[largest]);
        index = largest;
    }
}

int heap_increase_key(struct heap* h, int index, int newkey)
{
    if (h->nodes[index].key >= newkey)
        return -1;

    h->nodes[index].key = newkey;
    while (index > 1 && h->nodes[index].key > h->nodes[index / 2].key) {
        heap_swap(&h->nodes[index], &h->nodes[index / 2]);
        index /= 2;
    }
    return index;
}