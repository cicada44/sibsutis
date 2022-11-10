#include "Hashtab.hpp"
#include "ext_funcs_hashtab.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

Hashtab::Hashtab(const long long size) : size_ht(size) {
  for (long long i = 0; i != size; i++)
    ht.push_back(-1);
}

const vector<int> &Hashtab::get_ht() { return ht; }

unsigned int Hashtab::KRHash(const string &s) {
  unsigned int h = 0, hash_mul = 31;
  for (auto x = s.begin(); x != s.end(); x++)
    h = h * hash_mul + (unsigned int)*x;
  return h % SIZE_HT;
}

unsigned int Hashtab::ELFHash(const string &s) {
  unsigned int h = 0, g;
  for (auto c = s.begin(); c != s.end(); c++) {
    h = (h << 4) + (unsigned int)*c;
    g = h & 0xF0000000L;
    if (g)
      h ^= g >> 24;
    h &= ~g;
  }
  return h % SIZE_HT;
}

void Hashtab::add_dhash(const string &key, const int &value, int &col) {
  int hcode = ELFHash(key);
  for (int i = 1; i < SIZE_HT; i++) {
    if (ht[hcode] != -1) {
      hcode = (ELFHash(key) + i * KRHash(key)) % SIZE_HT;
      col++;
    } else {
      ht[hcode] = value;
      break;
    }
  }
  std::cout << "key - " << key << "\thcode - " << hcode << "\n";
}

void Hashtab::add_kidding(const string &key, const int &value, int &col) {
  int hcode = ELFHash(key);
  if (ht[hcode] != -1)
    col++;
  ht[hcode] = value;
}

int Hashtab::lookup(const string &key) {
  int hcode = ELFHash(key);
  return ht[hcode];
}
