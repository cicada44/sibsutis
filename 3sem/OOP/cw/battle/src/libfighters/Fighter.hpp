#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include "../../src/libfighters/Hp.hpp"
#include <SFML/Graphics.hpp>

class Fighter_ghost {
public:
  virtual size_t get_hp() = 0;
};

// default fighter
class Fighter : protected Fighter_ghost {
public:
  Fighter() = default;
  Fighter(sf::Color);
  Fighter(int x, int y, sf::Color c, int side);

  int get_x();
  int get_y();

  void draw(sf::RenderWindow &);
  void move_x(int side);
  void move_y(int side);
  virtual void shoot(sf::RenderWindow &window, Fighter &f2,
                     sf::RectangleShape &floor);
  sf::RectangleShape &get_hp_scale();
  void set_color(sf::Color clr);
  Hp &get_hp_obj();
  virtual size_t get_hp();
  int get_speed();
  void reset();

protected:
  sf::RectangleShape left_leg;
  sf::RectangleShape right_leg;
  sf::RectangleShape left_hand;
  sf::RectangleShape right_hand;
  sf::RectangleShape body;
  sf::CircleShape head;
  sf::Color clr;
  Hp hp;

private:
  const int speed = 15;
  const int damage = 30;
  const int hp_cnt = 300;
};

// f2
class Fighter_damaged : public Fighter {
public:
  Fighter_damaged() = default;
  Fighter_damaged(int x, int y, sf::Color c, int side);

  void shoot(sf::RenderWindow &window, Fighter &f2, sf::RectangleShape &floor);

  size_t get_hp();

protected:
  sf::Color clr;

private:
  const int speed = 10;
  const int damage = 75;
  const int hp_cnt = 150;
};

// f3
class Fighter_hp : public Fighter {
public:
  Fighter_hp() = default;
  Fighter_hp(int x, int y, sf::Color c, int side);

  void shoot(sf::RenderWindow &window, Fighter &f2, sf::RectangleShape &floor);

  size_t get_hp();

protected:
  sf::Color clr;

private:
  const int speed = 25;
  const int damage = 20;
  const int hp_cnt = 600;
};

#endif // __FIGHTER_H__