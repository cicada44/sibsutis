#pragma once
#include "llist.h"

struct queue {
    struct listnode* head;
    struct listnode* tail;
    int size;
};

struct queue* queue_create();
void queue_free(struct queue* q);
int queue_size(struct queue* q);
void queue_enqueue(struct queue* q, int value);
int queue_dequeue(struct queue* q);