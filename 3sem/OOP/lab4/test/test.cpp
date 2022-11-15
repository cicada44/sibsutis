#include <graphics.h>
#include <iostream>
#include <math.h>

struct MyPoint {
  float x, y;
} O, A;

float R = 100;

/*Функция поворота отрезка*/
void rotate(float x1, float y1, float &x2, float &y2, float angle) {
  float dx = x2; //Запоминаем для вычислений
  float dy = y2; //Запоминаем для вычислений

  x2 = x1 + (dx - x1) * cos(angle * M_PI / 180) -
       (dy - y1) * sin(angle * M_PI / 180); //Получили первую координату
  y2 = y1 + (dx - x1) * sin(angle * M_PI / 180) +
       (dy - y1) * cos(angle * M_PI / 180); //Получили вторую координату
  line(x1, y1, x2, y2);                     //Стрелка
}

/*ФУНКЦИЯ ВВОДА ПАРАМЕТРОВ*/
void input() {
  O.x = getmaxx() / 2;
  O.y = getmaxy() / 2;
  A.x = O.x + R * cos(90);
  A.y = O.y + R * sin(90);
  line(O.x, O.y, A.x, A.y); //Начальное положение стрелки

  setcolor(3);
}

int main() {
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "qqq");

  input(); //Ввод параметров

  for (int i = 0; i < 2000; i++) {
    cleardevice();                 //Очистка экрана
    rotate(O.x, O.y, A.x, A.y, 1); //Поворот отрезка
    std::cout << "LINE x - " << A.x << " y - " << A.y << std::endl;
    usleep(100000); //Задержка одна секунда
  }
  closegraph();
  return 0;
}