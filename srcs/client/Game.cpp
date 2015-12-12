# include "Game.hpp"

Game::Game(std::string host, Unit::color color, std::string name)
  : _host(host), _localPlayer(color, name, 0), _map({{0, &_localPlayer}}),
    _input({
      {{sf::Keyboard::Up, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::UP, tick); }},
      {{sf::Keyboard::Down, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
       	{ param->getLocalPlayer()->move(Unit::DOWN, tick); }},
      {{sf::Keyboard::Right, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::RIGHT, tick); }},
      {{sf::Keyboard::Left, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::LEFT, tick); }},
      {{sf::Keyboard::Space, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{
	  param->getLocalPlayer()->shootLoad();
	  keys[sf::Keyboard::Space] = Key::UNKNOWN;
	}},
      {{sf::Keyboard::Space, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{
	  param->getLocalPlayer()->shootSend();
	  keys[sf::Keyboard::Space] = Key::UNKNOWN;
	}}
      })
{
}

Game::~Game()
{
}

Unit::Player*		Game::getLocalPlayer()
{
  return &_localPlayer;
}

void			Game::connectUnit(Unit::AUnit & unit)
{
  _map[unit.getID()] = &unit;
}

void			Game::disconnectUnit(unsigned int id)
{
  RemoteMap::iterator	i = _map.find(id);

  if (i != _map.end())
    _map.erase(i);
}

void			Game::pollEvent(sf::RenderWindow & window, Time::stamp tick)
{
  sf::Event event;

  while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
	  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	window.close();
      
      if (event.type == sf::Event::KeyPressed ||
	  event.type == sf::Event::KeyReleased)
	  _input[event.key.code] = (event.type == sf::Event::KeyPressed) ? Key::PRESS : Key::RELEASE;
      
      /*
      else if (event.type == sf::Event::TextEntered)
	{
	  if (event.text.unicode < 128)
	    std::cout << "typed: " << static_cast<char>(event.text.unicode) << std::endl;
	
       }*/
    }
  _input.process(tick, this);
}

void			Game::render(sf::RenderWindow & window)
{
  for (RemoteMap::iterator i = _map.begin(); i != _map.end(); i++)
    i->second->render(window);
}
