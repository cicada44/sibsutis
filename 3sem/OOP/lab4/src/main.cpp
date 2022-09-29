#include "Field.hpp"
#include "Figures.hpp"
#include "tPoint.hpp"
#include <array>
#include <cstdlib>
#include <graphics.h>

#define DELAY_LONG 100000
#define DELAY_SHORT 1000
#define DELAY_USHORT 100
#define DELAY_UMSHORT 1

int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void draw_dot_lt(Field &f, tPoint &point) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    // point.move_once(point.get_x(), point.get_y(), point.get_vec_x(),
    //                 point.get_vec_y());
    f.draw_dot(point);
  }
}

void draw_line_lt(Field &f, Line &line) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    line.move_once_line();
    f.draw_line(line);
  }
}

void draw_line_urself_lt(Field &f, Line &line) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    line.move_urself_once();
    f.draw_line(line);
    std::cout << "LINE x - " << line.get_x2() << " y - " << line.get_y2()
              << std::endl;
  }
}

void draw_trian_lt(Field &f, Triangle &trian) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    trian.move_once_trian();
    f.draw_triangle(trian);
  }
}

void draw_trian_urself_lt(Field &f, Triangle &trian) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    trian.move_urself_once();
    f.draw_triangle(trian);
  }
}

void draw_rect_lt(Field &f, Rectangle &rect) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    rect.move_once_rect();
    f.draw_rectangle(rect);
  }
}

void draw_rect_urself_lt(Field &f, Rectangle &rect) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    rect.move_urself_once();
    f.draw_rectangle(rect);
  }
}

void draw_circ_lt(Field &f, Circle &circ) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    circ.move_once_circle();
    f.draw_circle(circ);
  }
}

void draw_diam_lt(Field &f, Diamond &diam) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    diam.move_once_diam();
    f.draw_diamond(diam);
  }
}

void draw_diam_urself_lt(Field &f, Diamond &diam) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    diam.move_urself_once();
    f.draw_diamond(diam);
    std::cout << "DIAM x - " << (diam.get_x() + diam.get_x3()) / 2 << " y - "
              << (diam.get_y() + diam.get_y3()) / 2 << std::endl;
  }
}

void draw_ell_lt(Field &f, Ellipse &ell) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    ell.move_once();
    f.draw_ellipse(ell);
  }
}

void draw_ell_urself_lt(Field &f, Ellipse &ell) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_USHORT);
    cleardevice();
    ell.move_urself_once();
    f.draw_ellipse(ell);
  }
}

void move_all_illustration(Field &f, Line &line, Rectangle &rect,
                           Triangle &trian, Circle &cir, Ellipse &ell,
                           Diamond &diam) {
  outtextxy(100, 325, "LINE MOVING");
  delay(2000);
  draw_line_lt(f, line);
  outtextxy(100, 325, "TRIANGLE MOVING");
  delay(2000);
  draw_trian_lt(f, trian);
  outtextxy(100, 325, "RECTANGLE MOVING");
  delay(2000);
  draw_rect_lt(f, rect);
  outtextxy(100, 325, "CIRCLE MOVING");
  delay(2000);
  draw_circ_lt(f, cir);
  outtextxy(100, 325, "DIAMOND MOVING");
  delay(2000);
  draw_diam_lt(f, diam);
  outtextxy(100, 325, "ELLIPSE MOVING");
  delay(2000);
  draw_ell_lt(f, ell);
  cleardevice();
}

void move_all_illustration_urself(Field &f, Line &line, Rectangle &rect,
                                  Triangle &trian, Circle &cir, Ellipse &ell,
                                  Diamond &diam) {
  outtextxy(100, 325, "LINE MOVING");
  delay(2000);
  draw_line_urself_lt(f, line);
  outtextxy(100, 325, "TRIANGLE MOVING");
  delay(2000);
  draw_trian_urself_lt(f, trian);
  outtextxy(100, 325, "RECTANGLE MOVING");
  delay(2000);
  draw_rect_urself_lt(f, rect);
  outtextxy(100, 325, "DIAMOND MOVING");
  delay(2000);
  draw_diam_urself_lt(f, diam);
  outtextxy(100, 325, "ELLIPSE MOVING");
  delay(2000);
  draw_ell_urself_lt(f, ell);
  cleardevice();
}

int main() {
  Field f;
  f.init();

  tPoint point;
  point.set_x(40);
  point.set_y(40);
  point.set_vec_x(1);
  point.set_vec_y(1);
  point.set_color(3);

  Line line1(100, 100);
  line1.set_x(getmaxy() / 2);
  line1.set_y(getmaxy() / 2);
  line1.set_x2(300);
  line1.set_y2(350);
  line1.set_color(5);
  line1.set_vec_x(1);
  line1.set_vec_y(1);

  Rectangle rect1;
  rect1.set_x(200);
  rect1.set_y(200);
  rect1.set_x2(300);
  rect1.set_y2(200);
  rect1.set_x3(300);
  rect1.set_y3(270);
  rect1.set_x4(200);
  rect1.set_y4(270);
  rect1.set_color(4);
  rect1.set_vec_x(1);
  rect1.set_vec_y(1);

  Circle circle1;
  circle1.set_x(200);
  circle1.set_y(200);
  circle1.set_x2(250);
  circle1.set_y2(200);
  circle1.seted_rad();
  circle1.set_color(3);
  circle1.set_vec_x(1);
  circle1.set_vec_y(1);

  Triangle trian1;
  trian1.set_x(200);
  trian1.set_y(200);
  trian1.set_x2(350);
  trian1.set_y2(350);
  trian1.set_x3(200);
  trian1.set_y3(350);
  trian1.set_color(2);
  trian1.set_vec_x(1);
  trian1.set_vec_y(1);

  Ellipse ellip1;
  ellip1.set_x(100);
  ellip1.set_y(300);
  ellip1.set_x2(0);
  ellip1.set_y2(360);
  ellip1.set_x_rad(100);
  ellip1.set_y_rad(50);
  ellip1.set_vec_x(1);
  ellip1.set_vec_y(1);
  ellip1.set_color(3);

  Diamond diam1;
  diam1.set_x(200);
  diam1.set_y(200);
  diam1.set_x2(250);
  diam1.set_y2(300);
  diam1.set_x3(300);
  diam1.set_y3(200);
  diam1.set_x4(250);
  diam1.set_y4(100);
  diam1.set_vec_x(1);
  diam1.set_vec_y(1);

  // f.draw_dot(point);
  // f.draw_circle(circle1);
  // f.draw_line(line1);
  // f.draw_rectangle(rect1);
  // f.draw_triangle(trian1);
  // f.draw_ellipse(ellip1);
  // f.draw_diamond(diam1);

  // draw_dot_lt(f, point);
  // draw_line_lt(f, line1);
  // draw_trian_lt(f, trian1);
  // draw_rect_lt(f, rect1);
  // draw_circ_lt(f, circle1);
  // draw_diam_lt(f, diam1);
  // draw_ell_lt(f, ellip1);

  // draw_line_urself_lt(f, line1);
  // draw_trian_urself_lt(f, trian1);
  // draw_rect_urself_lt(f, rect1);
  // draw_ell_urself_lt(f, ellip1);
  // draw_diam_urself_lt(f, diam1);

  move_all_illustration_urself(f, line1, rect1, trian1, circle1, ellip1, diam1);

  delay(DELAY_LONG);
  closegraph();
  return 0;
}