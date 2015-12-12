#include <iostream>
#include <SFML/Graphics.hpp>
#include "KeyBind.hpp"
#include "Time.hpp"
#include "Animation.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");

  Animation mob(std::string("../../ressources/sprites/NyanCat bonnus.run.53x21x5.png"), 5, 200, Time::getTimeStamp());
  Animation nyan(std::string("../../ressources/sprites/red ship2.fly.33x36x8.png"), 8, 100, Time::getTimeStamp());

  KeyBind<sf::Keyboard::Key, Animation *>	myInput({
      {sf::Keyboard::Up, [] (Time::stamp tick, KeyBind<sf::Keyboard::Key, Animation *>::keyState keys, Animation * param)
	  { param->setPosition(param->getPosition().x, param->getPosition().y - tick / 2); }},
      {sf::Keyboard::Down, [](Time::stamp tick, KeyBind<sf::Keyboard::Key, Animation *>::keyState keys, Animation * param)
	  { param->setPosition(param->getPosition().x, param->getPosition().y + tick / 2);  }},
      {sf::Keyboard::Right,[](Time::stamp tick, KeyBind<sf::Keyboard::Key, Animation *>::keyState keys, Animation * param)
	  { param->setPosition(param->getPosition().x + tick / 2, param->getPosition().y);  }},
      {sf::Keyboard::Left, [](Time::stamp tick, KeyBind<sf::Keyboard::Key, Animation *>::keyState keys, Animation * param)
	  { param->setPosition(param->getPosition().x - tick / 2, param->getPosition().y);  }},
  });

  nyan.scale(3, 3);
  mob.setPosition(0, 60);
  window.setTitle("R-type");
  window.setVerticalSyncEnabled(true);
  Time::stamp	tick = Time::getTimeStamp();
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
      tick = Time::getTimeStamp();
      window.clear();
      window.draw(mob.getFrame());
      window.draw(nyan.getFrame());
      window.display();
    }

  return 0;
}
