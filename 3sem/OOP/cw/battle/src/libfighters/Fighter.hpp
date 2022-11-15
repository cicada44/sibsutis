#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include "../../src/libfighters/Hp.hpp"
#include <SFML/Graphics.hpp>

// default fighter

class Fighter {

public:
  Fighter() = default;
  Fighter(sf::Color);
  Fighter(int x, int y, sf::Color c, int side);

  int get_x();
  int get_y();

  void draw(sf::RenderWindow &);
  void move_x(int speed);
  void move_y(int speed);
  void shoot(sf::RenderWindow &window, Fighter &f2, sf::RectangleShape &floor);
  sf::RectangleShape &get_hp_scale();
  void set_color(sf::Color clr);
  Hp &get_hp_obj();
  size_t get_hp();
  void reset();

private:
  sf::RectangleShape left_leg;
  sf::RectangleShape right_leg;
  sf::RectangleShape left_hand;
  sf::RectangleShape right_hand;
  sf::RectangleShape body;
  sf::CircleShape head;
  sf::Color clr;
  Hp hp;
};

#endif // __FIGHTER_H__