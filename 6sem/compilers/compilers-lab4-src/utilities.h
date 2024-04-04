#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

const char *cool_token_to_string(int tok);
void print_cool_token(int tok);
void print_escaped_string(std::ostream &str, const char *s);
const char *pad(int);

#endif
