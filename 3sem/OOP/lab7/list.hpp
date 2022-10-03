#ifdef __LIST__
#error List was enabled earlier
#else
#define __LIST__

#include <climits>
#include <initializer_list>
#include <iostream>

using std::initializer_list;

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
    unsigned long size;
    void copyall(const list& l);

public:
    list()
        : first(nullptr)
        , last(nullptr)
        , size(0)
    {
    }
    list(initializer_list<int> s)
    {
        this->first = this->last = nullptr;
        this->size = 0;
        for (auto tmp : s) {
            this->push_back(tmp);
        }
    }
    list(unsigned long count, int key)
    {
        this->first = this->last = nullptr;
        this->size = 0;
        for (decltype(count) i = 0; i < count; ++i)
            this->push_back(key);
    }
    ~list() { free_list(); }
    list(const list& l) { this->copyall(l); }

    Node* getfirst() { return this->first; }
    Node* getlast() { return this->last; }
    unsigned long getsize() { return this->size; }
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
    void unique();

    void operator=(const list& l) { this->copyall(l); }
    friend list operator+(const list& l1, const list& l2)
    {
        list tmp = l1;
        Node* head = l2.first;
        while (head) {
            tmp.push_back(head->key);
            head = head->next;
        }
        return tmp;
    }
};

#endif // __LIST__