#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IntVector* int_vector_new(size_t initial_capacity)
{
    IntVector* t = malloc(sizeof(IntVector));
    if (t == NULL)
        return NULL;
    t->pointer = malloc(initial_capacity * sizeof(int));
    if (t->pointer == NULL) {
        free(t);
        return NULL;
    }
    t->size = 0;
    t->capacity = initial_capacity;
    return t;
}

IntVector* int_vector_copy(const IntVector* v)
{
    IntVector* t = malloc(sizeof(IntVector));
    if (t == NULL)
        return NULL;
    t->pointer = malloc(v->capacity * sizeof(int));
    if (t->pointer == NULL) {
        free(t);
        return NULL;
    }
    memcpy(t->pointer, v->pointer, sizeof(int) * v->capacity);
    t->size = v->size;
    t->capacity = v->capacity;
    return t;
}

void int_vector_free(IntVector* v)
{
    free(v->pointer);
    free(v);
}

int int_vector_get_item(const IntVector* v, size_t index)
{
    return v->pointer[index];
}

void int_vector_set_item(IntVector* v, size_t index, int item)
{
    if (index <= v->capacity)
        v->pointer[index] = item;
    v->size++;
}

size_t int_vector_get_size(const IntVector* v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector* v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector* v, int item)
{
    if (v->size < v->capacity) {
        v->pointer[v->size] = item;
        v->size++;
    } else {
        v->capacity *= 2;
        // FIXME ready
        int* t = realloc(v->pointer, v->capacity * sizeof(int));
        if (t == NULL)
            return -1;
        v->pointer = t;
        v->pointer[v->size] = item;
        v->size++;
    }
    return 0;
}

void int_vector_pop_back(IntVector* v)
{
    if (v->size != 0)
        v->size--;
}

int int_vector_shrink_to_fit(IntVector* v)
{
    if (v->size < v->capacity) {
        v->capacity = v->size;
        int* t = realloc(v->pointer, v->size * sizeof(int));
        if (t == NULL)
            return -1;
        v->pointer = t;
        return 0;
    }
    return -1;
}

int int_vector_resize(IntVector* v, size_t new_size)
{
    if (new_size == v->size)
        return 0;
    if (new_size > v->size) {
        // FIXME ready
        int* t = realloc(v->pointer, new_size * sizeof(int));
        if (t == NULL)
            return -1;
        v->pointer = t;
        for (int i = v->size; i < new_size; i++)
            v->pointer[i] = 0;
    }
    v->size = new_size;
    return 0;
}

int int_vector_reserve(IntVector* v, size_t new_capacity)
{
    if (new_capacity > v->capacity) {
        v->capacity = new_capacity;
        int* t = realloc(v->pointer, new_capacity * sizeof(int));
        if (t == NULL)
            return -1;
        v->pointer = t;
        return 0;
    }
    return -1;
}