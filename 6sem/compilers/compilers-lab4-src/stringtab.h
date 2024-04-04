#ifndef STRINGTAB_H
#define STRINGTAB_H

#include <iostream>
#include <cstring>
#include <algorithm>
#include "list.h"

class Entry;
typedef Entry* Symbol;

extern std::ostream& operator<<(std::ostream &s, const Entry& sym);
extern std::ostream& operator<<(std::ostream &s, Symbol sym);

class Entry {
protected:
    char *str;     // string
    int  len;      // length of the string (without trailing \0)
    int index;     // unique index for each string
public:
    Entry(char *s, int l, int i) : len(l), index(i) {
        str = new char [len + 1];
        std::strncpy(str, s, len);
        str[len] = '\0';
    }
    int equal_string(char *s, int length) const { return (len == length) && (std::strncmp(str, s, len) == 0); }
    bool equal_index(int ind) const { return ind == index; }
    std::ostream& print(std::ostream &s) const { return s << "{" << str << ", " << len << ", " << index << "}\n"; }
    char *get_string() const { return str; }
    int get_len() const { return len; }
};

class StringEntry : public Entry {
public:
    StringEntry(char *s, int l, int i);
};

class IdEntry : public Entry {
public:
    IdEntry(char *s, int l, int i);
};

class IntEntry: public Entry {
public:
    IntEntry(char *s, int l, int i);
};

typedef StringEntry *StringEntryP;
typedef IdEntry *IdEntryP;
typedef IntEntry *IntEntryP;

// String Tables

template <class Elem>
class StringTable
{
protected:
   List<Elem> *tbl = nullptr;
   int index = 0;
public:
   // add the prefix of s of length maxchars
   Elem *add_string(char *s, int maxchars);
   // add the (null terminated) string s
   Elem *add_string(char *s);
   // add the string representation of an integer
   Elem *add_int(int i);

   // Iterator
   int first();
   int more(int i);
   int next(int i);
   Elem *lookup(int index);      // lookup an element using its index
   Elem *lookup_string(char *s); // lookup an element using its string
   void print();                 // print table
};

class IdTable : public StringTable<IdEntry> { };
class StrTable : public StringTable<StringEntry> { };
class IntTable : public StringTable<IntEntry> { };

extern IdTable idtable;
extern IntTable inttable;
extern StrTable stringtable;

template <class Elem>
Elem *StringTable<Elem>::add_string(char *s)
{
    constexpr int MAXSIZE = 1000000;
    return add_string(s, MAXSIZE);
}

template <class Elem>
Elem *StringTable<Elem>::add_string(char *s, int maxchars)
{
    int len = std::strlen(s);
    len = std::min(len, maxchars);
    for (List<Elem> *l = tbl; l; l = l->tl())
        if (l->hd()->equal_string(s, len))
        return l->hd();

    Elem *e = new Elem(s, len, index++);
    tbl = new List<Elem>(e, tbl);
    return e;
}

template <class Elem>
Elem *StringTable<Elem>::lookup_string(char *s)
{
    int len = std::strlen(s);
    for (List<Elem> *l = tbl; l; l = l->tl())
        if (l->hd()->equal_string(s, len))
            return l->hd();
    return nullptr;
}

template <class Elem>
Elem *StringTable<Elem>::lookup(int ind)
{
    for (List<Elem> *l = tbl; l; l = l->tl())
        if (l->hd()->equal_index(ind))
            return l->hd();
    return nullptr;
}

template <class Elem>
Elem *StringTable<Elem>::add_int(int i)
{
    static char *buf = new char[20];
    std::snprintf(buf, 20, "%d", i);
    return add_string(buf);
}
template <class Elem>
int StringTable<Elem>::first()
{
    return 0;
}

template <class Elem>
int StringTable<Elem>::more(int i)
{
    return i < index;
}

template <class Elem>
int StringTable<Elem>::next(int i)
{
    return i + 1;
}

template <class Elem>
void StringTable<Elem>::print()
{
    list_print(std::cerr, tbl);
}

#endif
