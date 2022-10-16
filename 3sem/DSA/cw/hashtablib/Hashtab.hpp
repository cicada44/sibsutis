#ifndef __HASHTAB_H__
#define __HASHTAB_H__

#include <cmath>
#include <string>
#include <vector>

class Hashtab {
public:
  Hashtab() = default;
  Hashtab(const long long size);
  const std::vector<std::string> &get_ht();
  void add(const std::string &, const std::string &);

private:
  long long size_ht;
  std::vector<std::string> ht;
};

#endif // __HASHTAB_H__