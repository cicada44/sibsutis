#include "../Ext_funcs/ext_funcs.hpp"
#include "../Hashtab/Hashtab.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 1000000000

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

  int collisions = 0;
  int n = 0;

  auto start = std::chrono::system_clock::now();

  /* adding... */
  for (auto &c : dict) {
    ht_default.insert(c, n, collisions);
    ++n;
  }

  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> time = end - start;

  cout << "time - " << time.count() << '\n';

  return 0;
}