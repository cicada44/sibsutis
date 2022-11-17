#ifndef __HP_H__
#define __HP_H__

#include <SFML/Graphics.hpp>

/* heatpoints of fighters */

class Hp {
public:
  Hp() = default;
  Hp(size_t hp) : hp_count(hp) {}

  sf::RectangleShape &get_hp_scale();

  void create(bool side);
  void set_hp_count(size_t hp);
  void decr_hp(size_t hp);
  size_t get_hp();
  bool is_low_hp();

private:
  sf::RectangleShape hp_scale;
  size_t hp_count;
};

void draw_all_scales(sf::RenderWindow &window, Hp &hp_sc1, Hp &hp_sc2,
                     sf::RectangleShape &floor);

#endif // __HP_H__