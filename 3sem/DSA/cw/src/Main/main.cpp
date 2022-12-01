#include "../Ext_funcs/ext_funcs.hpp"
#include "../Hashtab/Hashtab.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::ostream_iterator;
using std::string;
using std::vector;

void exp_lookup(Hashtab &ht_default, vector<string> &dict) {
  int adding_count = 100000;
  for (int i = 0; i < 10; i++) {
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x);
    }
    cout << "END OF ADDING" << '\n';
    auto start = std::chrono::system_clock::now();
    for (int x = 0; x < adding_count; ++x) {
      ht_default.lookup(dict[x]);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> time = end - start;
    cout << adding_count << '\t' << time.count();
    ht_default.set_null();
    adding_count += 100000;
  }
}

void exp_time(Hashtab &ht_default, vector<string> &dict) {
  int adding_count = 100000;
  for (int i = 0; i < 10; i++) {
    int collisions = 0;
    auto start = std::chrono::system_clock::now();
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 0);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> time = end - start;
    cout << adding_count << '\t' << time.count();
    ht_default.set_null();
    start = std::chrono::system_clock::now();
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 1);
    }
    end = std::chrono::system_clock::now();
    time = end - start;
    cout << '\t' << time.count();
    ht_default.set_null();
    start = std::chrono::system_clock::now();
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 2);
    }
    end = std::chrono::system_clock::now();
    time = end - start;
    cout << '\t' << time.count() << '\n';
    adding_count += 100000;
    ht_default.set_null();
  }
}

void exp_coll(Hashtab &ht_default, vector<string> &dict) {
  int adding_count = 100000;
  for (int i = 0; i < 10; i++) {
    int collisions = 0;
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 0);
    }
    ht_default.set_null();
    cout << adding_count << '\t' << collisions;
    collisions = 0;
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 1);
    }
    ht_default.set_null();
    cout << '\t' << collisions;
    collisions = 0;
    for (int x = 0; x < adding_count; ++x) {
      ht_default.insert(dict[x], x, collisions, 2);
    }
    cout << '\t' << collisions << '\n';
    adding_count += 100000;
    ht_default.set_null();
  }
}

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

#ifdef _EXP_TIME

  exp_time(ht_default, dict);

#endif // EXP_TIME

#ifdef _EXP_COLL

  exp_coll(ht_default, dict);

#endif // _EXP_COLL

#ifdef _EXP_LOOKUP

  cout << "BEGIN" << '\n';

  exp_lookup(ht_default, dict);

#endif // _EXP_LOOKUP

  ht_default.delete_ht();

  return 0;
}