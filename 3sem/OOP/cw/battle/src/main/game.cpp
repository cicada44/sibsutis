#include "game.hpp"
#include "../libfighters/Fighter.hpp"
#include "../libfighters/Hp.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 675

void game() {
  Fighter f1(800, 600, sf::Color::Black, 1);
  // Fighter f2(200, 600, sf::Color::Blue, 1);
  Fighter_hp f2(200, 600, sf::Color::Black, 0);
  // Fighter_ghost f2 = new Fighter(200, 600, sf::Color::Black, 1);

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
          f1.move_x(-1);
        if (event.key.code == sf::Keyboard::D && f1.get_x() < 1200)
          f1.move_x(1);
        if (event.key.code == sf::Keyboard::W && 485 < f1.get_y() + 30)
          f1.move_y(-1);
        if (event.key.code == sf::Keyboard::S && f1.get_y() + 30 < 675)
          f1.move_y(1);
        if (event.key.code == sf::Keyboard::E) {
          f1.shoot(window, f2, floor);
        }
        if (event.key.code == sf::Keyboard::Left && 0 < f2.get_x())
          f2.move_x(-1);
        if (event.key.code == sf::Keyboard::Right && f2.get_x() < 1200)
          f2.move_x(1);
        if (event.key.code == sf::Keyboard::Up && 485 < f2.get_y() + 30)
          f2.move_y(-1);
        if (event.key.code == sf::Keyboard::Down && f2.get_y() + 30 < 675)
          f2.move_y(1);
        if (event.key.code == sf::Keyboard::RControl) {
          f2.shoot(window, f1, floor);
        }
      }
    }

    if (static_cast<int>(f1.get_hp()) == 0) {
      gameover_display(window, 0);
    }
    if (static_cast<int>(f2.get_hp()) == 0) {
      gameover_display(window, 1);
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor & hp*/
    window.draw(floor);
    window.draw(f1.get_hp_scale());
    window.draw(f2.get_hp_scale());

    f1.draw(window);
    f2.draw(window);

    window.display();
  }
}

void gameover_display(sf::RenderWindow &window, int t) {
  window.clear(sf::Color::Red);
  sf::Font font;
  font.loadFromFile("go2.TTF");
  sf::Text text;
  if (t == 0)
    text.setString("PLAYER 1 WON");
  else if (t == 1)
    text.setString("PLAYER 2 WON");
  text.setFont(font);
  text.setPosition(450, WINDOW_SIZE_Y / 2);
  text.setCharacterSize(100);
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Green);
  window.draw(text);
  window.display();
  sf::sleep(sf::milliseconds(3000));
}
