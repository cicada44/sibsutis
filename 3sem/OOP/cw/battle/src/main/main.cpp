#include "../libfighters/Fighter.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

#define SHORT_DELAY 10
#define LONG_DELAY 100
#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 675

using std::cin;
using std::cout;

int main() {
  Fighter f1(sf::Color::Black);
  Fighter f2(sf::Color::Cyan);

  /* floor */
  sf::Color floor_clr;
  floor_clr.r = 105;
  floor_clr.g = 105;
  floor_clr.b = 105;
  sf::RectangleShape floor;
  floor.setSize(sf::Vector2f(1200, 190));
  floor.setPosition(sf::Vector2f(0, 485));
  floor.setFillColor(floor_clr);

  /* background texture */
  sf::Texture texture;
  if (!texture.loadFromFile(
          "/home/cicada44/cicada-main/sibsutis/3sem/OOP/cw/battle/"
          "images/fr2.jpg")) {
  }
  sf::Sprite background(texture);

  sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                          "Fighter");

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A && 0 < f1.get_x())
          f1.move_x(-10);
        if (event.key.code == sf::Keyboard::D && f1.get_x() < 1200)
          f1.move_x(10);
        if (event.key.code == sf::Keyboard::W && 485 < f1.get_y() + 30)
          f1.move_y(-10);
        if (event.key.code == sf::Keyboard::S && f1.get_y() + 30 < 675)
          f1.move_y(10);
        if (event.key.code == sf::Keyboard::E) {
          f1.shoot();
          window.clear(sf::Color::White);
          window.draw(floor);
          f1.draw(window);
          f2.draw(window);
          window.display();
          f1.reset();
          sf::sleep(sf::milliseconds(LONG_DELAY));
        }
        if (event.key.code == sf::Keyboard::Left && 0 < f2.get_x())
          f2.move_x(-10);
        if (event.key.code == sf::Keyboard::Right && f2.get_x() < 1200)
          f2.move_x(10);
        if (event.key.code == sf::Keyboard::Up && 485 < f2.get_y() + 30)
          f2.move_y(-10);
        if (event.key.code == sf::Keyboard::Down && f2.get_y() + 30 < 675)
          f2.move_y(10);
        if (event.key.code == sf::Keyboard::RControl) {
          f2.shoot();
          window.clear(sf::Color::White);
          window.draw(floor);
          f2.draw(window);
          f1.draw(window);
          window.display();
          f2.reset();
          sf::sleep(sf::milliseconds(LONG_DELAY));
        }
      }
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor */
    window.draw(floor);

    f1.draw(window);
    f2.draw(window);

    window.display();
  }

  return 0;
}