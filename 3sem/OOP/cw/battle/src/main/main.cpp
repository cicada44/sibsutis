#include "../libfighters/Fighter.hpp"
#include "../libfighters/Hp.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define SHORT_DELAY 10
#define LONG_DELAY 100
#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 675

using std::cin;
using std::cout;

void gameover_display(sf::RenderWindow &window, int t);
void fight_1();
void fight_2();
void fight_3();
void quote();

void quote() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                          "Fighter");
  window.clear(sf::Color::White);
  sf::Font font;
  font.loadFromFile("quote.TTF");
  sf::Text text;
  text.setString("no matter how you hit");
  text.setFont(font);
  text.setPosition(450, WINDOW_SIZE_Y / 3);
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::Black);
  window.draw(text);
  window.display();
  text.setString("the main thing is to keep hitting");
  text.setPosition(320, WINDOW_SIZE_Y / 2);
  text.setCharacterSize(40);
  sf::sleep(sf::milliseconds(1700));
  window.draw(text);
  window.display();
  sf::sleep(sf::milliseconds(3000));
}

int main() {
  fight_1();
  fight_2();
  fight_3();

  quote();

  return 0;
}

void fight_1() {
  Fighter f_standart(800, 600, sf::Color::Black, 1);
  Fighter_hp f_hp(200, 600, sf::Color::Black, 0);

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
    }

    if (abs(f_standart.get_x() - f_hp.get_x()) < 40) {
      f_hp.shoot(window, f_standart, floor);
      sf::sleep(sf::microseconds(100));
      f_standart.shoot(window, f_hp, floor);
      sf::sleep(sf::microseconds(100));
    } else {
      f_standart.move_x(-1);
      f_hp.move_x(1);
    }

    /* gameover */
    if (static_cast<int>(f_standart.get_hp()) == 0) {
      gameover_display(window, 1);
      window.close();
    }
    if (static_cast<int>(f_hp.get_hp()) == 0) {
      gameover_display(window, 0);
      window.close();
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor & hp*/
    window.draw(floor);
    window.draw(f_standart.get_hp_scale());
    window.draw(f_hp.get_hp_scale());

    f_standart.draw(window);
    f_hp.draw(window);

    window.display();

    sf::sleep(sf::milliseconds(LONG_DELAY));
  }
}

void fight_2() {
  Fighter_hp f_hp(800, 600, sf::Color::Black, 1);
  Fighter_damaged f_dmg(200, 600, sf::Color::Black, 0);

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
    }

    if (abs(f_hp.get_x() - f_dmg.get_x()) < 40) {
      f_hp.shoot(window, f_dmg, floor);
      sf::sleep(sf::microseconds(100));
      f_dmg.shoot(window, f_hp, floor);
      sf::sleep(sf::microseconds(100));
    } else {
      f_hp.move_x(-1);
      f_dmg.move_x(1);
    }

    /* gameover */
    if (static_cast<int>(f_hp.get_hp()) <= 0) {
      gameover_display(window, 0);
      window.close();
    }
    if (static_cast<int>(f_dmg.get_hp()) <= 0) {
      gameover_display(window, 1);
      window.close();
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor & hp*/
    window.draw(floor);
    window.draw(f_dmg.get_hp_scale());
    window.draw(f_hp.get_hp_scale());

    f_dmg.draw(window);
    f_hp.draw(window);

    window.display();

    sf::sleep(sf::milliseconds(LONG_DELAY));
  }
}

void fight_3() {
  Fighter f_standart(800, 600, sf::Color::Black, 1);
  Fighter_hp f_dmg(200, 600, sf::Color::Black, 0);

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
    }

    if (abs(f_standart.get_x() - f_dmg.get_x()) < 40) {
      f_standart.shoot(window, f_dmg, floor);
      sf::sleep(sf::microseconds(100));
      f_dmg.shoot(window, f_standart, floor);
      sf::sleep(sf::microseconds(100));
    } else {
      f_standart.move_x(-1);
      f_dmg.move_x(1);
    }

    /* gameover */
    if (static_cast<int>(f_standart.get_hp()) == 0) {
      gameover_display(window, 1);
      window.close();
    }
    if (static_cast<int>(f_dmg.get_hp()) == 0) {
      gameover_display(window, 0);
      window.close();
    }

    /* clear window */
    window.clear(sf::Color::White);

    /* draw floor & hp*/
    window.draw(floor);
    window.draw(f_standart.get_hp_scale());
    window.draw(f_dmg.get_hp_scale());

    f_standart.draw(window);
    f_dmg.draw(window);

    window.display();

    sf::sleep(sf::milliseconds(LONG_DELAY));
  }
}
