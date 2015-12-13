#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
  Game	bra("", Unit::RED, "");
  sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");

  window.setTitle("R-type");
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);

 Time::stamp	tick = Time::getTimeStamp();
  int i = 0;

  while (window.isOpen())
    {
      bra.pollEvent(window, tick);
      tick = Time::getTimeStamp();
      window.clear();
      bra.render(window);
      window.display();
    }

  return 0;
}
