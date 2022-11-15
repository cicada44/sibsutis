#include "field.hpp"
#include "tPoint.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#define clrcsl() std::cout << "\x1B[2J\x1B[H"

int main() {

  Field field;

  while (1) {
    clrcsl();
    out_array(field.get_arr());
    field.move_once_x();
    usleep(100000);
  }

  return 0;
}