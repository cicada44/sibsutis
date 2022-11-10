#ifndef __HP_H__
#define __HP_H__

#include <SFML/Graphics.hpp>

/* heatpoints of fighters */

class Hp {
public:
  Hp() = default;

  sf::RectangleShape &get_hp_scale();

  void create(bool side);
  bool is_low_hp();

private:
  sf::RectangleShape hp_scale;
  size_t hp_count = 300;
};

#endif // __HP_H__