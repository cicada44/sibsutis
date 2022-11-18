#include "../Ext_funcs/ext_funcs.hpp"
#include "../Hashtab/Hashtab.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 500000

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main(int argc, char **argv) {

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

  cout << "ADDED"
       << "\n\n\n";

  /* hashtab working... */
  int collisions = 0;
  int n = 1;
  for (auto &c : dict) {
    ht_default.add_dhash(c, n, collisions);
    n++;
  }

  cout << "ADDED"
       << "\n\n\n";

  print_hashtab(ht_default);

  int t = ht_default.lookup("rab");

  cout << "collisions - " << collisions << '\n';
  // cout << "n - " << n << '\n';
  cout << "lookuped - " << t << '\n';
  cout << "SIZE - " << sizeof(ht_default);

  return 0;
}