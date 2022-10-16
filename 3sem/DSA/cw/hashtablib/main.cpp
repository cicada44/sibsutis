#include "Hashtab.hpp"
#include "ext_funcs_hashtab.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 100

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "problems with count of arguments\n";
    exit(-1);
  }

  string default_value = "def";

  Hashtab ht_default(SIZE_HT);

  vector<string> dict;

  if (read_dict(argv[1], dict)) {
    cout << "no such file named " << argv[1] << "\n";
    exit(-1);
  }

  cout << "count of lines - " << dict.size() << "\n";

  for (auto &c : dict) {
    ht_default.add(c, default_value);
    // cout << "line - " << c << "\n";
  }

  print_hashtab(ht_default);

  return 0;
}