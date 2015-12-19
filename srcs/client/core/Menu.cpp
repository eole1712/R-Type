#include "Menu.hpp"

Menu::Menu(int width, int height, Client* client):
  _client(client), _window(sf::VideoMode(width, height), "R-Type"),
  _fieldsColor(102,78,255), _loginColor(178,102,255), _loginSizeErrColor(204, 0, 0),
  _highlightColor(255, 255, 255), _startColor(121, 248, 248), _currentGameNumber(0), _isConnected(false),
  _fieldsFont("../../resources/menu/fonts/BebasNeue Bold.ttf"),
  _loginFont("../../resources/menu/fonts/BebasNeue Book.ttf"),
  _menuFields{ClickableBtn(width / 5, height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Login", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Create", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Host", _fieldsFont, _fieldsColor, 21),
    ClickableBtn(width / 5, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.6, "Games", _fieldsFont, _fieldsColor, 21)},
  _login(width / 2.5, height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Player", _loginFont, _loginColor, 16, 24),
  _gameName(width / 2.5, height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "GameName", _loginFont, _loginColor, 20, 24),
  _host(width / 2.5, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Host", _loginFont, _loginColor, 20, 24),
  _loginSizeErr(width / 2, height / (MAX_NUMBER_OF_FIELDS + 1) * 1.15, "16 chars max", _fieldsFont, _loginSizeErrColor, 16),
  _createButton(width / 1.3, height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Create", _fieldsFont, _startColor, 21),
  _connectButton(width / 1.3, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Connect", _fieldsFont, _startColor, 21),
  _refreshButton(width / 1.15, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Refresh", _fieldsFont, _startColor, 21),
  _startButton(width / 2.3, height / (MAX_NUMBER_OF_FIELDS + 3) * 6, "START", _fieldsFont, _startColor, 30),
  _gameList(width / 2.5, height / (MAX_NUMBER_OF_FIELDS + 2) * 2.6, _fieldsFont, _fieldsColor, _highlightColor), _currentRow(LOGIN)
{
}

Menu::~Menu()
{
  delete _client;
}

void		Menu::initMainView()
{
  Animation background(std::string("../../resources/menu/Background Menu.360x240x4.png"), 4, 300, Time::getTimeStamp());

  std::string	s = "game";
  std::string	t = "hello";
  
  _gameList.addItem(s, 1, t);
  _gameList.addItem(s, 2, t);
  _gameList.addItem(s, 3, t);
  _gameList.addItem(s, 4, t);
  _gameList.addItem(s, 5, t);

  background.scale(2, 2);
  _window.setVerticalSyncEnabled(true);
  while (_window.isOpen())
    {
      eventHandler();
      _window.clear();
      _window.draw(background.getFrame());
      this->drawFields();
      this->drawEditable();
      this->drawLoginSizeErr();
      if (_isConnected == true && _gameList.getList().size() != 0)
	_gameList.render(_window);
      _window.display();
    }
}

void		Menu::eventHandler()
{
  sf::Event event;

  while (_window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  _window.close();
	  break;
	case sf::Event::MouseMoved:
	  this->handleMouseMoved();
	  if (_gameList.getList().size() != 0)
	    _gameList.mouseMovedHandler(_window, event);
	  break;
	case sf::Event::MouseButtonReleased:
	  this->handleMouseClick();
	  if (_gameList.getList().size() != 0)
	    _gameList.clickHandler(_window, event);
	  break;
	case sf::Event::TextEntered:
	  editionHandler(event);
	  break;
	  case sf::Event::KeyPressed:
	  if (event.key.code == sf::Keyboard::Tab)
	    this->changeCurrentRow();
	  break;
	default:
	  break;
	}
    }
}

void		Menu::handleMouseClick()
{
   sf::Vector2f	mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);

   if (_startButton.getClickableBtn().getGlobalBounds().contains(mousePosition) && !_gameList.getCurrentItem().empty())
   {;
       _client->selectGame(_gameList.getCurrentItem());
//       Unit::Player	player(100, 290, 1, 0, _login.getEditable().getString());
//       Game		game(_client, _window, player);
     }
   else if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _client->connect(_host.getEditable().getString(), _login.getEditable().getString());
       _isConnected = true;
     }
   else if (_refreshButton.getClickableBtn().getGlobalBounds().contains(mousePosition) && _isConnected)
     {
       _gameList.clean();
       //_client->connect(_host.getEditable().getString(), _login.getEditable().getString());
       _client->refreshGames();
     }
   else if (_createButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _client->createGame((std::string) _gameName.getEditable().getString());
     }
   else
     _gameList.scrollHandler(_window);
}

void		Menu::handleMouseMoved()
{
  sf::Vector2f	mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);

  if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _connectButton.getClickableBtn().setColor(_highlightColor);
  else if (_startButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _startButton.getClickableBtn().setColor(_highlightColor);
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
      _startButton.getClickableBtn().setColor(_startColor);
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
    }
}

void		Menu::drawFields()
{
  for (int i = 0; i < MAX_NUMBER_OF_FIELDS; i++)
    {
      _menuFields[i].getClickableBtn().setColor(_fieldsColor);
      if (i == _currentRow)
	_menuFields[_currentRow].setColor(_highlightColor);
      _window.draw(_menuFields[i].getClickableBtn());
    }
  _window.draw(_createButton.getClickableBtn());
  _window.draw(_refreshButton.getClickableBtn());
  _window.draw(_connectButton.getClickableBtn());
  _window.draw(_startButton.getClickableBtn());
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

void		Menu::addGame(std::string const& gameName, unsigned int playerNumber, std::string const& daySentence)
{
  _gameList.addItem(gameName, playerNumber, daySentence);
}

void		Menu::setConnected()
{
  _isConnected = true;
}
