#include "Hashtab.hpp"
#include "../Ext_funcs/ext_funcs.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define SIZE_HT 1000000000

using std::array;
using std::pair;
using std::string;

Hashtab::Hashtab(int64_t cap) : capacity(cap) {
  for (long long i = 0; i != SIZE_HT; i++)
    ht[i] = {"", -1};
  _size = 0;
}

const array<pair<string, int>, SIZE_HT> &Hashtab::get_ht() { return ht; }

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

void Hashtab::insert(const string &key, const int &value, int &col) {
  int flag = 0;
  int hcode = ELFHash(key);
  int probe = KRHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if (ht[hcode].second != -1) {
      hcode = (hcode + i * probe) % SIZE_HT;
      if (!flag)
        col++;
      flag = 1;
    } else {
      ht[hcode] = {key, value};
      ++_size;
      break;
    }
  }
}

int Hashtab::lookup(const string &key) {
  int hcode = ELFHash(key);
  int probe = KRHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if (ht[hcode].second != -1 && ht[hcode].first == key)
      return ht[hcode].second;
    hcode = (hcode + 1 * probe) % SIZE_HT;
  }
  return ht[hcode].second;
}

pair<string, int> &Hashtab::lookup_pair(const string &key) {
  int hcode = ELFHash(key);
  int probe = KRHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if (ht[hcode].second != -1 && ht[hcode].first == key)
      return ht[hcode];
    hcode = (hcode + 1 * probe) % SIZE_HT;
  }
  return ht[hcode];
}

bool Hashtab::delete_node(const std::string &key) {
  int hcode = ELFHash(key);
  int probe = KRHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if (ht[hcode].second != -1 && ht[hcode].first == key) {
      ht[hcode].first = "";
      ht[hcode].second = -1;
      --_size;
      return 1;
    }
    hcode = (hcode + 1 * probe) % SIZE_HT;
  }
  return 0;
}

int Hashtab::max() {
  pair<string, int> pair_max;
  for (auto x = ht.cbegin(); x != ht.cend(); ++x)
    if (x->first > pair_max.first)
      pair_max = *x;
  return pair_max.second;
}

int Hashtab::min() {
  pair<string, int> pair_min;
  for (auto x = ht.cbegin(); x != ht.cend(); ++x)
    if (x->first < pair_min.first)
      pair_min = *x;
  return pair_min.second;
}

int64_t Hashtab::size() { return _size; }
