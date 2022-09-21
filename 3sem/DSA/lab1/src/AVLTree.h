#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <stdio.h>

struct avltree
{
    int key;
    char *value;

    int height;
    struct avltree *left;
    struct avltree *right;
};

int imax2(int n1, int n2);
int avltree_balance(struct avltree *tree);
int avltree_height(struct avltree *tree);
struct avltree *avltree_left_rotate(struct avltree *tree);
struct avltree *avltree_right_rotate(struct avltree *tree);
struct avltree *avltree_rightleft_rotate(struct avltree *tree);
struct avltree *avltree_leftright_rotate(struct avltree *tree);
struct avltree *avltree_create(int key, char *value);
struct avltree *avltree_add(struct avltree *root, int key, char *value);
struct avltree *avltree_lookup(struct avltree *root, int key);
struct avltree *avltree_delete(struct avltree *root, int key);
struct avltree *avltree_min(struct avltree *root);
struct avltree *avltree_max(struct avltree *root);
void avltree_free(struct avltree *root);
void avltree_print_dfs(struct avltree *root, int level);

#endif // __AVLTREE_H__