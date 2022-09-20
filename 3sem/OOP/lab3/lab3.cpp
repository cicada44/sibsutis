#include "tPointN.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

int main() {

  sf::RenderWindow window(sf::VideoMode(640, 480), "Moving");

  tPoint t;

  t.set_shape_rad(3);
  t.set_color(100, 200, 300);

  window.draw(t.get_shape());
  window.display();

  //   sf::CircleShape shape(200);
  //
  //   while (window.isOpen()) {
  // sf::Event event;
  // while (window.pollEvent(event))
  //   if (event.type == sf::Event::Closed)
  // window.close();
  //
  // window.clear();
  // window.draw(shape);
  // window.display();
  //   }
  //
  usleep(10000000);

  return 0;
}