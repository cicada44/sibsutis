#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../libfighters/Fighter.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Window {
  sf::RenderWindow window;

public:
  Window();
  Window(unsigned, unsigned);

  void draw_fighter(Fighter &);

private:
};

#endif // __WINDOW_H__