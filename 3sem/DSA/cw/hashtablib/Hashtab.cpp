#include "Hashtab.hpp"
#include <list>
#include <string>

Hashtab::Hashtab(const long long size) : size_ht(size) {
  for (long long i = 0; i != size; i++)
    ht.emplace_back("");
}

const std::list<std::string> &Hashtab::get_ht() { return ht; }
