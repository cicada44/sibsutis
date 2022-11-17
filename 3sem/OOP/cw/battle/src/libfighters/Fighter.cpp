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

Hp &Fighter::get_hp_obj() { return hp; }

sf::RectangleShape &Fighter::get_hp_scale() { return hp.get_hp_scale(); }

int Fighter::get_x() { return static_cast<int>(body.getPosition().x); }
int Fighter::get_y() { return static_cast<int>(body.getPosition().y); }
int Fighter::get_speed() { return speed; }

size_t Fighter::get_hp() { return hp.get_hp(); }

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

Fighter::Fighter(int x, int y, sf::Color c, int side) : clr(c) {
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

  hp.set_hp_count(hp_cnt);

  if (!side) {
    hp.create(0);
  } else {
    hp.create(1);
  }
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

void Fighter::move_x(int side) {
  left_leg.setPosition(left_leg.getPosition().x + speed * side,
                       left_leg.getPosition().y);
  right_leg.setPosition(right_leg.getPosition().x + speed * side,
                        right_leg.getPosition().y);
  left_hand.setPosition(left_hand.getPosition().x + speed * side,
                        left_hand.getPosition().y);
  right_hand.setPosition(right_hand.getPosition().x + speed * side,
                         right_hand.getPosition().y);
  body.setPosition(body.getPosition().x + speed * side, body.getPosition().y);
  head.setPosition(head.getPosition().x + speed * side, head.getPosition().y);
}

void Fighter::move_y(int side) {
  left_leg.setPosition(left_leg.getPosition().x,
                       left_leg.getPosition().y + speed * side);
  right_leg.setPosition(right_leg.getPosition().x,
                        right_leg.getPosition().y + speed * side);
  left_hand.setPosition(left_hand.getPosition().x,
                        left_hand.getPosition().y + speed * side);
  right_hand.setPosition(right_hand.getPosition().x,
                         right_hand.getPosition().y + speed * side);
  body.setPosition(body.getPosition().x, body.getPosition().y + speed * side);
  head.setPosition(head.getPosition().x, head.getPosition().y + speed * side);
}

void Fighter::shoot(sf::RenderWindow &window, Fighter &f2,
                    sf::RectangleShape &floor) {
  window.clear(sf::Color::White);

  draw_all_scales(window, this->hp, f2.get_hp_obj(), floor);

  right_hand.setRotation(30);

  this->draw(window);
  f2.draw(window);

  if (abs(get_x() - f2.get_x()) < 40) {
    f2.get_hp_obj().decr_hp(damage);

    sf::Color tclr = clr;
    f2.set_color(sf::Color::Red);
    f2.draw(window);
    window.display();

    sf::sleep(sf::milliseconds(100));
    f2.set_color(tclr);

    this->reset();
    this->draw(window);
    f2.draw(window);
    draw_all_scales(window, hp, f2.get_hp_obj(), floor);

    window.display();

    return;
  }

  window.display();

  sf::sleep(sf::milliseconds(100));
  this->reset();

  window.display();

  sf::sleep(sf::milliseconds(LONG_DELAY));
}

void Fighter::reset() { right_hand.setRotation(120); }

/* f2 */
Fighter_damaged::Fighter_damaged(int x, int y, sf::Color c, int side) : clr(c) {
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

  hp.set_hp_count(hp_cnt);

  if (!side) {
    hp.create(0);
  } else {
    hp.create(1);
  }
}

void Fighter_damaged::shoot(sf::RenderWindow &window, Fighter &f2,
                            sf::RectangleShape &floor) {
  window.clear(sf::Color::White);

  draw_all_scales(window, this->hp, f2.get_hp_obj(), floor);

  right_hand.setRotation(30);

  this->draw(window);
  f2.draw(window);

  if (abs(get_x() - f2.get_x()) < 40) {
    f2.get_hp_obj().decr_hp(damage);

    sf::Color tclr = clr;
    f2.set_color(sf::Color::Red);
    f2.draw(window);
    window.display();

    sf::sleep(sf::milliseconds(100));
    f2.set_color(tclr);

    this->reset();
    this->draw(window);
    f2.draw(window);
    draw_all_scales(window, hp, f2.get_hp_obj(), floor);

    window.display();

    return;
  }

  window.display();

  sf::sleep(sf::milliseconds(100));
  this->reset();

  window.display();

  sf::sleep(sf::milliseconds(LONG_DELAY));
}

size_t Fighter_damaged::get_hp() { return hp.get_hp(); }

/* f3 */
Fighter_hp::Fighter_hp(int x, int y, sf::Color c, int side) : clr(c) {
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

  hp.set_hp_count(hp_cnt);

  if (!side) {
    hp.create(0);
  } else {
    hp.create(1);
  }
}

void Fighter_hp::shoot(sf::RenderWindow &window, Fighter &f2,
                       sf::RectangleShape &floor) {
  window.clear(sf::Color::White);

  draw_all_scales(window, this->hp, f2.get_hp_obj(), floor);

  right_hand.setRotation(30);

  this->draw(window);
  f2.draw(window);

  if (abs(get_x() - f2.get_x()) < 40) {
    f2.get_hp_obj().decr_hp(damage);

    sf::Color tclr = clr;
    f2.set_color(sf::Color::Red);
    f2.draw(window);
    window.display();

    sf::sleep(sf::milliseconds(100));
    f2.set_color(tclr);

    this->reset();
    this->draw(window);
    f2.draw(window);
    draw_all_scales(window, hp, f2.get_hp_obj(), floor);

    window.display();

    return;
  }

  window.display();

  sf::sleep(sf::milliseconds(100));
  this->reset();

  window.display();

  sf::sleep(sf::milliseconds(LONG_DELAY));
}

size_t Fighter_hp::get_hp() { return hp.get_hp(); }
