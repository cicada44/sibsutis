#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

#define N 26

Trie *make_trienode(char data)
{
    Trie *node = (Trie *)calloc(1, sizeof(Trie));
    for (int i = 0; i < N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(Trie *node)
{
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL)
            free_trienode(node->children[i]);
        else
            continue;
    }
    free(node);
}

Trie *insert_trie(Trie *root, char *word)
{
    Trie *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int)word[i] - 'a';
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = make_trienode(word[i]);
        }
        temp = temp->children[idx];
    }
    temp->is_leaf = 1;
    return root;
}

int search_trie(Trie *root, char *word)
{
    Trie *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}

void print_trie(Trie *root)
{
    if (!root)
        return;
    Trie *temp = root;
    printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++)
    {
        print_trie(temp->children[i]);
    }
}

void print_search(Trie *root, char *word)
{
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}
