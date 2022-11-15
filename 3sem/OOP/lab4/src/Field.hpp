#ifndef __FIELD_H__
#define __FIELD_H__

#include "Figures.hpp"
#include "tPoint.hpp"
#include <array>
#include <graphics.h>

#define X_B 635
#define Y_B 475

class Field {
public:
  Field() = default;

  void init();
  void draw_dot(tPoint &tp);
  void draw_line(Line &l);
  void draw_rectangle(Rectangle &rect);
  void draw_circle(Circle &c);
  void draw_triangle(Triangle &trian);
  void draw_ellipse(Ellipse &ellipse);
  void draw_diamond(Diamond &diam);

private:
};

void Field::init() {
  int gm, gl = DETECT;
  initgraph(&gl, &gm, NULL);
}

void Field::draw_dot(tPoint &tp) {
  setcolor(tp.get_color());
  circle(tp.get_x(), tp.get_y(), R_DOT);
}

void Field::draw_line(Line &l) {
  setcolor(l.get_color());
  line(l.get_x(), l.get_y(), l.get_x2(), l.get_y2());
}

void Field::draw_rectangle(Rectangle &rect) {
  setcolor(rect.get_color());
  line(rect.get_x(), rect.get_y(), rect.get_x2(), rect.get_y2());
  line(rect.get_x2(), rect.get_y2(), rect.get_x3(), rect.get_y3());
  line(rect.get_x3(), rect.get_y3(), rect.get_x4(), rect.get_y4());
  line(rect.get_x4(), rect.get_y4(), rect.get_x(), rect.get_y());
}

void Field::draw_circle(Circle &c) {
  setcolor(c.get_color());
  circle(c.get_x(), c.get_y(), c.get_rad());
}

void Field::draw_triangle(Triangle &trian) {
  setcolor(trian.get_color());
  Line l1, l2, l3;
  l1.set_x(trian.get_x());
  l1.set_y(trian.get_y());
  l1.set_x2(trian.get_x2());
  l1.set_y2(trian.get_y2());
  l1.set_color(3);

  l2.set_x(trian.get_x2());
  l2.set_y(trian.get_y2());
  l2.set_x2(trian.get_x3());
  l2.set_y2(trian.get_y3());
  l2.set_color(3);

  l3.set_x(trian.get_x());
  l3.set_y(trian.get_y());
  l3.set_x2(trian.get_x3());
  l3.set_y2(trian.get_y3());
  l3.set_color(3);

  draw_line(l1);
  draw_line(l2);
  draw_line(l3);
}

void Field::draw_ellipse(Ellipse &ellip) {
  setcolor(ellip.get_color());
  ellipse(ellip.get_x(), ellip.get_y(), ellip.get_x2(), ellip.get_y2(),
          ellip.get_x_rad(), ellip.get_y_rad());
}

void Field::draw_diamond(Diamond &diam) {
  setcolor(diam.get_color());
  Line l1, l2, l3, l4;
  l1.set_x(diam.get_x());
  l1.set_y(diam.get_y());
  l1.set_x2(diam.get_x2());
  l1.set_y2(diam.get_y2());
  l1.set_color(3);

  l2.set_x(diam.get_x2());
  l2.set_y(diam.get_y2());
  l2.set_x2(diam.get_x3());
  l2.set_y2(diam.get_y3());
  l2.set_color(3);

  l3.set_x(diam.get_x3());
  l3.set_y(diam.get_y3());
  l3.set_x2(diam.get_x4());
  l3.set_y2(diam.get_y4());
  l3.set_color(3);

  l4.set_x(diam.get_x4());
  l4.set_y(diam.get_y4());
  l4.set_x2(diam.get_x());
  l4.set_y2(diam.get_y());
  l4.set_color(3);

  draw_line(l1);
  draw_line(l2);
  draw_line(l3);
  draw_line(l4);
}

#endif // __FIELD_H__