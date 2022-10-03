#ifndef __FIELD_H__
#define __FIELD_H__

#include "tPoint.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>

#define SIZEX 200
#define SIZEY 60

class Field {
  friend void
  out_array(std::array<std::array<tPoint, SIZEX>, SIZEY> &array_dots);

public:
  Field() {
    int n = 0;
    for (unsigned x = 0; x < SIZEY; x++) {
      for (unsigned i = 0; i < SIZEX; i++) {
        array_dots[x][i].set_dot();
        array_dots[x][i].set_num(n);
        n++;
      }
    }
  }
  void move_once_x();
  void move_once_random();
  std::array<std::array<tPoint, SIZEX>, SIZEY> &get_arr() { return array_dots; }

private:
  std::array<std::array<tPoint, SIZEX>, SIZEY> array_dots;
};

void Field::move_once_x() {
  for (unsigned x = 0; x < SIZEY; x++) {
    for (unsigned i = 0; i < SIZEX; i++) {
      if (array_dots[x][i].get_real() == 1) {
        if (array_dots[x][i].get_x() == 1 && i != SIZEX - 1) {
          // std::cout << "<MOVE RIGHT> LINE - " << x << "    "
          //           << "TAB - " << i << std::endl;
          array_dots[x][i].set_real(0);
          array_dots[x][i + 1].set_real(1);
          array_dots[x][i + 1].set_x(1);
          array_dots[x][i + 1].set_color(array_dots[x][i].get_color());
          i++;
        } else if (array_dots[x][i].get_x() == 1 && i == SIZEX - 1) {
          // std::cout << "<BOUNSE RIGHT> LINE - " << x << "    "
          // << "TAB - " << i << std::endl;
          array_dots[x][i].set_real(0);
          array_dots[x][0].set_real(1);
          array_dots[x][0].set_color(array_dots[x][i].get_color());
          array_dots[x][0].set_x(-1);
        } else if (array_dots[x][i].get_x() == -1 && i != 0) {
          // std::cout << "<MOVE LEFT> LINE - " << x << "    "
          //           << "TAB - " << i << std::endl;
          array_dots[x][i].set_real(0);
          array_dots[x][i - 1].set_real(1);
          array_dots[x][i - 1].set_x(-1);
          array_dots[x][i - 1].set_color(array_dots[x][i].get_color());
        } else if (array_dots[x][i].get_x() == -1 && i == 0) {
          // std::cout << "<BOUNSE LEFT> LINE - " << x << "    "
          //           << "TAB - " << i << std::endl;
          array_dots[x][i].set_real(0);
          array_dots[x][i + 1].set_real(1);
          array_dots[x][i + 1].set_color(array_dots[x][i].get_color());
          array_dots[x][i + 1].set_x(1);
          i++;
        }
      }
    }
  }
}

void Field::move_once_random() {
  std::array<int, SIZEX * SIZEY> arr_unused;
  int cnt = 0;
  for (unsigned x = 0; x < SIZEY; x++) {
    for (unsigned i = 0; i < SIZEX; i++) {
      if (array_dots[x][i].get_real() == 1) {
        if (array_dots[x][i].get_x() == 1 && array_dots[x][i].get_y() == 1 &&
            x != SIZEY - 1 && i != SIZEX - 1) {
          if (arr_unused.end() == std::find(arr_unused.begin(),
                                            arr_unused.end(),
                                            array_dots[x][i].get_num())) {
            array_dots[x + 1][i + 1] = array_dots[x][i];
            array_dots[x][i].set_real(0);
            arr_unused[cnt] = array_dots[x][i].get_num();
            cnt++;
          }
        }
      }
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