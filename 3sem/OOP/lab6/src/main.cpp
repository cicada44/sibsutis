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

using std::cin;
using std::cout;

int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void draw_dot_lt(Field &f, tPoint &point) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    // point.move_once(point.get_x(), point.get_y(), point.get_vec_x(),
    //                 point.get_vec_y());
    f.draw_dot(point);
  }
}

/* LINE */

void draw_line_lt(Field &f, Line &line) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    line.move_once();
    f.draw_line(line);
  }
}

void draw_line_urself_lt(Field &f, Line &line) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    line.move_urself_once();
    f.draw_line(line);
  }
}

// void draw_line_lt_cp(Field &f, Line &line) {
// for (int x = 0; x < 4000; x++) {
// delay(DELAY_UMSHORT);
// cleardevice();
// line.move_once_line_cp();
// f.draw_line(line);
// }
// }

/* TRIANGLE */

void draw_trian_lt(Field &f, Triangle &trian) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    trian.move_once();
    f.draw_triangle(trian);
  }
}

void draw_trian_urself_lt(Field &f, Triangle &trian) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    trian.move_urself_once();
    f.draw_triangle(trian);
  }
}

// void draw_trian_lt_cp(Field &f, Triangle &trian) {
//   for (int x = 0; x < 4000; x++) {
//     delay(DELAY_UMSHORT);
//     cleardevice();
//     trian.move_once_trian_cp();
//     f.draw_triangle(trian);
//   }
// }

/* RECTANGLE */

void draw_rect_lt(Field &f, Rectangle &rect) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    rect.move_once();
    f.draw_rectangle(rect);
  }
}

void draw_rect_urself_lt(Field &f, Rectangle &rect) {
  for (int x = 0; x < 3500; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    rect.move_urself_once();
    f.draw_rectangle(rect);
  }
}

// void draw_rect_lt_cp(Field &f, Rectangle &rect) {
//   for (int x = 0; x < 4000; x++) {
//     delay(DELAY_UMSHORT);
//     cleardevice();
//     rect.move_once_rectangle_cp();
//     f.draw_rectangle(rect);
//   }
// }

/* CIRCLE */

void draw_circ_lt(Field &f, Circle &circ) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    circ.move_once();
    f.draw_circle(circ);
  }
}

// void draw_circ_lt_cp(Field &f, Circle &circ) {
//   for (int x = 0; x < 4000; x++) {
//     delay(DELAY_UMSHORT);
//     cleardevice();
//     circ.move_once_circle_cp();
//     f.draw_circle(circ);
//   }
// }

/* DIAMOND */

void draw_diam_lt(Field &f, Diamond &diam) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    diam.move_once();
    f.draw_diamond(diam);
  }
}

void draw_diam_urself_lt(Field &f, Diamond &diam) {
  for (int x = 0; x < 3500; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    diam.move_urself_once();
    f.draw_diamond(diam);
  }
}

// void draw_diam_lt_cp(Field &f, Diamond &diam) {
//   for (int x = 0; x < 4000; x++) {
//     delay(DELAY_UMSHORT);
//     cleardevice();
//     diam.move_once_diamond_cp();
//     f.draw_diamond(diam);
//   }
// }

/* ELLIPSE */

void draw_ell_lt(Field &f, Ellipse &ell) {
  for (int x = 0; x < 4000; x++) {
    delay(DELAY_UMSHORT);
    cleardevice();
    ell.move_once();
    f.draw_ellipse(ell);
  }
}

void draw_ell_urself_lt(Field &f, Ellipse &ell) {
  for (int x = 0; x < 500; x++) {
    delay(DELAY_USHORT);
    cleardevice();
    ell.move_urself_once();
    f.draw_ellipse(ell);
  }
}

// void draw_ell_lt_cp(Field &f, Ellipse &ell) {
//   for (int x = 0; x < 4000; x++) {
//     delay(DELAY_UMSHORT);
//     cleardevice();
//     ell.move_once_ell_cp();
//     f.draw_ellipse(ell);
//   }
// }

void move_all_illustration(Field &f, Line &line, Rectangle &rect,
                           Triangle &trian, Circle &cir, Ellipse &ell,
                           Diamond &diam) {
  outtextxy(75, 75, "MOVEMENT");
  delay(2000);
  cleardevice();
  outtextxy(100, 325, "LINE MOVING");
  delay(2000);
  draw_line_lt(f, line);
  cleardevice();
  outtextxy(100, 325, "TRIANGLE MOVING");
  delay(2000);
  draw_trian_lt(f, trian);
  cleardevice();
  outtextxy(100, 325, "RECTANGLE MOVING");
  delay(2000);
  draw_rect_lt(f, rect);
  cleardevice();
  outtextxy(100, 325, "CIRCLE MOVING");
  delay(2000);
  draw_circ_lt(f, cir);
  cleardevice();
  outtextxy(100, 325, "DIAMOND MOVING");
  delay(2000);
  draw_diam_lt(f, diam);
  cleardevice();
  outtextxy(100, 325, "ELLIPSE MOVING");
  delay(2000);
  draw_ell_lt(f, ell);
  cleardevice();
}

