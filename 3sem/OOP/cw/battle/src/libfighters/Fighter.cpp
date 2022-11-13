#include "Fighter.hpp"
#include "../libfighters/Hp.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define LEN 40
#define LONG_DELAY 140
#define DMG_STANDART 50

using std::cin;
using std::cout;

int Fighter::get_x() { return static_cast<int>(body.getPosition().x); }
int Fighter::get_y() { return static_cast<int>(body.getPosition().y); }

Fighter::Fighter(sf::Color clr) {
  left_leg.setSize(sf::Vector2f(LEN, 5));
  left_leg.setFillColor(clr);
  left_leg.setPosition(sf::Vector2f(200, 600));
  left_leg.rotate(60);

  right_leg.setSize(sf::Vector2f(LEN, 5));
  right_leg.setFillColor(clr);
  right_leg.setPosition(sf::Vector2f(200, 600));
  right_leg.rotate(120);

  body.setSize(sf::Vector2f(LEN, 5));
  body.setFillColor(clr);
  body.setPosition(sf::Vector2f(200, 600 - LEN));
  body.rotate(90);

  left_hand.setSize(sf::Vector2f(LEN, 5));
  left_hand.setFillColor(clr);
  left_hand.setPosition(sf::Vector2f(200, 600 - LEN));
  left_hand.rotate(60);

  right_hand.setSize(sf::Vector2f(LEN, 5));
  right_hand.setFillColor(clr);
  right_hand.setPosition(sf::Vector2f(200, 600 - LEN));
  right_hand.rotate(120);

  head.setRadius(20);
  head.setPosition(178, 600 - LEN - LEN);
  head.setFillColor(clr);

  this->clr = clr;
}

Fighter::Fighter(int x, int y, sf::Color c) {
  body.setSize(sf::Vector2f(LEN, 5));
  body.setFillColor(c);
  body.setPosition(sf::Vector2f(x, y - LEN));
  body.rotate(90);

  left_leg.setSize(sf::Vector2f(LEN, 5));
  left_leg.setFillColor(c);
  left_leg.setPosition(sf::Vector2f(x, y));
  left_leg.rotate(60);

  right_leg.setSize(sf::Vector2f(LEN, 5));
  right_leg.setFillColor(c);
  right_leg.setPosition(sf::Vector2f(x, y));
  right_leg.rotate(120);

  left_hand.setSize(sf::Vector2f(LEN, 5));
  left_hand.setFillColor(c);
  left_hand.setPosition(sf::Vector2f(x, y - LEN));
  left_hand.rotate(60);

  right_hand.setSize(sf::Vector2f(LEN, 5));
  right_hand.setFillColor(c);
  right_hand.setPosition(sf::Vector2f(x, y - LEN));
  right_hand.rotate(120);

  head.setRadius(20);
  head.setPosition(x - 22, y - LEN - LEN);
  head.setFillColor(clr);

  this->clr = c;
}

void Fighter::set_color(sf::Color c) { clr = c; }

void Fighter::draw(sf::RenderWindow &window) {
  left_hand.setFillColor(clr);
  left_leg.setFillColor(clr);
  right_hand.setFillColor(clr);
  right_leg.setFillColor(clr);
  body.setFillColor(clr);
  head.setFillColor(clr);
  window.draw(left_leg);
  window.draw(right_leg);
  window.draw(body);
  window.draw(left_hand);
  window.draw(right_hand);
  window.draw(head);
}

void Fighter::move_x(int speed) {
  left_leg.setPosition(left_leg.getPosition().x + speed,
                       left_leg.getPosition().y);
  right_leg.setPosition(right_leg.getPosition().x + speed,
                        right_leg.getPosition().y);
  left_hand.setPosition(left_hand.getPosition().x + speed,
                        left_hand.getPosition().y);
  right_hand.setPosition(right_hand.getPosition().x + speed,
                         right_hand.getPosition().y);
  body.setPosition(body.getPosition().x + speed, body.getPosition().y);
  head.setPosition(head.getPosition().x + speed, head.getPosition().y);
}

void Fighter::move_y(int speed) {
  left_leg.setPosition(left_leg.getPosition().x,
                       left_leg.getPosition().y + speed);
  right_leg.setPosition(right_leg.getPosition().x,
                        right_leg.getPosition().y + speed);
  left_hand.setPosition(left_hand.getPosition().x,
                        left_hand.getPosition().y + speed);
  right_hand.setPosition(right_hand.getPosition().x,
                         right_hand.getPosition().y + speed);
  body.setPosition(body.getPosition().x, body.getPosition().y + speed);
  head.setPosition(head.getPosition().x, head.getPosition().y + speed);
}

void Fighter::shoot(sf::RenderWindow &window, Fighter &f2,
                    sf::RectangleShape &floor, Hp &hp_sc2) {
  window.clear(sf::Color::White);
  draw_all_scales(window, hp, hp_sc2, floor);

  right_hand.setRotation(30);

  this->draw(window);
  f2.draw(window);

  if (abs(get_x() - f2.get_x()) < 40) {
    hp_sc2.decr_hp(DMG_STANDART);

    sf::Color tclr = sf::Color::Blue;
    f2.set_color(sf::Color::Red);
    f2.draw(window);
    window.display();

    sf::sleep(sf::milliseconds(100));
    f2.set_color(tclr);

    this->reset();
    this->draw(window);
    f2.draw(window);
    draw_all_scales(window, hp, hp_sc2, floor);

    window.display();

    return;
  }
  this->reset();
  window.display();
  sf::sleep(sf::milliseconds(LONG_DELAY));
}

void Fighter::reset() { right_hand.setRotation(120); }
