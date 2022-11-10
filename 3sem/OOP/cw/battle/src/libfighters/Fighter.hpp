#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include <SFML/Graphics.hpp>

// default fighter

class Fighter {

public:
  Fighter() = default;
  Fighter(sf::Color);
  Fighter(int x, int y, sf::Color c);

  int get_x();
  int get_y();

  void draw(sf::RenderWindow &);
  void move_x(int speed);
  void move_y(int speed);
  void shoot(sf::RenderWindow &window, Fighter &f2, sf::RectangleShape &floor);
  void set_color(sf::Color clr);
  void reset();

private:
  sf::RectangleShape left_leg;
  sf::RectangleShape right_leg;
  sf::RectangleShape left_hand;
  sf::RectangleShape right_hand;
  sf::RectangleShape body;
  sf::CircleShape head;
  sf::Color clr;
};

#endif // __FIGHTER_H__