#ifndef __HASHTAB_H__
#define __HASHTAB_H__

#include <list>
#include <string>

class Hashtab {
public:
  Hashtab() = default;
  Hashtab(const long long size);
  const std::list<std::string> &get_ht();

private:
  long long size_ht;
  std::list<std::string> ht;
};

#endif // __HASHTAB_H__