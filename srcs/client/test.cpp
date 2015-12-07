#include <iostream>
#include <SFML/Graphics.hpp>
#include "Time.hpp"
#include "Animation.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

  RType::Animation nyan(std::string("../../ressources/sprites/NyanCat bonnus.run.53x21x5.png"), 5, 200, RType::Time::getTimeStamp());
  RType::Animation mob(std::string("../../ressources/sprites/red ship.fly.33x36x8.png"), 8, 100, RType::Time::getTimeStamp());

  nyan.scale(3, 3);
  mob.scale(3, 3);
  mob.setPosition(0, 60);
  window.setTitle("R-type");
  window.setVerticalSyncEnabled(true);
  int i = 0;
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      window.clear();
      window.draw(nyan.getFrame());
      window.draw(mob.getFrame());
      window.display();
    }

  return 0;
}
