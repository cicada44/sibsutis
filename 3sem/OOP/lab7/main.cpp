#include "list.hpp"

int main(void)
{
    list l;
    l.push_front(5);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_front(4);
    l.remove(3);
    l.print();
    return 0;
}