void move_all_illustration_urself(Field &f, Line &line, Rectangle &rect,
                                  Triangle &trian, Circle &cir, Ellipse &ell,
                                  Diamond &diam) {
  outtextxy(75, 75, "MOVEMENT AT CIRCLE");
  delay(2000);
  cleardevice();
  outtextxy(100, 325, "LINE MOVING");
  delay(2000);
  draw_line_urself_lt(f, line);
  cleardevice();
  outtextxy(100, 325, "TRIANGLE MOVING");
  delay(2000);
  draw_trian_urself_lt(f, trian);
  cleardevice();
  outtextxy(100, 325, "RECTANGLE MOVING");
  delay(2000);
  draw_rect_urself_lt(f, rect);
  cleardevice();
  outtextxy(100, 325, "DIAMOND MOVING");
  delay(2000);
  draw_diam_urself_lt(f, diam);
  cleardevice();
}

// void move_all_illustration_cp(Field &f, Line &line, Rectangle &rect,
//                               Triangle &trian, Circle &cir, Ellipse &ell,
//                               Diamond &diam) {
//   outtextxy(75, 75, "MOVEMENT CENTER POUNSE");
//   delay(2000);
//   cleardevice();
//   outtextxy(100, 325, "LINE MOVING");
//   delay(2000);
//   draw_line_lt_cp(f, line);
//   cleardevice();
//   outtextxy(100, 325, "TRIANGLE MOVING");
//   delay(2000);
//   draw_trian_lt_cp(f, trian);
//   cleardevice();
//   outtextxy(100, 325, "RECTANGLE MOVING");
//   delay(2000);
//   draw_rect_lt_cp(f, rect);
//   cleardevice();
//   outtextxy(100, 325, "CIRCLE MOVING");
//   delay(2000);
//   draw_circ_lt_cp(f, cir);
//   cleardevice();
//   outtextxy(100, 325, "DIAMOND MOVING");
//   delay(2000);
//   draw_diam_lt_cp(f, diam);
//   cleardevice();
// }

int main() {
  Field f;
  f.init();

  float cent_x = getmaxx() / 2;
  float cent_y = getmaxy() / 2;

  tPoint *arr_shapes[7];
  arr_shapes[0] = new Line(cent_x, cent_y, cent_x + 70, cent_y + 70, 1, 1);
  arr_shapes[1] = new Triangle(cent_x, cent_y, cent_x + 70, cent_y, cent_x,
                               cent_y + 70, 1, 1);
  arr_shapes[2] =
      new Rectangle(cent_x, cent_y, cent_x + 100, cent_y, cent_x + 100,
                    cent_y + 70, cent_x, cent_y + 70, 1, 1);
  arr_shapes[3] = new Circle(cent_x, cent_y, cent_x + 50, cent_y, 1, 1);
  arr_shapes[4] = new Diamond(200, 200, 250, 300, 300, 200, 250, 100, 1, 1);
  arr_shapes[5] = new Ellipse(100, 300, 0, 360, 100, 50, 1, 1);

  cout << "LINE"
       << "  x - " << arr_shapes[0]->get_x() << "  y - "
       << arr_shapes[0]->get_y() << "\n";
  cout << "TRIANGLE"
       << "  x - " << arr_shapes[1]->get_x() << "  y - "
       << arr_shapes[1]->get_y() << "\n";
  cout << "RECTANGLE"
       << "  x - " << arr_shapes[2]->get_x() << "  y - "
       << arr_shapes[2]->get_y() << "\n";
  cout << "CIRCLE"
       << "  x - " << arr_shapes[3]->get_x() << "  y - "
       << arr_shapes[3]->get_y() << "\n";
  cout << "ELLIPSE"
       << "  x - " << arr_shapes[4]->get_x() << "  y - "
       << arr_shapes[4]->get_y() << "\n";
  cout << "DIAMOND"
       << "  x - " << arr_shapes[5]->get_x() << "  y - "
       << arr_shapes[5]->get_y() << "\n";

  Line line1(cent_x, cent_y, cent_x + 70, cent_y + 70, 1, 1);

  Triangle trian1(cent_x, cent_y, cent_x + 70, cent_y, cent_x, cent_y + 70, 1,
                  1);

  Rectangle rect1(cent_x, cent_y, cent_x + 100, cent_y, cent_x + 100,
                  cent_y + 70, cent_x, cent_y + 70, 1, 1);

  Circle circle1(cent_x, cent_y, cent_x + 50, cent_y, 1, 1);

  Ellipse ellip1(100, 300, 0, 360, 100, 50, 1, 1);

  Diamond diam1(200, 200, 250, 300, 300, 200, 250, 100, 1, 1);

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

  // move_all_illustration(f, line1, rect1, trian1, circle1, ellip1, diam1);

  // move_all_illustration_urself(f, line1, rect1, trian1, circle1, ellip1,
  // diam1);

  // move_all_illustration_cp(f, line1, rect1, trian1, circle1, ellip1, diam1);

  // delay(DELAY_LONG);
  closegraph();
  return 0;
}