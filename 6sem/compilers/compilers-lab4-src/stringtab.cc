#include <iostream>
#include "stringtab.h"
#include "utilities.h"

std::ostream& operator<<(std::ostream &s, const Entry &sym)
{
    return s << sym.get_string();
}

std::ostream& operator<<(std::ostream& s, Symbol sym)
{
    return s << *sym;
}

// A Symbol is a pointer to an Entry
// Symbols are stored directly as nodes of the abstract syntax tree
Symbol copy_Symbol(const Symbol s)
{
    return s;
}

void dump_Symbol(std::ostream& s, int n, Symbol sym)
{
    s << pad(n) << sym << std::endl;
}

StringEntry::StringEntry(char *s, int l, int i) : Entry(s, l, i) { }
IdEntry::IdEntry(char *s, int l, int i) : Entry(s, l, i) { }
IntEntry::IntEntry(char *s, int l, int i) : Entry(s, l, i) { }

IdTable idtable;
IntTable inttable;
StrTable stringtable;
