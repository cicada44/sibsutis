#ifndef __FIELD_H__
#define __FIELD_H__

#include "tPoint.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>

#define SIZEX 20
#define SIZEY 10

class Field {
  friend void
  out_array(std::array<std::array<tPoint, SIZEX>, SIZEY> &array_dots);

public:
  Field() {
    for (unsigned x = 0; x < SIZEY; x++) {
      for (unsigned i = 0; i < SIZEX; i++) {
        array_dots[x][i].set_dot();
      }
    }
  }
  void move_once();
  std::array<std::array<tPoint, SIZEX>, SIZEY> &get_arr() { return array_dots; }

private:
  std::array<std::array<tPoint, SIZEX>, SIZEY> array_dots;
  std::array<std::array<int, SIZEX>, SIZEY> array_vector;
};

void Field::move_once() {
  for (unsigned x = 0; x < SIZEY; x++) {
    for (unsigned i = 0; i < SIZEX; i++) {
      // if (array_dots[x][i].)
    }
  }
}

void out_array(std::array<std::array<tPoint, SIZEX>, SIZEY> &array_dots);

void out_array(std::array<std::array<tPoint, SIZEX>, SIZEY> &array_dots) {
  for (unsigned x = 0; x != SIZEX; x++)
    std::cout << "_";
  std::cout << std::endl;
  for (unsigned x = 0; x < SIZEY; x++) {
    std::cout << "|";
    for (unsigned i = 0; i < SIZEX; i++) {
      if (array_dots[x][i].get_real() == 1) {
        std::string colored_text =
            "\033[0;3" +
            std::string(std::to_string(array_dots[x][i].get_color())) +
            std::string("m") + std::string("*") + std::string("\033[0m");
        std::cout << colored_text;
      } else {
        std::cout << " ";
      }
    }
    std::cout << "|";
    std::cout << std::endl;
  }
  for (unsigned x = 0; x != SIZEX; x++)
    std::cout << "_";
  std::cout << std::endl;
}

#endif // __FIELD_H__