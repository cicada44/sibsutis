#ifndef __TPOINT_H__
#define __TPOINT_H__

#include <cstdlib>
#include <iostream>
#include <string>

class tPoint {
  // friend void set_dot(tPoint &d);

public:
  int get_real() { return this->real; }
  int get_color() { return this->color; }
  int get_x() { return this->x; }
  int get_y() { return this->y; }
  void set_real(int r) { this->real = r; }
  void set_color(unsigned c) { this->color = c; }
  void set_x(int vec) { this->x = vec; }
  void set_y(int vec) { this->y = vec; }
  void set_dot() {
    this->y = 0;
    this->x = 1;
    this->real = rand() % 10;
    this->color = rand() % 7;
  }

private:
  int x;
  int y;
  int real;
  unsigned color;
};

#endif // __TPOINT_H__