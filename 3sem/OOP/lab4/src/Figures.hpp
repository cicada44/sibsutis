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
  int x2, y2;

private:
public:
  Line() = default;
  Line(int px2, int py2) : x2(px2), y2(py2) {}
  void set_x2(int x2) { this->x2 = x2; }
  void set_y2(int y2) { this->y2 = y2; }
  int get_x2() { return this->x2; }
  int get_y2() { return this->y2; }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B) {
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
};

class Triangle : public Line {
protected:
  int x3, y3;

public:
  Triangle() = default;
  Triangle(int px2, int px3, int py2, int py3) : x3(px3), y3(py3) {}
  void set_x3(int x3) { this->x3 = x3; }
  void set_y3(int y3) { this->y3 = y3; }
  int get_x3() { return this->x3; }
  int get_y3() { return this->y3; }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0 || x3 == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0 || y3 == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B || x3 == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B || y3 == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
      x2++;
      x3++;
    }
    if (vec_y == 1) {
      y++;
      y2++;
      y3++;
    }
    if (vec_x == -1) {
      x--;
      x2--;
      x3--;
    }
    if (vec_y == -1) {
      y--;
      y2--;
      y3--;
    }
  }
};

class Rectangle : public Triangle {
protected:
  int x4, y4;

private:
public:
  Rectangle() = default;
  Rectangle(int px4, int py4) : x4(px4), y4(py4) {}
  int get_x4() { return this->x4; }
  int get_y4() { return this->y4; }
  void set_x4(int x4) { this->x4 = x4; }
  void set_y4(int y4) { this->y4 = y4; }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x4 == 0) {
      vec_x = 1;
    }
    if (y == 0 || y4 == 0) {
      vec_y = 1;
    }
    if (x == X_B || x4 == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y4 == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
      x4++;
    }
    if (vec_y == 1) {
      y++;
      y4++;
    }
    if (vec_x == -1) {
      x--;
      x4--;
    }
    if (vec_y == -1) {
      y--;
      y4--;
    }
  }
};

class Circle : public tPoint {
protected:
  int rad;
  int x2, y2;

public:
  Circle() = default;
  void set_x2(int x2) { this->x2 = x2; }
  void set_y2(int y2) { this->y2 = y2; }
  int get_x2() { return this->x2; }
  int get_y2() { return this->y2; }
  int get_rad() { return this->rad; }
  void set_rad(int rad) { this->rad = rad; }

  void seted_rad() { this->rad = sqrt(pow((x2 - x), 2) + pow((y2 - y), 2)); }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0 || x - rad == 0 || x2 - rad == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0 || y - rad == 0 || y2 - rad == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B || x + rad == X_B || x2 + rad == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B || y + rad == Y_B || y2 + rad == Y_B) {
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
};

class Ellipse : public Circle {
protected:
  int x_rad, y_rad;

public:
  Ellipse() = default;
  Ellipse(int px4, int py4) : x_rad(px4), y_rad(py4) {}
  void set_x_rad(int x_rad) { this->x_rad = x_rad; }
  void set_y_rad(int y_rad) { this->y_rad = y_rad; }
  int get_x_rad() { return this->x_rad; }
  int get_y_rad() { return this->y_rad; }

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
};

class Diamond : public Rectangle {
protected:
  int x3, y3;

public:
  void set_x3(int x3) { this->x3 = x3; }
  void set_y3(int y3) { this->y3 = y3; }
  int get_x3() { return this->x3; }
  int get_y3() { return this->y3; }

  void move_once() {
    if (vec_x == 0 || vec_y == 0)
      return;
    if (x == 0 || x2 == 0 || x3 == 0 || x4 == 0) {
      vec_x = 1;
    }
    if (y == 0 || y2 == 0 || y3 == 0 || y4 == 0) {
      vec_y = 1;
    }
    if (x == X_B || x2 == X_B || x3 == X_B || x4 == X_B) {
      vec_x = -1;
    }
    if (y == Y_B || y2 == Y_B || y3 == Y_B || y4 == Y_B) {
      vec_y = -1;
    }
    if (vec_x == 1) {
      x++;
      x2++;
      x3++;
      x4++;
    }
    if (vec_y == 1) {
      y++;
      y2++;
      y3++;
      y4++;
    }
    if (vec_x == -1) {
      x--;
      x2--;
      x3--;
      x4--;
    }
    if (vec_y == -1) {
      y--;
      y2--;
      y3--;
      y4--;
    }
  }
};

#endif // __FIGURES_H__