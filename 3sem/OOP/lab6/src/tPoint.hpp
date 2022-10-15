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
  tPoint(float x1, float y1, int clr) {
    x = x1;
    y = y1;
    color = clr;
  }
  int get_color() { return this->color; }
  void set_color(int clr) { this->color = clr; }
  float get_x() { return this->x; }
  void set_x(int x) { this->x = x; }
  float get_y() { return this->y; }
  void set_y(int y) { this->y = y; }
  int get_real() { return this->real; }
  void set_real(int real) { this->real = real; }
  float get_vec_x() { return this->vec_x; }
  void set_vec_x(int vec_x) { this->vec_x = vec_x; }
  float get_vec_y() { return this->vec_y; }
  void set_vec_y(int vec_y) { this->vec_y = vec_y; }

  virtual void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0) {
      vec_x = 1;
    }
    if (y == 0) {
      vec_y = 1;
    }
    if (x == X_B) {
      vec_x = -1;
    }
    if (y == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
    }
    if (vec_y == 1) {
      y++;
    }
    if (vec_x == -1) {
      x--;
    }
    if (vec_y == -1) {
      y--;
    }
  }

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
  float vec_x, vec_y;

private:
};

#endif // __TPOINT_H__