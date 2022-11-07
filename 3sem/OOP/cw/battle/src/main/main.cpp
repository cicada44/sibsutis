#include "../libfighters/Fighter.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

#define SHORT_DELAY 10

using std::cin;
using std::cout;

int main() {
  Fighter f1(sf::Color::Black);
  Fighter f2(sf::Color::White);

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

  sf::RenderWindow window(sf::VideoMode(1200, 675), "Fighter");

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor */
    window.draw(floor);

    // window.draw(background);
    f1.draw(window);

    // f1.move_x(1);
    // f1.move_y(1);
    // f1.draw(window);
    // sf::sleep(sf::milliseconds(SHORT_DELAY));

    window.display();
  }

  return 0;
}