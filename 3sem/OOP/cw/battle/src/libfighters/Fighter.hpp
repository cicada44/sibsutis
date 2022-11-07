#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include <SFML/Graphics.hpp>

// default fighter

class Fighter {
  //   friend void Window::draw_fighter(Fighter &f);

public:
  Fighter() = default;
  Fighter(sf::Color);

  void draw(sf::RenderWindow &);
  void move_x(int speed);
  void move_y(int speed);

private:
  sf::RectangleShape left_leg;
  sf::RectangleShape right_leg;
  sf::RectangleShape left_hand;
  sf::RectangleShape right_hand;
  sf::RectangleShape body;
  sf::CircleShape head;
};

#endif // __FIGHTER_H__