#include "Menu.hpp"
#include "ClientKeyboardPressPacket.hpp"

Menu::Menu(int width, int height, IMenuHandler* client):
  _width(width), _height(height), _scale{1, 1},
  _client(client), _window(sf::VideoMode(width, height), "R-Type"),
  _fieldsColor(102,78,255), _loginColor(178,102,255), _loginSizeErrColor(204, 0, 0),
  _highlightColor(255, 255, 255), _startColor(121, 248, 248), _currentGameNumber(0), _isConnected(false),
  _isReady(false),
  _fieldsFont("../resources/menu/fonts/BebasNeue Bold.ttf"),
  _loginFont("../resources/menu/fonts/BebasNeue Book.ttf"),
  _menuFields{ClickableBtn(width / 5, static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1), "Login", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6), "Create", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1), "Host", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.6), "Games", _fieldsFont, _fieldsColor, 21)},
  _login(static_cast<unsigned int>(width / 2.5), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1), "Player", _loginFont, _loginColor, 16, 24),
  _gameName(static_cast<unsigned int>(width / 2.5), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6), "GameName", _loginFont, _loginColor, 20, 24),
  _host(static_cast<unsigned int>(width / 2.5), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1), "Host", _loginFont, _loginColor, 20, 24),
  _loginSizeErr(width / 2, static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 1) * 1.15), "16 chars max", _fieldsFont, _loginSizeErrColor, 16),
  _createButton(static_cast<unsigned int>(width / 1.3), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6), "Create", _fieldsFont, _startColor, 21),
  _connectButton(static_cast<unsigned int>(width / 1.3), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1), "Connect", _fieldsFont, _startColor, 21),
  _refreshButton(static_cast<unsigned int>(width / 1.15), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1), "Refresh", _fieldsFont, _startColor, 21),
  _readyButton(static_cast<unsigned int>(width / 2.3), height / (MAX_NUMBER_OF_FIELDS + 3) * 6, "READY", _fieldsFont, _startColor, 30),
  _gameList(static_cast<unsigned int>(width / 2.5), static_cast<unsigned int>(height / (MAX_NUMBER_OF_FIELDS + 2) * 2.6), _fieldsFont, _fieldsColor, _highlightColor), _currentRow(LOGIN),
  _game(NULL), _gameStart(false), _soundPlayer("../resources/sound/MegaMan.ogg")
{
  _eventChecks.push_back([this] () {
      if (_gameStart)
	{
	  _game = new Game(_client->getGameHandler(), _window, 0, _login.getEditable().getString(), _time);
	  _game->loop();
	  _gameStart = false;
	}
      });
      _eventChecks.push_back([this] () {
	for (auto& room : _roomsBuf)
	  {
	    _gameList.addItem(room.first,
			      std::get<0>(room.second),
			      std::get<1>(room.second),
			      std::get<2>(room.second),
			      std::get<0>(room.second),
			      (std::get<0>(room.second) == ((std::string) _gameName.getEditable().getString())),
            std::get<3>(room.second));
	  }
	_roomsBuf.clear();
      });
    }

Menu::~Menu()
{
  if (_game != NULL)
    delete _game;
}

void		Menu::initMainView()
{
  Animation background(std::string("../resources/menu/Background Menu.360x240x4.png"), 4, 300, Time::getTimeStamp());

  //_soundPlayer.play();
  _window.setVerticalSyncEnabled(true);
  _window.setKeyRepeatEnabled(false);
  _soundPlayer.pause();
  while (_window.isOpen())
    {
      for (auto& elem : _eventChecks) {
	elem();
      }
      eventHandler();
      _window.clear();
      _window.draw(background.getFrame());
      this->drawFields();
      this->drawEditable();
      this->drawLoginSizeErr();
      if (_gameList.getList().size() != 0)
	_gameList.render(_window);
      _window.display();
    }
}

void		Menu::eventHandler()
{
  sf::Event event;

  while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::MouseMoved||
	  event.type == sf::Event::MouseButtonReleased)
	{
	  event.mouseMove.x = static_cast<int>(sf::Mouse::getPosition(_window).x * _scale[0]);
	  event.mouseMove.y = static_cast<int>(sf::Mouse::getPosition(_window).y * _scale[1]);
	}
      switch (event.type)
	{
	  case sf::Event::Resized:
	    _scale[0] = float(_width) / event.size.width;
	    _scale[1] = float(_height) / event.size.height;
	    break;
	case sf::Event::Closed:
	  _window.close();
	  break;
	case sf::Event::MouseMoved:
	  this->handleMouseMoved(event);
	  if (_gameList.getList().size() != 0)
	    _gameList.mouseMovedHandler(_window, event);
	  break;
	case sf::Event::MouseButtonReleased:
	  this->handleMouseClick(event);
	  if (_gameList.getList().size() != 0)
	    if (_gameList.clickHandler(event) == true)
	      _client->selectGame(_gameList.getCurrentItem());
	  break;
	case sf::Event::TextEntered:
	  editionHandler(event);
	  break;
	case sf::Event::KeyPressed:
	  if (event.key.code == sf::Keyboard::Tab)
	    this->changeCurrentRow();
	  if (event.key.code == sf::Keyboard::Space) {
	    _client->sendKey(ClientKeyboardPressPacket::SpacePress);
	    _isReady = true;
	  }
	  break;
	default:
	  break;
	}
    }
}

