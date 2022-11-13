#include "../libfighters/Fighter.hpp"
#include "../libfighters/Hp.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

#define SHORT_DELAY 10
#define LONG_DELAY 100
#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 675

using std::cin;
using std::cout;

void gameover_display(sf::RenderWindow &window);

int main() {

  sf::Font font_fot_go;
  font_fot_go.loadFromFile("../images/go.ttf");
  // Fighter f1(sf::Color::Black);
  // Fighter f2(sf::Color::Cyan);

  Fighter f1(800, 600, sf::Color::Blue);
  Fighter f2(200, 600, sf::Color::Blue);

  /* floor */
  sf::Color floor_clr;
  floor_clr.r = 105;
  floor_clr.g = 105;
  floor_clr.b = 105;
  sf::RectangleShape floor;
  floor.setSize(sf::Vector2f(1200, 190));
  floor.setPosition(sf::Vector2f(0, 485));
  floor.setFillColor(floor_clr);

  /* hp of fighters */
  Hp hp_left, hp_right;
  hp_left.create(0);
  hp_right.create(1);

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
          f1.move_x(-20);
        if (event.key.code == sf::Keyboard::D && f1.get_x() < 1200)
          f1.move_x(20);
        if (event.key.code == sf::Keyboard::W && 485 < f1.get_y() + 30)
          f1.move_y(-20);
        if (event.key.code == sf::Keyboard::S && f1.get_y() + 30 < 675)
          f1.move_y(20);
        if (event.key.code == sf::Keyboard::E) {
          f1.shoot(window, f2, floor, hp_right);
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
          f2.shoot(window, f1, floor, hp_left);
        }
      }
    }

    // cout << "hpleft - " << hp_left.get_hp() << '\n';
    if (static_cast<int>(hp_right.get_hp()) == 0) {
      gameover_display(window);
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor & hp*/
    window.draw(floor);
    window.draw(hp_left.get_hp_scale());
    window.draw(hp_right.get_hp_scale());

    f1.draw(window);
    f2.draw(window);

    window.display();
  }

  return 0;
}

void gameover_display(sf::RenderWindow &window) {
  // cout << "hpleft - " << hp_left.get_hp() << '\n';
  sf::Font font;
  if (!font.loadFromFile("../../images/arial.ttf")) {
    cout << "can't load font" << '\n';
  }
  sf::Text text("Score = 0", font);
  text.setCharacterSize(100);
  text.setFillColor(sf::Color::White);
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Green);
  window.draw(text);
  window.display();
  sf::sleep(sf::milliseconds(10000));
}
