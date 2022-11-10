#include "Hashtab.hpp"
#include "ext_funcs_hashtab.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 20001

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main(int argc, char **argv) {
  int collisions = 0;

  if (argc != 2) {
    cout << "problems with count of arguments\n";
    exit(-1);
  }

  Hashtab ht_default(SIZE_HT);

  vector<string> dict;

  if (read_dict(argv[1], dict)) {
    cout << "no such file named " << argv[1] << "\n";
    exit(-1);
  }

  /* hashtab working... */

  int n = 0;

  for (auto &c : dict) {
    ht_default.add_dhash(c, n, collisions);
    n++;
  }

  // print_hashtab(ht_default);

  cout << "n - " << n << "\n";

  return 0;
}