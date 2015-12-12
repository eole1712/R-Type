#include <iostream>
#include <SFML/Graphics.hpp>
#include "KeyBind.hpp"
#include "Time.hpp"
#include "Animation.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");

  RType::Animation nyan(std::string("../../ressources/sprites/NyanCat bonnus.run.53x21x5.png"), 5, 200, RType::Time::getTimeStamp());
  RType::Animation mob(std::string("../../ressources/sprites/red ship.fly.33x36x8.png"), 8, 100, RType::Time::getTimeStamp());

  RType::KeyBind<sf::Keyboard::Key, RType::Animation *>	myInput({
      {sf::Keyboard::Up, [] (RType::Time::stamp tick, RType::KeyBind<sf::Keyboard::Key, RType::Animation *>::keyState keys, RType::Animation * param)
	  { param->setPosition(param->getPosition().x, param->getPosition().y - tick); }},
      {sf::Keyboard::Down, [](RType::Time::stamp tick, RType::KeyBind<sf::Keyboard::Key, RType::Animation *>::keyState keys, RType::Animation * param)
	  { param->setPosition(param->getPosition().x, param->getPosition().y + tick);  }},
      {sf::Keyboard::Right,[](RType::Time::stamp tick, RType::KeyBind<sf::Keyboard::Key, RType::Animation *>::keyState keys, RType::Animation * param)
	  { param->setPosition(param->getPosition().x + tick, param->getPosition().y);  }},
      {sf::Keyboard::Left, [](RType::Time::stamp tick, RType::KeyBind<sf::Keyboard::Key, RType::Animation *>::keyState keys, RType::Animation * param)
	  { param->setPosition(param->getPosition().x - tick, param->getPosition().y);  }},
  });

  nyan.scale(3, 3);
  mob.scale(3, 3);
  mob.setPosition(0, 60);
  window.setTitle("R-type");
  window.setVerticalSyncEnabled(true);
  RType::Time::stamp	tick = RType::Time::getTimeStamp();
  int i = 0;
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();

	  if (event.type == sf::Event::KeyPressed ||
	      event.type == sf::Event::KeyReleased)
	    myInput[event.key.code] = (event.type == sf::Event::KeyPressed);
	  else if (event.type == sf::Event::TextEntered)
	    {
	      if (event.text.unicode < 128)
		std::cout << "typed: " << static_cast<char>(event.text.unicode) << std::endl;
	    }
        }
      myInput.process(tick, &nyan);
      tick = RType::Time::getTimeStamp();
      window.clear();
      window.draw(nyan.getFrame());
      window.draw(mob.getFrame());
      window.display();
    }

  return 0;
}
