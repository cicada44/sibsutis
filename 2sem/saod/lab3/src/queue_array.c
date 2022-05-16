#include "queue_array.h"
#include <stdio.h>
#include <stdlib.h>

struct queue* queue_create()
{
    struct queue* q = malloc(sizeof(*q));
    if (q != NULL) {
        q->size = 0;
        q->head = 0;
        q->tail = 0;
    }
    return q;
}

void queue_free(struct queue* q)
{
    while (q->size > 0)
        queue_dequeue(q);
    free(q);
}

int queue_size(struct queue* q)
{
    return q->size;
}

void queue_enqueue(struct queue* q, int value)
{
    struct listnode* oldtail = q->tail;
    q->tail = list_createnode(value);
    if (q->head == NULL) /* Очередь пуста */
        q->head = q->tail;
    else
        oldtail->next = q->tail;
    q->size++;
}

int queue_dequeue(struct queue* q)
{
    int value;
    struct listnode* p;
    if (q->size == 0)
        return -1;

    value = q->head->value;
    p = q->head->next;
    free(q->head);
    q->head = p;
    q->size--;
    return value;
}