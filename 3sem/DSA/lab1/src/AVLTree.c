#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "AVLTree.h"

struct avltree *avltree_delete(struct avltree *tree, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (tree == NULL)
        return tree;

    // If the key to be deleted is smaller than the
    // tree's key, then it lies in left subtree
    if (key < tree->key)
        tree->left = avltree_delete(tree->left, key);

    // If the key to be deleted is greater than the
    // tree's key, then it lies in right subtree
    else if (key > tree->key)
        tree->right = avltree_delete(tree->right, key);

    // if key is same as tree's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if ((tree->left == NULL) || (tree->right == NULL))
        {
            struct avltree *temp = tree->left ? tree->left : tree->right;

            // No child case
            if (temp == NULL)
            {
                temp = tree;
                tree = NULL;
            }
            else               // One child case
                *tree = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct avltree *temp = avltree_min(tree->right);

            // Copy the inorder successor's data to this node
            tree->key = temp->key;

            // Delete the inorder successor
            tree->right = avltree_delete(tree->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (tree == NULL)
        return tree;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    tree->height = 1 + imax2(avltree_height(tree->left),
                             avltree_height(tree->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = avltree_balance(tree);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && avltree_balance(tree->left) >= 0)
        return avltree_right_rotate(tree);

    // Left Right Case
    if (balance > 1 && avltree_balance(tree->left) < 0)
    {
        return avltree_leftright_rotate(tree);
    }

    // Right Right Case
    if (balance < -1 && avltree_balance(tree->right) <= 0)
        return avltree_left_rotate(tree);

    // Right Left Case
    if (balance < -1 && avltree_balance(tree->right) > 0)
    {
        return avltree_rightleft_rotate(tree);
    }

    return tree;
}

struct avltree *avltree_add(struct avltree *tree, int key, char *value)
{
    if (tree == NULL)
    {
        return avltree_create(key, value);
    }

    if (key < tree->key)
    {
        /* Insert into left subtree */
        tree->left = avltree_add(tree->left, key, value);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
        {
            /* Subtree is unbalanced */
            if (key < tree->left->key)
            {
                /* Left left case */
                tree = avltree_right_rotate(tree);
            }
            else
            {
                /* Left right case */
                tree = avltree_leftright_rotate(tree);
            }
        }
    }
    else if (key > tree->key)
    {
        /* Insert into right subtree */
        tree->right = avltree_add(tree->right, key, value);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        {
            /* Subtree is unbalanced */
            if (key > tree->right->key)
            {
                /* Right right case */
                tree = avltree_left_rotate(tree);
            }
            else
            {
                /* Right left case */
                tree = avltree_rightleft_rotate(tree);
            }
        }
    }
    tree->height = imax2(avltree_height(tree->left),
                         avltree_height(tree->right)) +
                   1;
    return tree;
}

struct avltree *avltree_leftright_rotate(struct avltree *tree)
{
    tree->left = avltree_left_rotate(tree->left);
    printf("LEFTRIGHT ROTATE <%d>\n", tree->left->key);
    return avltree_right_rotate(tree);
}
struct avltree *avltree_rightleft_rotate(struct avltree *tree)
{
    tree->right = avltree_right_rotate(tree->right);
    printf("RIGHTLEFT ROTATE <%d>\n", tree->right->key);
    return avltree_left_rotate(tree);
}

struct avltree *avltree_right_rotate(struct avltree *tree)
{
    struct avltree *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;
    printf("RIGHT ROTATE <%d>\n", left->key);
    return left;
}

struct avltree *avltree_left_rotate(struct avltree *tree)
{
    struct avltree *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;
    printf("LEFT ROTATE <%d>\n", right->key);
    return right;
}

int imax2(int n1, int n2)
{
    return ((n1 > n2) ? n1 : n2);
}

int avltree_height(struct avltree *tree)
{
    return ((tree != NULL) ? tree->height : -1);
}

int avltree_balance(struct avltree *tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}

struct avltree *avltree_create(int key, char *value)
{
    struct avltree *node;
    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

struct avltree *avltree_lookup(struct avltree *tree, int key)
{
    while (tree != NULL)
    {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

struct avltree *avltree_min(struct avltree *tree)
{
    struct avltree *min = tree;
    while (min->left != NULL)
        min = min->left;
    return min;
}

void avltree_print_dfs(struct avltree *node, int level)
{
    long i;
    if (node != NULL)
    {
        avltree_print_dfs(node->right, level + 5);
        for (i = 0; i < level; i++)
            printf(" ");
        printf("%d\n", node->key);
        avltree_print_dfs(node->left, level + 5);
    }
}

struct avltree *avltree_max(struct avltree *tree)
{
    struct avltree *max = tree;
    while (max->right != NULL)
        max = max->right;
    return max;
}

void avltree_free(struct avltree *tree)
{
    if (tree == NULL)
        return;
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}