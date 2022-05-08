#include <stdlib.h>
#include <string.h>

typedef struct bstree
{
    char *key;
    int value;
    struct bstree *left;
    struct bstree *right;
    struct bstree *parent;
} bstree;

bstree *bstree_create(char *key, int value) {
    bstree *tree = (bstree *)malloc(sizeof(bstree));

    tree->key = key;
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;

    return tree;
}

int bstree_add(bstree *tree, char *key, int value) {
    bstree *new_node = bstree_create(key, value);

    if (!tree)
        return 0;

    while (1) {
        if (!strcmp(tree->key, key))
            return 0;
        else if (strcmp(tree->key, key) > 0) {
            if (!tree->left) {
                tree->left = new_node;
                new_node->parent = tree;
                return 1;
            }
            else
                tree = tree->left;
        }
        else {
            if (!tree->right) {
                tree->right = new_node;
                new_node->parent = tree;
                return 1;
            }
            else
                tree = tree->right;
        }

        if (!tree)
            break;
    }

    return 0;
}

bstree *bstree_lookup(bstree *tree, char *key) {
    while (1) {
        if (!strcmp(tree->key, key))
            return tree;

        else if (strcmp(tree->key, key) > 0) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }

        if (!tree)
            break;
    }

    return NULL;
}

bstree *bstree_min(bstree *tree) {
    bstree *min = tree;

    while (min->left) {
        min = min->left;
    }

    return min;
}

bstree *bstree_max(bstree *tree) {
    bstree *max = tree;

    while (max->right) {
        max = max->right;
    }

    return max;
}

static void _bstree_delete1(bstree *deltree, char*key) {
    bstree *pardeltree = deltree->parent;

    if (pardeltree->left == deltree)
        pardeltree->left = NULL;
    else
        pardeltree->right = NULL;

    free(deltree);
}

static void _bstree_delete2(bstree *deltree, char *key) {
    /* one child (left) */
    bstree *pardeltree = deltree->parent;
    if (deltree->left && !deltree->right) {
        if (pardeltree->left == deltree)
            pardeltree->left = deltree->left;
        else
            pardeltree->right = deltree->left;

        free(deltree);
    }

    /* one child (right) */
    if (!deltree->left && deltree->right) {
        if (pardeltree->left == deltree)
            pardeltree->left = deltree->right;
        else
            pardeltree->right = deltree->right;

        free(deltree);
    }
}

static void _bstree_delete3(bstree *deltree, char *key) {
    char *res_key;
    bstree *reserve = bstree_min(deltree->right);
    deltree->value = reserve->value;
    res_key = reserve->key;

    /* no children*/
    if (!reserve->left && !reserve->right)
        _bstree_delete1(reserve, key);

    /* one child*/
    if ((reserve->left && !reserve->right) || (!reserve->left && reserve->right))
        _bstree_delete2(reserve, key);

    deltree->key = res_key;
}

bstree *bstree_delete(bstree *tree, char *key) {
    bstree *deltree = bstree_lookup(tree, key);

    if (!deltree)
        return tree;

    /* no children*/
    if (!deltree->left && !deltree->right)
        _bstree_delete1(deltree, key);

    /* one child*/
    if ((deltree->left && !deltree->right) || (!deltree->left && deltree->right))
    _bstree_delete2(deltree, key);

    /* two children */
    if (deltree->left && deltree->right)
        _bstree_delete3(deltree, key);

    return tree;
}

void bstree_free(bstree *tree) {
    if (tree->left)
        bstree_free(tree->left); 
    if (tree->right)
        bstree_free(tree->right); 
    free(tree); 
}

void print_tree_as_list(bstree *root)
{
    if (!root)
        return;
    if (root)
        printf("[%s]%d ", root->key, root->value);
    print_tree_as_list(root->left);
    print_tree_as_list(root->right);
}

void showLine(char *c, int p, int s)
{
    int t = s;
    for (int i = 0; i < p; i++)
    {
        printf(t & 1 ? "|  " : "   ");
        t /= 2;
    }
    printf("%s", c);
}

void print_tree(bstree *tree, int p, int s)
{ // string s = string("")) {
    if (tree == NULL)
        return;
    printf("[%s]%d",tree->key, tree->value);
    printf("\n");

    if (tree->left != NULL)
    {
        showLine("|\n", p, s);
        showLine("L: ", p, s);
        print_tree(tree->left, p + 1, s + ((tree->right == NULL ? 0 : 1) << p));
    }
    if (tree->right != NULL)
    {
        showLine("|\n", p, s);
        showLine("R: ", p, s);
        print_tree(tree->right, p + 1, s);
    }
}