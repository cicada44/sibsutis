#include "../Ext_funcs/ext_funcs.hpp"
#include "../Hashtab/Hashtab.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::istream_iterator;
using std::pair;
using std::string;

unsigned int AddHash(const char *s) {
  unsigned int h = 0;
  unsigned int cnter_s = 0;
  while (*s) {
    h += (unsigned int)*s++;
    ++cnter_s;
  }
  return h % SIZE_HT;
}

unsigned int Jen(const string &s) {
  unsigned int hash, i;
  for (hash = i = 0; i < s.size(); ++i) {
    hash += s[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash % SIZE_HT;
}

unsigned int DJB2(const string &s) {
  unsigned long hash = 5381;
  for (auto c : s) {
    hash = (hash << 5) + hash + c; /* hash * 33 + c */
  }
  return hash % SIZE_HT;
}

unsigned int FNVHash(const string &str) {
  const unsigned int fnv_prime = 0x811C9DC5;
  unsigned int hash = 0;
  unsigned int i = 0;
  unsigned int len = str.length();

  for (i = 0; i < len; i++) {
    hash *= fnv_prime;
    hash ^= (str[i]);
  }

  return hash % SIZE_HT;
}

unsigned int KRHash(const string &s) {
  unsigned int h = 0, hash_mul = 31;
  for (auto x = s.begin(); x != s.end(); x++)
    h = h * hash_mul + (unsigned int)*x;
  return h % SIZE_HT;
}

unsigned int ELFHash(const string &s) {
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

bool validate(const string &key) {
  if (key.empty()) {
    cout << "[!!!] Can't validate this key";
    return 1;
  }
  return 0;
}

bool validate(const int value) {
  if (value < 0) {
    cout << "[!!!] Can't validate this value";
    return 1;
  }
  return 0;
}

void visual() {
  Hashtab hashtab(SIZE_HT);

  size_t opt;
  string key;
  int value;

  while (1) {
    cout << "[~] Select option" << '\n';
    cin >> opt;
    if (opt == 1) {
      cout << "[!] Enter the key: ";
      cin >> key;
      if (validate(key))
        continue;
      cout << "[!] Enter the value: ";
      cin >> value;
      if (validate(value))
        continue;
      hashtab.insert(key, value);
    } else if (opt == 2) {
      cout << "[!] Enter the key to find: ";
      cin >> key;
      if (validate(key))
        continue;
      pair<string, int> p = hashtab.lookup_pair(key);
      cout << "[I] RESULT: ";
      if (p.second == -1)
        cout << "EMPTY" << '\n';
      else
        cout << "key - " << p.first << "   value - " << p.second << '\n';
    } else if (opt == 3) {
      cout << "[!] Enter the key to delete: ";
      cin >> key;
      if (validate(key))
        continue;
      if (hashtab.delete_node(key))
        cout << "[I] DELETED\n";
      else
        cout << "[!!!] This node is not detected\n";
    } else if (opt == 4) {
      print_hashtab(hashtab);
    }
  }
}

void test_coll() {
  string s;
  while (1) {
    cin >> s;
    cout << "DJB2: " << DJB2(s) << '\n';
    cout << "FNV: " << FNVHash(s) << '\n';
    cout << "add: " << AddHash(s.c_str()) << '\n';
    cout << "Jen: " << Jen(s) << '\n';
    cout << "KR: " << KRHash(s) << '\n';
    cout << "ELF: " << ELFHash(s) << '\n';
  }
}

int main() {
  test_coll();
  return 0;
}
