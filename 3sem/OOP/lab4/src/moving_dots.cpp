#include "Field.hpp"
#include "tPoint.hpp"
#include <array>
#include <cstdlib>
#include <graphics.h>

#define DELAY_LONG 100000
#define DELAY_SHORT 1000
#define DELAY_USHORT 100
#define DELAY_UMSHORT 1
#define DOTS_COUNT 100

int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void move_dots_once(std::array<tPoint, DOTS_COUNT> &field) {
  for (int x = 0; x < DOTS_COUNT; x++) {
    if (field[x].get_real() == 1) {
      if (field[x].get_x() == X_B)
        field[x].set_vec_x(-1);
      if (field[x].get_y() == Y_B)
        field[x].set_vec_y(-1);
      if (field[x].get_x() == 1)
        field[x].set_vec_x(1);
      if (field[x].get_y() == 1)
        field[x].set_vec_y(1);
      field[x].set_x(field[x].get_x() + field[x].get_vec_x());
      field[x].set_y(field[x].get_y() + field[x].get_vec_y());
    }
  }
}

void init_field_dots(std::array<tPoint, DOTS_COUNT> &field) {
  for (int x = 0; x < DOTS_COUNT; x++) {
    field[x].set_real(rand() % 2);
    if (field[x].get_real() == 1) {
      field[x].set_x(getrand(0, 635));
      field[x].set_y(getrand(0, 475));
      field[x].set_color(getrand(1, 15));
      int vec_x = getrand(0, 2);
      int vec_y = getrand(0, 2);

      if (vec_x == 0)
        field[x].set_vec_x(-1);
      else if (vec_x == 1)
        field[x].set_vec_x(0);
      else if (vec_x == 2)
        field[x].set_vec_x(1);

      if (vec_y == 0)
        field[x].set_vec_y(-1);
      else if (vec_y == 1)
        field[x].set_vec_y(0);
      else if (vec_y == 2)
        field[x].set_vec_y(1);
    }
  }
}

void print_field_dots(std::array<tPoint, DOTS_COUNT> &field, Field &f) {
  for (int x = 0; x < DOTS_COUNT; x++) {
    if (field[x].get_real() == 1)
      f.draw_dot(field[x].get_x(), field[x].get_y(), field[x].get_color());
  }
}

int main() {
  Field f;

  f.init();

  std::array<tPoint, DOTS_COUNT> field;

  init_field_dots(field);

  while (1) {
    print_field_dots(field, f);
    move_dots_once(field);
    delay(DELAY_UMSHORT);
    cleardevice();
  }

  // for (int x = 5; x < 375; x++) {
  //   delay(DELAY_UMSHORT);
  //   cleardevice();
  //   f.draw_dot(x, 100, 5);
  // }

  // bar(left + 300, top, right + 300, bottom);
  // line(left - 10, top + 150, left + 410, top + 150);
  // ellipse(x, y + 200, 0, 360, 100, 50);
  // outtextxy(left + 100, top + 325, "C Graphics Program");

  delay(DELAY_LONG);
  closegraph();
  return 0;
}