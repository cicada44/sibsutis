#include <malloc.h>
#include <string.h>
#define HASH_SIZE 200003

typedef struct Node
{
    char *key;
    int value;
    struct Node *next;
} Node;

void print_node(const Node *head)
{
    int i = 0;
    while (head)
    {
        printf("{%d}[%s]%d ", i, head->key, head->value);
        head = head->next;
        i++;
    }
    printf("\n");
}

Node *new_node(int data, char *key)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    temp->value = data;
    temp->key = key;
    temp->next = NULL;

    return temp;
}

void free_node(Node *node)
{
    if (!(node->next))
        return;

    Node *head = (Node *)malloc(sizeof(Node));

    while (head)
    {
        head = node->next;
        free(node);
        node = head;
    }
}

void push_start(Node **head, int data, char *key)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = data;
    temp->key = key;
    temp->next = (*head);
    *head = temp;
}

void push_back(Node *head, int data, char* key)
{
    while (head->next)
        head = head->next;

    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = data;
    temp->key = key;
    temp->next = NULL;
    head->next = temp;
}

void pop_back(Node *head)
{
    while (head->next->next)
        head = head->next;

    head->next = NULL;
}

Node *find_node(Node *head, char *key) {
    Node *temp = NULL;

    while (1) {
        if (!head)
            return NULL;
        
        if (!strcmp(head->key, key)) {
            temp = head;
            return temp;
        }

        head = head->next;
    }
}

Node *delete_in_node(Node *head, char *key) {
    Node *temp = NULL;
    Node *parent = head;

    temp = find_node(head, key);

    if (!temp)
        return NULL;

    if (head == temp) {
        parent = head->next;
        free(head);
        return parent;
    }

    while (head->next != temp) {
        if (!head)
            break;
        head = head->next;
    }

    if (!head->next) {
        free(head);
        return parent;
    }

    head->next = temp->next;
    free(temp);
    return parent;
}

unsigned int hashtab_hash(char *key) {
    // add 
    // unsigned int h = 0;
    //     while (*key)
    //         h += (unsigned int)*key++;
    // return h % HASH_SIZE;
    
    // kr
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASH_SIZE;
}

void hashtab_init(struct Node **hashtab) {
    int i;

    for (i = 0; i < HASH_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_print(struct Node **hashtab) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (!hashtab[i])
            continue;
        else
            print_node(hashtab[i]);
        }
}

void hashtab_add(struct Node **hashtab, char *key, int value) {
    int hashkey = hashtab_hash(key);

    if (!hashtab[hashkey]) {
        hashtab[hashkey] = new_node(value, key);
    }
    else {
        push_back(hashtab[hashkey], value, key);
    }
}

struct Node *hashtab_lookup(struct Node **hashtab, char *key) {
    int getkey = hashtab_hash(key);

    while (1) {
        if (!strcmp(hashtab[getkey]->key, key))
            return hashtab[getkey];
        if (hashtab[getkey]->next)
            hashtab[getkey] = hashtab[getkey]->next;
        else break;
    }

    return NULL;
}

// struct Node *hashtab_lookup(struct Node **hashtab, char *key) {
//     Node *temp = NULL;

//     for (int i = 0; i < HASH_SIZE; i++) {
//         temp = find_node(hashtab[i], key);
//         if (!temp)
//             continue;
//         else {
//             return temp;
//         }
//     }
// }

Node *delete_value(Node *head, char *key)
{
    Node *current, *previous;
  
    current = head;
 
    while(current) {
        if (!strcmp(current->key, key)) {
            if (current == head) {
                if (head->next == NULL) {
                    free(current);
                    return head = NULL;
                }
                
            head = current->next;
            free(current);
            current = head;
            }
        else {
            if (current->next != NULL) {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
            else {
                previous->next = NULL;
                free(current);
                return head;
            }
        }
    }

    previous = current;
    current = previous->next;
    }

    if (head == current) head = current;
    return head;
}

void hashtab_delete(struct Node **hashtab, char *key) {
    Node *temp = NULL;

    for (int i = 0; i < HASH_SIZE; i++) {
        temp = hashtab_lookup(hashtab, key);
        if (!temp)
            continue;
        else {
            hashtab[i] = delete_value(hashtab[i], key);
        }
    }
}

void hashtab_free(struct Node **hashtab) {
    for (int i = 0; i < HASH_SIZE; i++) {
        free_node(hashtab[i]);
        hashtab[i] = NULL;
    }
}

int hashtab_col(struct Node **hashtab) {
    int count = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashtab[i] && hashtab[i]->next)
            count++;
    }
    
    return count;
}
