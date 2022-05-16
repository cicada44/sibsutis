#pragma once

struct listnode {
    int value;             /* Значение */
    struct listnode* next; /* Указатель на следующий элемент */
};

struct listnode* list_createnode(int value);
struct listnode* list_addfront(struct listnode* list, int value);
struct listnode* list_lookup(struct listnode* list, int value);
struct listnode* list_delete(struct listnode* list, int value);