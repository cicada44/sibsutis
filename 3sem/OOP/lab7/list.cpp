#include "list.hpp"

void list::print()
{
    if (is_empty())
        return;
    Node* _head = this->first;
    while (_head != this->last) {
        std::cout << _head->key << " -> ";
        _head = _head->next;
    }
    std::cout << this->last->key << std::endl;
}

Node* list::new_node(int key)
{
    Node* temp = nullptr;
    try {
        temp = new Node(key);
    } catch (std::bad_alloc& ba) {
        std::cerr << ba.what() << std::endl;
    }

    return temp;
}

void list::push_front(int key)
{
    Node* newnode = new_node(key);
    if (is_empty()) {
        this->last = this->first = newnode;
    } else {
        newnode->next = this->first;
        this->first = newnode;
    }
    this->size += 1;
}

void list::push_back(int key)
{
    Node* newnode = new_node(key);
    if (is_empty()) {
        this->last = this->first = newnode;
    } else {
        this->last->next = newnode;
        this->last = this->last->next;
    }
    this->size += 1;
}

int list::pop_back()
{
    if (is_empty())
        return INT_MIN;
    int k = this->last->key;

    Node* head = first;
    while (head->next->next)
        head = head->next;

    head->next = nullptr;
    delete this->last;
    this->last = head;
    this->size -= 1;

    return k;
}

int list::pop_front()
{
    if (is_empty())
        return INT_MIN;
    int k = this->first->key;

    Node* head = first->next;
    delete this->first;
    this->first = head;
    this->size -= 1;
    return k;
}

void list::free_list()
{
    if (is_empty())
        return;
    Node* head = this->first;
    this->first = this->last = nullptr;

    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    this->size = 0;
}

Node* list::find_node(int key)
{
    Node* head = this->first;

    while (head) {
        if (head->key == key)
            return head;
        head = head->next;
    }

    return nullptr;
}

void list::remove(int key)
{
    Node* head = find_node(key);
    if (!head)
        return;
    if (head == first) {
        pop_front();
    } else if (head == last) {
        pop_back();
    } else {
        Node* prev = first;
        while (prev && prev->next->key != head->key) {
            prev = prev->next;
        }
        prev->next = head->next;
        delete head;
    }
}

void list::merge(list m)
{
    Node* head = m.getfirst();
    while (head) {
        this->push_back(head->key);
        head = head->next;
    }
}

void list::unique()
{
    for (Node* i = this->first; i; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (i->key == j->key)
                this->remove(i->key);
        }
    }
}

void list::copyall(const list& l)
{
    this->first = this->last = nullptr;
    Node* head = l.first;
    while (head) {
        this->push_back(head->key);
        head = head->next;
    }
}