#include <stdio.h>
#include <stdlib.h>
#pragma once

struct bstree {
    char* key;
    int value;
    struct bstree* left;
    struct bstree* right;
};

struct bstree* bstreeCreate(char* key, int value);
void* bstreeAdd(struct bstree* tree, char* key, int value);
struct bstree* bstreeLookup(struct bstree* tree, char* key);
struct bstree* bstreeMin(struct bstree* tree);
struct bstree* bstreeMax(struct bstree* tree);
void bstreeDelete(struct bstree* tree, char* key);
void deleteTree(struct bstree* tree);
struct bstree* max(struct bstree* tree);