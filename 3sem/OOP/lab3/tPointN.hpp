#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class tPoint {
public:
  sf::CircleShape &get_shape() { return this->shape; }
  void set_shape_rad(float r) { this->shape.setRadius(r); }
  void set_color(int r, int g, int b) {
    RGB[0] = r;
    RGB[1] = g;
    RGB[2] = b;
    this->shape.setFillColor(sf::Color(r, g, b));
  }
  std::array<int, 3> &get_color_R() { return this->RGB; }

private:
  sf::CircleShape shape;
  std::array<int, 3> RGB;
};