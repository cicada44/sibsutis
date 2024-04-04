#ifndef LIST_H
#define LIST_H

template <class T>
class List {
private:
    T *head;
    List<T> *tail;
public:
    List(T *h, List<T>* t = nullptr): head(h), tail(t) { }
    T *hd() const { return head; }
    List<T>* tl() const { return tail; }
};

template <class T>
void list_map(void f(T*), List<T> *l)
{
    for (l; l != nullptr; l = l->tl())
        f(l->hd());
}

template <class S, class T>
void list_print(S &str, List<T> *l)
{
    str << "[\n";
    for(; l != NULL; l = l->tl())
	    str << *(l->hd()) << " ";
    str << "]\n";
}

template <class T>
int list_length(List<T> *l)
{
    int i = 0;
    for (; l != NULL; l = l->tl())
        i++;
    return i;
}

#endif

