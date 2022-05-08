#include "bstlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstree* bstreeCreate(char* key, int value)
{
    struct bstree* node;

    node = malloc(sizeof(*node));

    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void* bstreeAdd(struct bstree* tree, char* key, int value)
{
    if (tree == NULL)
        return;
    struct bstree *parent, *node;
    while (tree != NULL) {
        parent = tree;
        if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else if (strcmp(key, tree->key) > 0) {
            tree = tree->right;
        } else
            return;
    }
    node = bstreeCreate(key, value);
    if (strcmp(key, parent->key) < 0)
        parent->left = node;
    else
        parent->right = node;
}

struct bstree* bstreeLookup(struct bstree* tree, char* key)
{
    if (tree == NULL)
        return NULL;
    if (strcmp(key, tree->key) == 0) {
        return tree;
    } else if ((strcmp(key, tree->key) < 0)) {
        return bstreeLookup(tree->left, key);
    } else if ((strcmp(key, tree->key) > 0)) {
        return bstreeLookup(tree->right, key);
    }
}

struct bstree* bstreeMin(struct bstree* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

struct bstree* bstreeMax(struct bstree* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

struct bstree* bstreeFindParent(struct bstree* tree, char* key)
{
    struct bstree* parent = tree;
    while (parent->left != NULL && parent->right != NULL) {
        if (strcmp(parent->left->key, key) == 0
            || strcmp(parent->right->key, key) == 0)
            return 0;
        else if (strcmp(parent->key, key) > 0)
            parent = parent->left;
        else if (strcmp(parent->key, key) < 0)
            parent = parent->right;
        else
            return NULL;
    }
    return parent;
}

void bstreeDelete(struct bstree* tree, char* key)
{
    struct bstree* node = bstreeLookup(tree, key);
    struct bstree* parent = bstreeFindParent(tree, node->key);
    if (node->left == NULL && node->right == NULL) {
        if (parent->left->key == key) {
            parent->left = NULL;
        } else if (parent->right->key == key) {
            parent->right = NULL;
        }
        free(node);
    } else if (
            (node->left == NULL && node->right != NULL)
            || (node->left != NULL && node->right == NULL)) {
        if (parent->left != NULL) {
            if (parent->left->key == key) {
                if (parent->left->left != NULL)
                    parent->left = parent->left->left;
                else
                    parent->left = parent->left->right;
            }
        } else if (parent->right != NULL) {
            if (parent->right->key == key) {
                if (parent->right->left != NULL)
                    parent->right = parent->right->left;
                else
                    parent->right = parent->right->right;
            }
        }
        free(node);
    } else if (node->left != NULL && node->right != NULL) {
        struct bstree* x = node->right;
        x = bstreeMin(x);
        int tempValue = x->value;
        char* tempKey = x->key;
        bstreeDelete(tree, x->key);
        node->key = tempKey;
        node->value = tempValue;
    }
}

void traverseInorder(struct bstree* tree)
{
    if (tree != NULL) {
        traverseInorder(tree->left);
        traverseInorder(tree->right);
    }
}

void deleteTree(struct bstree* tree)
{
    if (tree == NULL)
        return;
    deleteTree(tree->right);
    deleteTree(tree->left);
    free(tree);
}

struct bstree* max(struct bstree* tree)
{
    if (tree->right != NULL) {
        tree = tree->right;
        max(tree);
    } else
        return tree;
}