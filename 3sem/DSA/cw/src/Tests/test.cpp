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

int main() {
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

  return 0;
}