void		Menu::handleMouseClick(sf::Event& event)
{
   sf::Vector2f	mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

   if (_readyButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _client->sendKey(ClientKeyboardPressPacket::SpacePress);
       _isReady = true;
     }
   else if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _client->connect(_host.getEditable().getString(), _login.getEditable().getString());
       _gameList.clean();
       _client->refreshGames();
       _isConnected = true;
     }
   else if (_refreshButton.getClickableBtn().getGlobalBounds().contains(mousePosition) && _isConnected)
     {
       _gameList.clean();
       _client->refreshGames();
     }
   else if (_createButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _gameList.clean();
       _client->createGame((std::string) _gameName.getEditable().getString());
     }
   else
     _gameList.scrollHandler(event);
}

void		Menu::handleMouseMoved(sf::Event& event)
{
  sf::Vector2f	mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

  if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _connectButton.getClickableBtn().setColor(_highlightColor);
  else if (_readyButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _readyButton.getClickableBtn().setColor(_highlightColor);
  else if (_refreshButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _refreshButton.getClickableBtn().setColor(_highlightColor);
  else if (_createButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _createButton.getClickableBtn().setColor(_highlightColor);
  else
    {
      for (int i = 0; i < MAX_NUMBER_OF_FIELDS; i++)
	{
	  _menuFields[i].getClickableBtn().setColor(_fieldsColor);
	  if (_menuFields[i].getClickableBtn().getGlobalBounds().contains(mousePosition))
	    {
	      _menuFields[i].getClickableBtn().setColor(_highlightColor);
	      _currentRow = static_cast<Row>(i);
	    }
	}
      _createButton.getClickableBtn().setColor(_startColor);
      _readyButton.getClickableBtn().setColor(_startColor);
      _connectButton.getClickableBtn().setColor(_startColor);
      _refreshButton.getClickableBtn().setColor(_startColor);
    }
}

void		Menu::editionHandler(sf::Event const& event)
{
  switch (_currentRow)
    {
    case LOGIN:
      _login.editionHandler(event);
      break;
    case CREATE:
      _gameName.editionHandler(event);
      break;
    case HOST:
      _host.editionHandler(event);
      break;
    default:
      break;
    }
}

void		Menu::drawFields()
{
  for (unsigned int i = 0; i < MAX_NUMBER_OF_FIELDS; i++)
    {
      _menuFields[i].getClickableBtn().setColor(_fieldsColor);
      if (i == _currentRow)
	_menuFields[_currentRow].setColor(_highlightColor);
      _window.draw(_menuFields[i].getClickableBtn());
    }
  _window.draw(_createButton.getClickableBtn());
  _window.draw(_refreshButton.getClickableBtn());
  _window.draw(_connectButton.getClickableBtn());
  int currentId = _client->getRoomConnected();
  auto it = _gameList.getList().find(currentId);
  if (_isConnected && currentId != 0 && it != _gameList.getList().end())
    {
      if (it->second.isReady())
	_readyButton.getClickableBtn().setColor(sf::Color(0, 255, 0));
      else
	_readyButton.getClickableBtn().setColor(sf::Color(255, 0, 0));
      _window.draw(_readyButton.getClickableBtn());
    }
}

void		Menu::drawEditable()
{
  _window.draw(_login.getEditable());
  _window.draw(_gameName.getEditable());
  _window.draw(_host.getEditable());
}

void		Menu::drawLoginSizeErr()
{
  if (_login.getMaxSize() == true)
    _loginSizeErr.render(_window);
}

void		Menu::changeCurrentRow()
{
  if (_currentRow < 3)
    _currentRow = static_cast<Row>(_currentRow + 1);
  else
    _currentRow = static_cast<Row>(0);
}

void		Menu::startGame(unsigned long currentTime)
{
  _gameStart = true;
  _time = currentTime;
}

void		Menu::addGame(unsigned int id, std::string const& gameName, unsigned int playerNumber, unsigned int playerReady, std::string const&, bool isReady)
{
  _roomsBuf[id] = std::make_tuple(gameName, playerNumber, playerReady, isReady);
}

void		Menu::setConnected()
{
  _isConnected = true;
}
