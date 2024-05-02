#pragma once

#include <ostream>

const char *cool_token_to_string(int tok);
void print_cool_token(int tok);
void print_escaped_string(std::ostream &str, const char *s);
const char *pad(int);
