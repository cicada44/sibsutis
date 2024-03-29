#ifndef __TPOINT_H__
#define __TPOINT_H__

#include <array>
#include <graphics.h>
#include <iostream>

#define R_DOT 1

class tPoint {
public:
  tPoint() = default;
  tPoint(float x1, float y1, int clr) {
    x = x1;
    y = y1;
    color = clr;
  }
  int get_color() { return this->color; }
  void set_color(int clr) { this->color = clr; }
  int get_x() { return this->x; }
  void set_x(int x) { this->x = x; }
  int get_y() { return this->y; }
  void set_y(int y) { this->y = y; }
  int get_real() { return this->real; }
  void set_real(int real) { this->real = real; }
  int get_vec_x() { return this->vec_x; }
  void set_vec_x(int vec_x) { this->vec_x = vec_x; }
  int get_vec_y() { return this->vec_y; }
  void set_vec_y(int vec_y) { this->vec_y = vec_y; }

  void move_cent_once(float &x, float &y, float &x_c, float &y_c) {
    float dx = x;
    float dy = y;
    x = x_c + (dx - x_c) * cos(M_PI / 180) - (dy - y_c) * sin(M_PI / 180);
    y = y_c + (dx - x_c) * sin(M_PI / 180) + (dy - y_c) * cos(M_PI / 180);
  }

protected:
  int real;
  int color;
  float x;
  float y;
  int vec_x, vec_y;

private:
};

#endif // __TPOINT_H__