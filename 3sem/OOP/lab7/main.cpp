#include "list.hpp"

int main(void)
{
    list l = { 1, 2, 3, 4, 5, 1 };

    // list l(10, 1);

    // l.push_front(5);
    // l.push_back(1);
    // l.push_back(2);
    // l.push_back(3);
    // l.push_front(4);
    // l.print();

    // list m;
    // m.push_back(31);
    // m.push_front(14);

    // l = l + m;

    l.unique();
    l.print();
    return 0;
}