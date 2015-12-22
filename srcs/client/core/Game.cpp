#include "Game.hpp"

#include "UnitFactory.hpp"
#include "MonsterTest.hpp"

Game::Game(IGameHandler * client, sf::RenderWindow & window, int localPlayer, std::string name, unsigned long time)
  : _client(client),_window(window), _tick(Time::getTimeStamp()), _createStack(), _deleteStack(),
    _localPlayerName(name), _localPlayer(localPlayer),
    _map{}, _finish(false), _creationTime(Time::getTimeStamp() - time),
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
    {{sf::Keyboard::Escape, Key::PRESS}, [] (Time::stamp, Key::keyState &, Game * param)
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
      }), _background("../resources/textures/star.png", 1), _soundPlayer("../resources/sound/R-Type.ogg")
{
    client->setGame(this);
    _background.setState(Animation::PAUSE);
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
  return getPlayer(_localPlayer);
}

Unit::Player *		Game::getPlayer(unsigned int id)
{
  std::lock_guard<Lock> l(_lock);
  
  RemoteMap::iterator it = _map.find(id);
  if (it != _map.end())
    {
      return dynamic_cast<Unit::Player *>((*it).second);
    }
  return nullptr;
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
  deleteUnit();
  std::unique_lock<Lock>  l(_lock);
  for (RemoteMap::iterator i = _map.begin(); i != _map.end(); i++)
    {
      if (i->second->getType() == Unit::PLAYERTYPE)
	delete i->second;
      else
	Unit::Factory::getInstance()->deleteUnit(i->second);
    }
}

void			Game::setTimer(unsigned long time)
{
  std::lock_guard<Lock>   l(_lock);
  
  _creationTime = Time::getTimeStamp() - time;
}

Time::stamp     Game::getTimer()
{
  std::lock_guard<Lock> l(_lock);
  
  return _creationTime;
}

void			Game::createUnit()
{
  Unit::AUnit *		unit;
  unitCreateItem	newUnit;
  
  std::unique_lock<Lock>  l(_lock);
  for (std::list<unitCreateItem>::iterator i = _createStack.begin();
       i != _createStack.end(); i++)
    {
      newUnit = *i;
      if (std::get<0>(newUnit) == Unit::PLAYERTYPE)
        unit = new Unit::Player(std::get<1>(newUnit), std::get<2>(newUnit), std::get<3>(newUnit),
                                std::get<4>(newUnit), std::get<5>(newUnit), std::get<6>(newUnit));
      else
        unit = Unit::Factory::getInstance()->createUnit(std::get<0>(newUnit), std::get<1>(newUnit),
                                                        std::get<2>(newUnit), std::get<3>(newUnit),
                                                        std::get<4>(newUnit), std::get<6>(newUnit));
      _map[unit->getID()] = unit;
    }
  _createStack.clear();
  l.unlock();
  
}

void			Game::deleteUnit()
{
  std::unique_lock<Lock>  l(_lock);
  for (std::list<unitDeleteItem>::iterator i = _deleteStack.begin();
         i != _deleteStack.end(); i++)
    {
      if ((*i).second)
      	{
      	  Unit::pos	pos = (*i).first->move(Time::getTimeStamp() - _creationTime);
      	  explosion	item = 
	  {
	    new Animation("../resources/sprites/explosion.0.33x33x6.png", 6, 80, false),
	    new SoundPlayer("../resources/sound/explose.ogg", false, 30)
	  };

      	  item.anim->setPosition(pos.first, pos.second);
      	  _explosion.push_back(item);
      	}
      if (i->first->getType() == Unit::PLAYERTYPE)
	delete ((*i).first);
      else
	Unit::Factory::getInstance()->deleteUnit(i->first);
    }
  _deleteStack.clear();
  l.unlock();
}

void			Game::connectUnit(Unit::typeID type, int x, int y, unsigned int id,
                                  Time::stamp creationTime, int param)
{
  float		_param = float(param) / 1000;
  std::string		_name = std::string("");
  
  if (id == _localPlayer)
    _name = _localPlayerName;
  _createStack.push_back(std::make_tuple(type, x, y, id, creationTime, _name, _param));
}

void			Game::disconnectUnit(unsigned int id, bool explode)
{
  std::lock_guard<Lock>	l(_lock);
  RemoteMap::iterator	i = _map.find(id);
    
  if (i != _map.end())
    {
      _deleteStack.push_back(std::make_pair(i->second, explode));
      _map.erase(i);
    }
  else {
    for (std::list<unitCreateItem>::iterator it = _createStack.begin(); it != _createStack.end(); it++)
      {
	if (std::get<3>((*it)) == id)
	  {
	    _createStack.erase(it);
	    return;
	  }
      }
  }
}

void			Game::pollEvent()
{
  sf::Event event;
  
  if (!_window.isOpen())
    {
      _finish = true;
      return ;
    }
  for (std::list<explosion>::iterator i = _explosion.begin(); i != _explosion.end(); i++)
    {
      if ((*i).anim->finish())
	{
	  delete (*i).anim;
	  delete (*i).sound;
	  i = _explosion.erase(i);
	}
    }
  deleteUnit();
  createUnit();
  while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
	  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	_window.close();
      
      if (event.type == sf::Event::KeyPressed ||
	  event.type == sf::Event::KeyReleased)
	_input[event.key.code] = (event.type == sf::Event::KeyPressed) ? Key::PRESS : Key::RELEASE;
    }
  _input.process(_tick, this);
}

void			Game::render()
{
  static float		i = 0;
  Time::stamp		currentFrameTime = Time::getTimeStamp() - getTimer();
    
    std::lock_guard<Lock> l(_lock);

    i += 0.001;
    if (i > 1)
      i = 0;
    _background.setFrameIndex(i);
    _window.draw(_background);
    for (RemoteMap::iterator i = _map.begin(); i != _map.end(); i++)
      i->second->render(currentFrameTime, _window);
    for (std::list<explosion>::iterator i = _explosion.begin(); i != _explosion.end(); i++)
      _window.draw((*i).anim->getFrame());
}

Unit::AUnit*		Game::operator[](unsigned int id)
{
  std::lock_guard<Lock> l(_lock);
  
  return (_map.find(id)->second);
}
