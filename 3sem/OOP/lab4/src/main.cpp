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

void draw_line_lt(Field &f, Line &line) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    line.move_once();
    f.draw_line(line);
  }
}

void draw_trian_lt(Field &f, Triangle &trian) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    trian.move_once();
    f.draw_triangle(trian);
  }
}

void draw_rect_lt(Field &f, Rectangle &rect) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    rect.move_once();
    f.draw_rectangle(rect);
  }
}

void draw_circ_lt(Field &f, Circle &circ) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    circ.move_once();
    f.draw_circle(circ);
  }
}

void draw_diam_lt(Field &f, Diamond &diam) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    diam.move_once();
    f.draw_diamond(diam);
  }
}

void draw_ell_lt(Field &f, Ellipse &ell) {
  for (int x = 0; x < 5000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    ell.move_once();
    f.draw_ellipse(ell);
    printf("ELLIPSE\n x - %d, y - %d, x2 - %d, y2 - %d, x3 - %d, y3 - %d\n",
           ell.get_x(), ell.get_y(), ell.get_x2(), ell.get_y2(),
           ell.get_x_rad(), ell.get_y_rad());
  }
}

int main() {
  Field f;
  f.init();

  Line line1(100, 100);
  line1.set_x(10);
  line1.set_y(10);
  line1.set_x2(100);
  line1.set_y2(100);
  line1.set_color(5);
  line1.set_vec_x(1);
  line1.set_vec_y(1);

  Rectangle rect1(400, 200);
  rect1.set_x(30);
  rect1.set_y(30);
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
  trian1.set_x(400);
  trian1.set_y(400);
  trian1.set_x2(450);
  trian1.set_y2(450);
  trian1.set_x3(400);
  trian1.set_y3(450);
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
  diam1.set_x2(300);
  diam1.set_y2(400);
  diam1.set_x4(300);
  diam1.set_y4(0);
  diam1.set_vec_x(1);
  diam1.set_vec_y(1);

  // f.draw_circle(circle1);
  // f.draw_line(line1);
  // f.draw_rectangle(rect1);
  // f.draw_triangle(trian1);
  // f.draw_ellipse(ellip1);
  // f.draw_diamond(diam1);

  // draw_line_lt(f, line1);
  // draw_trian_lt(f, trian1);
  // draw_rect_lt(f, rect1);
  // draw_circ_lt(f, circle1);
  // draw_diam_lt(f, diam1);
  // draw_ell_lt(f, ellip1);

  // bar(left + 300, top, right + 300, bottom);
  // line(left - 10, top + 150, left + 410, top + 150);
  // ellipse(100, 100 + 200, 0, 360, 100, 50);
  // outtextxy(left + 100, top + 325, "C Graphics Program");

  delay(DELAY_LONG);
  closegraph();
  return 0;
}