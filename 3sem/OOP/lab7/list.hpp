#ifdef __LIST__
#error List was enabled earlier
#else
#define __LIST__

#include <climits>
#include <iostream>
#include <vector>

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
    static unsigned long count;

public:
    list()
        : first(nullptr)
        , last(nullptr)
        , size(0)
    {
        list::setcount(list::getcount() + 1);
    }
    list(std::initializer_list<int> s)
    {
        this->first = this->last = nullptr;
        this->size = 0;
        for (auto tmp : s) {
            this->push_back(tmp);
        }
        list::setcount(list::getcount() + 1);
    }
    list(unsigned long count, int key)
    {
        this->first = this->last = nullptr;
        this->size = 0;
        for (decltype(count) i = 0; i < count; ++i)
            this->push_back(key);
        list::setcount(list::getcount() + 1);
    }
    ~list()
    {
        free_list();
        list::setcount(list::getcount() - 1);
    }
    list(const list& l) { this->copyall(l); }

    Node* getfirst() { return this->first; }
    Node* getlast() { return this->last; }
    unsigned long getsize() { return this->size; }
    static unsigned long getcount() { return list::count; }
    void setsize(unsigned long n) { this->size = n; }
    void setfirst(Node* f) { this->first = f; }
    void setlast(Node* l) { this->last = l; }
    void setcount(unsigned long n) { list::count += 1; }
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
    // friend list mergeKLists(std::vector<list>& lists);
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

list mergeKLists(std::vector<list>& lists);

#endif // __LIST__

#ifdef __STACK__
#error Stack was enabled earlier
#else

#ifndef __LIST__
#error List dont included
#endif

#define __STACK__

class stack : protected list {
private:
    Node* _top;

public:
    stack()
        : _top(nullptr)
    {
        setsize(0);
        setfirst(nullptr);
        setlast(nullptr);
    }
    stack(std::initializer_list<int> s)
    {
        this->setfirst(nullptr);
        this->setlast(nullptr);
        this->setsize(0);
        for (auto tmp : s) {
            this->push(tmp);
        }
    }
    stack(unsigned long count, int key)
    {
        this->setfirst(nullptr);
        this->setlast(nullptr);
        this->setsize(0);
        for (decltype(count) i = 0; i < count; ++i)
            this->push(key);
    }
    ~stack() { free_stack(); }
    void push(int key)
    {
        this->push_front(key);
        this->setsize(this->getsize() + 1);
        this->_top = this->getfirst();
    }
    int pop()
    {
        int k = this->pop_front();
        this->setsize(this->getsize() - 1);
        _top = this->getfirst();
        return k;
    }
    bool empty() { return this->is_empty(); }
    unsigned long size() { return this->getsize(); }
    Node* top() { return this->_top; }
    void free_stack() { this->free_list(); }
};

#endif // __QUEUE__

#ifdef __QUEUE__
#error Stack was enabled earlier
#else

#ifndef __LIST__
#error List dont included
#endif

#define __QUEUE__

class queue : protected list {
private:
    Node* _back;

public:
    queue()
        : _back(nullptr)
    {
        setsize(0);
        setfirst(nullptr);
        setlast(nullptr);
    }
    queue(std::initializer_list<int> s)
    {
        this->setfirst(nullptr);
        this->setlast(nullptr);
        this->setsize(0);
        for (auto tmp : s) {
            this->push(tmp);
        }
    }
    queue(unsigned long count, int key)
    {
        this->setfirst(nullptr);
        this->setlast(nullptr);
        this->setsize(0);
        for (decltype(count) i = 0; i < count; ++i)
            this->push(key);
    }
    ~queue() { free_queue(); }
    void push(int key)
    {
        this->push_back(key);
        this->_back = this->getlast();
    }
    int pop()
    {
        int k = this->pop_front();
        _back = this->getlast();
        return k;
    }
    bool empty() { return this->is_empty(); }
    unsigned long size() { return this->getsize(); }
    Node* back() { return this->_back; }
    void free_queue() { this->free_list(); }
};

#endif // __QUEUE__