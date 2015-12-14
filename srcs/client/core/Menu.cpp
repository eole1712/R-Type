#include <unistd.h>
#include "Menu.hpp"
#include "Game.hpp"
#include "Player.hpp"

Menu::Menu(int width, int height):
  _width(width), _height(height), _window(sf::VideoMode(_width, _height), "R-Type"),
  _fieldsColor(102,78,255), _loginColor(178,102,255), _loginSizeErrColor(204, 0, 0),
  _highlightColor(255, 255, 255), _startColor(121, 248, 248)
{
  _currentRow = LOGIN;
  _maxLoginSize = false;
}

Menu::~Menu()
{
}

void		Menu::initMainView()
{
  Animation background(std::string("../../resources/menu/Background Menu.360x240x4.png"), 4, 300, Time::getTimeStamp());
  background.scale(2, 2);
  this->initFields();
  //  sf::RenderWindow window(sf::VideoMode(_width, _height), "R-Type");
  _window.setVerticalSyncEnabled(true);

  while (_window.isOpen())
    {
      eventHandler();
      _window.clear();
      _window.draw(background.getFrame());
      this->drawFields();
      this->drawEditable();
      this->drawLoginSizeErr();
      _window.display();
    }
}


void		Menu::initFields()
{
  if (!_fieldsFont.loadFromFile("../../resources/menu/fonts/BebasNeue Bold.ttf"))
    std::cout << "error loading Font" << std::endl;
  if (!_loginFont.loadFromFile("../../resources/menu/fonts/BebasNeue Book.ttf"))
    std::cout << "error loading Font" << std::endl;

  _menuFields[0] = ClickableBtn(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2, "Login", _fieldsFont, _fieldsColor);
  _menuFields[1] = ClickableBtn(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5, "Host", _fieldsFont, _fieldsColor);
  _menuFields[2] = ClickableBtn(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 3, "Server", _fieldsFont, _fieldsColor);
  _login = Editable(_width / 2, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2, "Player", _loginFont, _loginColor);
  _loginSizeErr = ClickableBtn(_width / 1.568, _height / (MAX_NUMBER_OF_FIELDS + 1) * 1.8, "16 chars max", _fieldsFont, _loginSizeErrColor, 21);
  _host = Editable(_width / 2, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5, "Host", _loginFont, _loginColor);
  _startButton = ClickableBtn(_width / 2.3, _height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7, "START", _fieldsFont, _startColor, 50);
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
	  this->handleMouseMoved(event);
	  break;
	case sf::Event::MouseButtonReleased:
	  this->handleMouseClick(event);
	  break;
	case sf::Event::TextEntered:
	  if (_currentRow == LOGIN)
	    this->handleLoginEdition(event);
	  else if (_currentRow == HOST)
	    this->handleHostEdition(event);
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

void		Menu::handleMouseClick(sf::Event& event)
{
   sf::Vector2f	mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);

   if (_startButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       Unit::Player	player(100, 270, 0, 0, _login.getEditable().getString());
       Game		game(_window, player);
	
      	while (!game.getFinish())
	  { 
	  }
     }
   if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     std::cout << "Connect" << std::endl;
}

void		Menu::handleMouseMoved(sf::Event& event)
{
  sf::Vector2f	mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);

  if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _connectButton.getClickableBtn().setColor(_highlightColor);
  else if (_startButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _startButton.getClickableBtn().setColor(_highlightColor);
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
      _startButton.getClickableBtn().setColor(_startColor);
      _connectButton.getClickableBtn().setColor(_startColor);
    }
}

void		Menu::handleLoginEdition(sf::Event& event)
{
  if (_login.getEditable().getString().getSize() <= 16)
    {
      _maxLoginSize = false;
      if (event.text.unicode >= 32 && event.text.unicode <= 126)
	_login.getEditable().setString(_login.getEditable().getString() + static_cast<char>(event.text.unicode));
    }
  else
    _maxLoginSize = true;
  if (event.text.unicode == 8)
    {
      _login.getEditable().setString(std::string(_login.getEditable().getString()).substr(0, _login.getEditable().getString().getSize()-1));
      _maxLoginSize = false;
    }
}

void		Menu::handleHostEdition(sf::Event& event)
{
  if (_host.getEditable().getString().getSize() <= 20)
    {
      if (event.text.unicode >= 32 && event.text.unicode <= 126)
	_host.getEditable().setString(_host.getEditable().getString() + static_cast<char>(event.text.unicode));
    }
  if (event.text.unicode == 8)
    {
      _host.getEditable().setString(std::string(_host.getEditable().getString()).substr(0, _host.getEditable().getString().getSize()-1));
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
  _window.draw(_connectButton.getClickableBtn());
  _window.draw(_startButton.getClickableBtn());
}

void		Menu::drawEditable()
{
  _window.draw(_login.getEditable());
  _window.draw(_host.getEditable());
}

void		Menu::drawLoginSizeErr()
{
  if (_maxLoginSize == true)
    _window.draw(_loginSizeErr.getClickableBtn());
}

void		Menu::changeCurrentRow()
{
  switch (_currentRow)
    {
    case LOGIN:
      _currentRow = HOST;
      break;
    case HOST:
      _currentRow = SERVER;
      break;
    case SERVER:
      _currentRow = LOGIN;
      break;
    }
}

void		Menu::addGame(std::string gameName, unsigned int playerNumber, std::string daySentence)
{
  s_gameData	newGame;

  newGame._gameName = gameName;
  newGame._playerNumber = playerNumber;
  newGame._daySentence = daySentence;
  _gamesData.push_back(newGame);
}
