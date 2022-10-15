#include "Hashtab.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;

void print_hashtab(Hashtab &ht) {
  const std::list<std::string> &hashtab = ht.get_ht();
  for (auto c : hashtab) {
    if (!(c.empty()))
      cout << c << "\n";
  }
}