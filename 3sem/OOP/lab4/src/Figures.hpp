#ifndef __FIGURES_H__
#define __FIGURES_H__

#include "Field.hpp"
#include "tPoint.hpp"
#include <cmath>
#include <iostream>

#define X_B 635
#define Y_B 475

class Line : public tPoint {
protected:
  float x2, y2;

private:
public:
  Line() = default;
  Line(float px, float py, float px2, float py2, float pvec_x = 0,
       float pvec_y = 0, int pclr = 3)
      : x2(px2), y2(py2) {
    x = px;
    y = py;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = pclr;
  }
  void set_x2(int x2) { this->x2 = x2; }
  void set_y2(int y2) { this->y2 = y2; }
  float get_x2() { return this->x2; }
  float get_y2() { return this->y2; }

  void move_once_line() {
    this->move_once(x, y, vec_x, vec_y);
    this->move_once(x2, y2, vec_x, vec_y);
  }

  void move_urself_once() {
    float x_c = (x + x2) / 2;
    float y_c = (y + y2) / 2;
    move_cent_once(x, y, x_c, y_c);
    move_cent_once(x2, y2, x_c, y_c);
  }

  void move_once_line_cp() {
    float x_c = (x + x2) / 2;
    float y_c = (y + y2) / 2;
    this->move_once_cp(x, y, x_c, y_c, vec_x, vec_y);
    this->move_once_cp(x2, y2, x_c, y_c, vec_x, vec_y);
  }
};

class Triangle : public Line {
protected:
  float x3, y3;

public:
  Triangle() = default;
  Triangle(float px, float py, float px2, float py2, float px3, float py3,
           float pvec_x = 0, float pvec_y = 0, int pclr = 3) {
    x = px;
    y = py;
    x2 = px2;
    y2 = py2;
    x3 = px3;
    y3 = py3;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = pclr;
  }
  void set_x3(int x3) { this->x3 = x3; }
  void set_y3(int y3) { this->y3 = y3; }
  float get_x3() { return this->x3; }
  float get_y3() { return this->y3; }

  void move_once_trian() {
    this->move_once(x, y, vec_x, vec_y);
    this->move_once(x2, y2, vec_x, vec_y);
    this->move_once(x3, y3, vec_x, vec_y);
  }

  void move_urself_once() {
    float x_c = (x + x2 + x3) / 3;
    float y_c = (y + y2 + y3) / 3;
    move_cent_once(x, y, x_c, y_c);
    move_cent_once(x2, y2, x_c, y_c);
    move_cent_once(x3, y3, x_c, y_c);
  }

  void move_once_trian_cp() {
    float x_c = (x + x2 + x3) / 3;
    float y_c = (y + y2 + y3) / 3;
    move_once_cp(x, y, x_c, y_c, vec_x, vec_y);
    move_once_cp(x2, y2, x_c, y_c, vec_x, vec_y);
    move_once_cp(x3, y3, x_c, y_c, vec_x, vec_y);
  }
};

class Rectangle : public Triangle {
protected:
  float x4, y4;

private:
public:
  Rectangle() = default;
  Rectangle(float px, float py, float px2, float py2, float px3, float py3,
            float px4, float py4, float pvec_x = 0, float pvec_y = 0,
            int pclr = 3) {
    x = px;
    y = py;
    x2 = px2;
    y2 = py2;
    x3 = px3;
    y3 = py3;
    x4 = px4;
    y4 = py4;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = pclr;
  }
  float get_x4() { return this->x4; }
  float get_y4() { return this->y4; }
  void set_x4(int x4) { this->x4 = x4; }
  void set_y4(int y4) { this->y4 = y4; }

  void move_once_rect() {
    this->move_once(x, y, vec_x, vec_y);
    this->move_once(x2, y2, vec_x, vec_y);
    this->move_once(x3, y3, vec_x, vec_y);
    this->move_once(x4, y4, vec_x, vec_y);
  }

  void move_urself_once() {
    float x_c = (x + x3) / 2;
    float y_c = (y + y3) / 2;
    move_cent_once(x, y, x_c, y_c);
    move_cent_once(x2, y2, x_c, y_c);
    move_cent_once(x3, y3, x_c, y_c);
    move_cent_once(x4, y4, x_c, y_c);
  }

  void move_once_rectangle_cp() {
    float x_c = (x + x3) / 2;
    float y_c = (y + y3) / 2;
    move_once_cp(x, y, x_c, y_c, vec_x, vec_y);
    move_once_cp(x2, y2, x_c, y_c, vec_x, vec_y);
    move_once_cp(x3, y3, x_c, y_c, vec_x, vec_y);
    move_once_cp(x4, y4, x_c, y_c, vec_x, vec_y);
  }
};

