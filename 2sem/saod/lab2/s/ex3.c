#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include "node.h"
#include "tree.h"
#define DC_SIZE 12000000
#define TEST 200000

void getkeys(char (*dc)[20]);
void set_hash_test(Node **hash, char (*dictionary)[20], int size);
double wtime();
// int hashtab_col(struct Node **hashtab);


int main() {
    double start_tree, finish_tree;
    Node *hash[HASH_SIZE];
    Node *hash_test = NULL;
    char (*dictionary)[20] = malloc(DC_SIZE * sizeof(char));
    FILE *ex1_hash = fopen("graphics/ex6_kr.txt", "a+");
    FILE *ex1_hash_col = fopen("graphics/ex6_kr_col.txt", "a+");

    getkeys(dictionary);

    fprintf(ex1_hash, "%d\t", TEST);
    fprintf(ex1_hash_col, "%d\t", TEST);
    set_hash_test(hash, dictionary, TEST);
    start_tree = wtime();
    hash_test = hashtab_lookup(hash, &dictionary[TEST / 2][0]);
    finish_tree = wtime();
    fprintf(ex1_hash, "%.6lf\n", finish_tree - start_tree);
    fprintf(ex1_hash_col, "%d\n", hashtab_col(hash));
    printf("find [%s]%d\n", hash_test->key, hash_test->value);
}

void getkeys(char (*dc)[20]) {
    FILE *dictionary = fopen("dictionary.txt", "r");

    for (int i = 0; i < 200000; i++) {
        fscanf(dictionary, "%s", dc[i]);
    }

    fclose(dictionary);
}

void set_hash_test(Node **hash, char (*dictionary)[20], int size) {
    hashtab_init(hash);

    for (int i = 1; i < size; i++) {
        hashtab_add(hash, &dictionary[i][0], rand()%100000);
    }
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// int hashtab_col(struct Node **hashtab) {
//     int count = 0;

//     for (int i = 0; i < HASH_SIZE; i++) {
//         if (hashtab[i] && hashtab[i]->next)
//             count++;
//     }
    
//     return count;
// }

unsigned int KRHash(char *s) {
    unsigned int h = 0, hash_mul = 31;
    while (*s)
    h = h * hash_mul + (unsigned int)*s++;
    return h % HASH_SIZE;
}

unsigned int AddHash(char *s) {
    unsigned int h = 0;
    while (*s)
    h += (unsigned int)*s++;
    return h % HASH_SIZE;
}

// struct Node *hashtab_lookup(struct Node **hashtab, char *key) {
//     int getkey = hashtab_hash(key);

//     while (1) {
//         if (!strcmp(hashtab[getkey]->key, key))
//             return hashtab[getkey];
//         if (hashtab[getkey]->next)
//             hashtab[getkey] = hashtab[getkey]->next;
//         else break;
//     }

//     return NULL;
// }