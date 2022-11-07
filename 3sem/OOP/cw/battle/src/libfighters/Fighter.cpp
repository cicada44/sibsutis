#include "Fighter.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#define LEN 40

using std::cin;
using std::cout;

int Fighter::get_x() { return body.getPosition().x; }

int Fighter::get_y() { return body.getPosition().y; }

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
}

void Fighter::draw(sf::RenderWindow &window) {
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

void Fighter::shoot() { right_hand.setRotation(30); }

void Fighter::reset() { right_hand.setRotation(120); }
