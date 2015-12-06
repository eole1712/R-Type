#include <ctime>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  
  Animation nyan(std::string("../../ressources/sprites/NyanCat bonnus.run.53x21x5.png"), 5, 4, std::time(NULL));
  Animation mob(std::string("../../ressources/sprites/red ship.fly.33x36x8.png"), 8, 4, std::time(NULL));

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
