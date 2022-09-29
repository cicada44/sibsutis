#ifndef __TPOINT_H__
#define __TPOINT_H__

#include <array>
#include <graphics.h>
#include <iostream>

#define R_DOT 1
#define X_B 635
#define Y_B 475

class tPoint {
public:
  tPoint() = default;
  tPoint(int x1, int y1, int clr) : x(x1), y(y1), color(clr) {}
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

  void move_once(float &px, float &py, int &pvec_x, int &pvec_y) {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (px == 0)
      pvec_x = 1;
    if (py == 0)
      pvec_y = 1;
    if (px == X_B)
      pvec_x = -1;
    if (py == Y_B)
      pvec_y = -1;
    if (pvec_x == 1)
      px++;
    if (pvec_y == 1)
      py++;
    if (pvec_x == -1)
      px--;
    if (pvec_y == -1)
      py--;
  }

protected:
  int real;
  int color;
  float x, y;
  int vec_x, vec_y;

private:
};

#endif // __TPOINT_H__