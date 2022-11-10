#include <stdio.h>
#include "trie.h"

int main()
{
    // Driver program for the Trie Data Structure Operations
    Trie *root = make_trienode('\0');
    root = insert_trie(root, "hello");
    root = insert_trie(root, "hi");
    root = insert_trie(root, "teabag");
    root = insert_trie(root, "teacan");
    print_search(root, "tea");
    print_search(root, "teabag");
    print_search(root, "teacan");
    print_search(root, "hi");
    print_search(root, "hey");
    print_search(root, "hello");
    print_trie(root);
    free_trienode(root);

    return 0;
}