class Circle : public tPoint {
protected:
  int rad;
  float x2, y2;

public:
  Circle() = default;
  Circle(float px, float py, float px2, float py2, int pvec_x = 0,
         int pvec_y = 0, int clr = 3) {
    x = px;
    y = py;
    x2 = px2;
    y2 = py2;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = clr;
    this->seted_rad();
  }
  void set_x2(int x2) { this->x2 = x2; }
  void set_y2(int y2) { this->y2 = y2; }
  float get_x2() { return this->x2; }
  float get_y2() { return this->y2; }
  int get_rad() { return this->rad; }
  void set_rad(int rad) { this->rad = rad; }

  void seted_rad() { this->rad = sqrt(pow((x2 - x), 2) + pow((y2 - y), 2)); }

  void move_once_circle() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0 || x - rad == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0 || y - rad == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B || x + rad == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B || y + rad == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
      x2++;
    }
    if (vec_y == 1) {
      y++;
      y2++;
    }
    if (vec_x == -1) {
      x--;
      x2--;
    }
    if (vec_y == -1) {
      y--;
      y2--;
    }
  }

  void move_once_circle_cp() { move_once_cp(x, y, x, y, vec_x, vec_y); }
};

class Ellipse : public Circle {
protected:
  float x_rad, y_rad;

public:
  Ellipse() = default;
  Ellipse(float px, float py, float px2, float py2, float pxrad, float pyrad,
          int pvec_x = 0, int pvec_y = 0, int clr = 3) {
    x = px;
    y = py;
    x2 = px2;
    y2 = py2;
    x_rad = pxrad;
    y_rad = pyrad;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = clr;
  }
  void set_x_rad(int x_rad) { this->x_rad = x_rad; }
  void set_y_rad(int y_rad) { this->y_rad = y_rad; }
  float get_x_rad() { return this->x_rad; }
  float get_y_rad() { return this->y_rad; }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0 || x - x_rad == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0 || y - y_rad == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B || x + x_rad == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B || y + y_rad == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
      x2++;
      y2++;
    }
    if (vec_y == 1) {
      y++;
      y2++;
      x2++;
    }
    if (vec_x == -1) {
      x--;
      x2--;
      y2--;
    }
    if (vec_y == -1) {
      y--;
      y2--;
      x2--;
    }
  }

  void move_once_ell_cp() { move_once_cp(x, y, x, y, vec_x, vec_y); }

  void move_urself_once() {
    float t = x_rad;
    x_rad = y_rad;
    y_rad = t;
  }
};

class Diamond : public Rectangle {
protected:
  float x3, y3;

public:
  Diamond() = default;
  Diamond(float px, float py, float px2, float py2, float px3, float py3,
          float px4, float py4, float pvec_x = 0, float pvec_y = 0,
          int pclr = 3) {
    x = px;
    y = py;
    x2 = px2;
    y2 = py2;
    x3 = px3;
    y3 = py3;
    x4 = px4;
    y4 = py4;
    vec_x = pvec_x;
    vec_y = pvec_y;
    color = pclr;
  }
  void set_x3(int x3) { this->x3 = x3; }
  void set_y3(int y3) { this->y3 = y3; }
  int get_x3() { return this->x3; }
  int get_y3() { return this->y3; }

  void move_once_diam() {
    this->move_once(x, y, vec_x, vec_y);
    this->move_once(x2, y2, vec_x, vec_y);
    this->move_once(x3, y3, vec_x, vec_y);
    this->move_once(x4, y4, vec_x, vec_y);
  }

  void move_urself_once() {
    float x_c = (x + x3) / 2;
    float y_c = (y + y3) / 2;
    move_cent_once(x, y, x_c, y_c);
    move_cent_once(x2, y2, x_c, y_c);
    move_cent_once(x3, y3, x_c, y_c);
    move_cent_once(x4, y4, x_c, y_c);
  }

  void move_once_diamond_cp() {
    float x_c = (x + x3) / 2;
    float y_c = (y + y3) / 2;
    move_once_cp(x, y, x_c, y_c, vec_x, vec_y);
    move_once_cp(x2, y2, x_c, y_c, vec_x, vec_y);
    move_once_cp(x3, y3, x_c, y_c, vec_x, vec_y);
    move_once_cp(x4, y4, x_c, y_c, vec_x, vec_y);
  }
};

#endif // __FIGURES_H__