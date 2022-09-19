#include "field.hpp"
#include "tPoint.hpp"
#include <array>
#include <iostream>
#include <string>
#include <unistd.h>

#define clrcsl() std::cout << "\x1B[2J\x1B[H"

int main() {

  Field field;

  while (1) {
    clrcsl();
    out_array(field.get_arr());
    field.move_once();
    sleep(1);
  }

  return 0;
}