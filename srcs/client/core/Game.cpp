#include "Game.hpp"

#include "UnitFactory.hpp"
#include "MonsterTest.hpp"

Game::Game(IGameHandler * client, sf::RenderWindow & window, Unit::Player & player)
  : _client(client),_window(window), _tick(Time::getTimeStamp()), _localPlayer(player),
    _map({{_localPlayer.getID(), &_localPlayer}}), _finish(false), _creationTime(Time::getTimeStamp()),
    /*_input({
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
      })*/

      _input({
      {{sf::Keyboard::Escape, Key::PRESS}, [] (Time::stamp tick, Key::keyState & keys, Game * param)
	{
	  param->setFinish();
	}},
	{{sf::Keyboard::Up, Key::PRESS}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Up, Key::PRESS); }},
	{{sf::Keyboard::Up, Key::RELEASE}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Up, Key::RELEASE); }},
	{{sf::Keyboard::Down, Key::PRESS}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Down, Key::PRESS); }},
	{{sf::Keyboard::Down, Key::RELEASE}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Down, Key::RELEASE); }},
	{{sf::Keyboard::Right, Key::PRESS}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Right, Key::PRESS); }},
	{{sf::Keyboard::Right, Key::RELEASE}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Right, Key::RELEASE); }},
	{{sf::Keyboard::Left, Key::PRESS}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Left, Key::PRESS); }},
	{{sf::Keyboard::Left, Key::RELEASE}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Left, Key::RELEASE); }},
	{{sf::Keyboard::Space, Key::PRESS}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Space, Key::PRESS); }},
	{{sf::Keyboard::Space, Key::RELEASE}, [] (Time::stamp, Key::keyState & keys, Game * param)
	    { Game::sendKey(param, keys, sf::Keyboard::Space, Key::RELEASE); }},
    	})
{
  client->setGame(this);
  connectUnit(Unit::MONSTERTEST, 100, 100, 5u, Time::stamp(0), 2);
}

Game::~Game()
{
  _client->setGame(NULL);
}

void			Game::sendKey(Game * param, Key::keyState & key,
				      sf::Keyboard::Key keycode, Key::event e)
{
  static std::map<std::pair<sf::Keyboard::Key, Key::event>,
		 ClientKeyboardPressPacket::keyEvent>	netAssoc =
    {
      {{sf::Keyboard::Up, Key::PRESS}, ClientKeyboardPressPacket::UpPress},
      {{sf::Keyboard::Up, Key::RELEASE}, ClientKeyboardPressPacket::UpRealease},
      {{sf::Keyboard::Down, Key::PRESS}, ClientKeyboardPressPacket::DownPress},
      {{sf::Keyboard::Down, Key::RELEASE}, ClientKeyboardPressPacket::DownRealease},
      {{sf::Keyboard::Right, Key::PRESS}, ClientKeyboardPressPacket::RightPress},
      {{sf::Keyboard::Right, Key::RELEASE}, ClientKeyboardPressPacket::RightRealease},
      {{sf::Keyboard::Left, Key::PRESS}, ClientKeyboardPressPacket::LeftPress},
      {{sf::Keyboard::Left, Key::RELEASE}, ClientKeyboardPressPacket::LeftRealease},
      {{sf::Keyboard::Space, Key::PRESS}, ClientKeyboardPressPacket::SpacePress},
      {{sf::Keyboard::Space, Key::RELEASE}, ClientKeyboardPressPacket::SpaceRelease},
    };

  param->_client->sendKey(netAssoc[std::pair<sf::Keyboard::Key, Key::event>(keycode, e)]);
  key[keycode] = Key::UNKNOWN;
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

void			Game::setTimer(unsigned long time)
{
  _creationTime = Time::getTimeStamp() - time;
}

void			Game::connectUnit(Unit::type type, int x, int y, unsigned int id,
					  Time::stamp creationTime, int param)
{
  Unit::AUnit *	unit = Unit::Factory::getInstance()->createUnit(type, x, y, id, creationTime, float(param) / 1000);

  _map[unit->getID()] = unit;
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
