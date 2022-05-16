#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listnode* list_createnode(int value)
{
    struct listnode* p;

    p = malloc(sizeof(*p));
    if (p != NULL) {
        p->value = value;
        p->next = NULL;
    }
    return p;
}

struct listnode* list_addfront(struct listnode* list, int value)
{
    struct listnode* newnode;
    newnode = list_createnode(value);

    if (newnode != NULL) {
        newnode->next = list;
        return newnode;
    }
    return list;
}

struct listnode* list_lookup(struct listnode* list, int value)
{
    for (; list != NULL; list = list->next) {
        if (list->value == value) {
            return list;
        }
    }
    return NULL; /* Не нашли */
}

struct listnode* list_delete(struct listnode* list, int value)
{
    struct listnode *p, *prev = NULL;
    for (p = list; p != NULL; p = p->next) {
        if (p->value == value) {
            if (prev == NULL)
                list = p->next; /* Удаляем голову */
            else
                prev->next = p->next; /* Есть элемент слева */
            free(p);                  /* Освобождаем память */
            return list; /* Указатель на новую голову */
        }
        prev = p; /* Запоминаем предыдущий элемент */
    }
    return NULL; /* Не нашли */
}