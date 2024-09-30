#include "../include/hashtab.h"

unsigned int hashtab_hash(int key)
{
	unsigned int h = 0;
	int p;

	for(p = key; p != (key + 10); p++){
		h = h * HASHTAB_MUL + (unsigned int)p;
	}
	return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab)
{
	for(int i = 0; i < HASHTAB_SIZE; i++)
		hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, int key, int value)
{
	struct listnode *node = (struct listnode *)malloc(sizeof(node));

	int index = hashtab_hash(key);
	if(node != NULL){
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, int key)
{
	int index = hashtab_hash(key);
	struct listnode *node;

	for(node = hashtab[index]; node != NULL; node = node->next){
		if(node->key == key){
			return node;
		}
	}
	return NULL;
}

void hashtab_print(struct listnode **hashtab)
{
	for (int i = 0; i < HASHTAB_SIZE; i++)
		if(hashtab[i] != NULL)
			printf("%d\t%d\n", hashtab[i]->key, hashtab[i]->value);
}