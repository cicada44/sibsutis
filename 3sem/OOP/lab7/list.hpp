#ifdef __LIST__
#error List was enabled earlier
#else
#define __LIST__

#include <climits>
#include <iostream>
#include <string>

using std::string;

typedef struct Node {
    int key;
    struct Node* next;
    Node(int _key)
        : key(_key)
        , next(nullptr)
    {
    }
} Node;

class list {

private:
    Node* first;
    Node* last;

public:
    list()
        : first(nullptr)
        , last(nullptr)
    {
    }
    ~list() { free_list(); }
    Node* getfirst() { return this->first; }
    Node* getlast() { return this->last; }
    bool is_empty() { return (!first) ? true : false; }
    void print();
    Node* new_node(int key);
    void push_front(int key);
    void push_back(int key);
    int pop_back();
    int pop_front();
    void free_list();
    Node* find_node(int key);
    void remove(int key);
    Node* front() { return this->first; };
    Node* back() { return this->last; };
    void merge(list m);
};

#endif // __LIST__