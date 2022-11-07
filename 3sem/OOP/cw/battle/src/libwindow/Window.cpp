#include "Window.hpp"
#include <SFML/Graphics.hpp>

Window::Window() { window.create(sf::VideoMode(800, 600), "Fighter"); }

Window::Window(unsigned sizex, unsigned sizey) {
  window.create(sf::VideoMode(sizex, sizey), "Fighter");
}

void Window::draw_fighter(Fighter &f) {

}