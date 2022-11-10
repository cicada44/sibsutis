#include "Hp.hpp"

void Hp::create(bool side) {
  if (side) {
    hp_scale.setSize(sf::Vector2f(hp_count, 10));
    hp_scale.setFillColor(sf::Color::Green);
    hp_scale.setPosition(sf::Vector2f(0, 0));
    // hp_scale.rotate(90);
  } else {
    hp_scale.setSize(sf::Vector2f(hp_count, 10));
    hp_scale.setFillColor(sf::Color::Green);
    hp_scale.setPosition(sf::Vector2f(900, 0));
    // hp_scale.rotate(90);
  }
}

bool Hp::is_low_hp() { return (hp_count < 150) ? 1 : 0; }

sf::RectangleShape &Hp::get_hp_scale() { return hp_scale; }