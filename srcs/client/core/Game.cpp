#include "Game.hpp"

#include "UnitFactory.hpp"
#include "MonsterTest.hpp"

Game::Game(Client * client, sf::RenderWindow & window, Unit::Player & player)
  : _client(client),_window(window), _tick(Time::getTimeStamp()), _localPlayer(player),
    _map({{_localPlayer.getID(), &_localPlayer}}), _finish(false), _creationTime(Time::getTimeStamp()),
    _input({
      {{sf::Keyboard::Escape, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->setFinish(); }},
      {{sf::Keyboard::Up, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::UP, tick); }},
      {{sf::Keyboard::Down, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
       	{ param->getLocalPlayer()->move(Unit::DOWN, tick); }},
      {{sf::Keyboard::Right, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::RIGHT, tick); }},
      {{sf::Keyboard::Left, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->getLocalPlayer()->move(Unit::LEFT, tick); }},
      {{sf::Keyboard::Space, Key::PRESS}, [](Time::stamp, Key::keyState & keys, Game * param)
	{

	  keys[sf::Keyboard::Space] = Key::UNKNOWN;
	}},
      {{sf::Keyboard::Space, Key::PRESS}, [](Time::stamp, Key::keyState & keys, Game * param)
	{

	  keys[sf::Keyboard::Space] = Key::UNKNOWN;
	}}
      })/*
      _input({
      {{sf::Keyboard::Escape, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->setFinish(); }},
      {{sf::Keyboard::Up, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::UpPress); }},
      {{sf::Keyboard::Up, Key::RELEASE}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::UpRealease); }},
      {{sf::Keyboard::Down, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::DownPress); }},
      {{sf::Keyboard::Down, Key::RELEASE}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::DownRealease); }},
      {{sf::Keyboard::Right, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::RightPress); }},
      {{sf::Keyboard::Right, Key::RELEASE}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::RightRealease); }},
      {{sf::Keyboard::Left, Key::PRESS}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::LeftPress); }},
      {{sf::Keyboard::Left, Key::RELEASE}, [](Time::stamp tick, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::LeftRealease); }},
      {{sf::Keyboard::Space, Key::PRESS}, [](Time::stamp, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::SpacePress); }},
      {{sf::Keyboard::Space, Key::RELEASE}, [](Time::stamp, Key::keyState & keys, Game * param)
	{ param->_client->sendKey(ClientKeyboardPressPacket::SpaceRelease); }}
	})*/
{
  Unit::AUnit *test = Unit::Factory::getInstance()->createUnit(Unit::MONSTERTEST, 100, 100, 5, 0);

  connectUnit(*test);
}

Game::~Game()
{

}

bool			Game::getFinish() const
{
  return _finish;
}

void			Game::setFinish()
{
  _finish = true;
}

Unit::Player*		Game::getLocalPlayer()
{
  return &_localPlayer;
}

Unit::Player *		Game::getPlayer(unsigned int id)
{
  return dynamic_cast<Unit::Player *>(_map[id % 5]);
}

void			Game::loop()
{
  while (!_finish)
    {
      pollEvent();
      _tick = Time::getTimeStamp();
      _window.clear();
      render();
      _window.display();
    }
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

void			Game::pollEvent()
{
  sf::Event event;

  if (!_window.isOpen())
    {
      _finish = true;
      return ;
    }

  while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
	  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	_window.close();

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
  _input.process(_tick, this);
}

void			Game::render()
{
  Time::stamp		currentFrameTime = Time::getTimeStamp() - _creationTime;
  for (RemoteMap::iterator i = _map.begin(); i != _map.end(); i++)
    i->second->render(currentFrameTime, _window);
}

Unit::AUnit &		Game::operator[](unsigned int id)
{
  return *_map[id];
}
