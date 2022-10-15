#include "Hashtab.hpp"
#include "ext_funcs_hashtab.hpp"
#include <iostream>

#define SIZE_HT 100000

using std::cin;
using std::cout;

int main() {
  Hashtab ht_default(SIZE_HT);

  print_hashtab(ht_default);

  return 0;
}