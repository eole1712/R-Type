#include <iostream>
#include <list>
#include <unistd.h>
#include "Menu.hpp"
#include "Time.hpp"
#include "Animation.hpp"

Menu::Menu(int width, int height):
  _width(width), _height(height), _fieldsColor(102,78,255), _loginColor(178,102,255),
  _loginSizeErrColor(204, 0, 0), _highlightColor(255, 255, 255), _startColor(121, 248, 248),
  _BRYGColor({sf::Color(0, 0, 255), sf::Color(187, 11, 11), sf::Color(243, 214, 23), sf::Color(20, 148, 5)}),
  _BRYGhighlight({sf::Color(0, 191, 255), sf::Color(255, 48, 48), sf::Color(255, 255, 5), sf::Color(0, 255, 0)})
{
  _currentRow = LOGIN;
  _currentPlayerColor = BLUE;
  _maxLoginSize = false;
}

Menu::~Menu()
{
}

void Menu::initMainView()
{
  Animation background(std::string("../../resources/menu/Background Menu.360x240x4.png"), 4, 300, Time::getTimeStamp());
  background.scale(2, 2);
  this->initFields();
  sf::RenderWindow window(sf::VideoMode(_width, _height), "R-Type");
  window.setVerticalSyncEnabled(true);

  while (window.isOpen())
    {
      eventHandler(window);
      window.clear();
      window.draw(background.getFrame());
      usleep(50000);
      this->drawFields(window);
      this->drawLogin(window);
      this->drawLoginSizeErr(window);
      window.display();
    }
}


void		Menu::initFields()
{
  if (!_fieldsFont.loadFromFile("../../resources/menu/fonts/BebasNeue Bold.ttf"))
    std::cout << "error loading Font" << std::endl;
  if (!_loginFont.loadFromFile("../../resources/menu/fonts/BebasNeue Book.ttf"))
    std::cout << "error loading Font" << std::endl;

  _menuFields[0] = sf::Text("Login", _fieldsFont, 30);
  _menuFields[0].setColor(_fieldsColor);
  _menuFields[0].setPosition(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2);


   _menuFields[1] = sf::Text("Color", _fieldsFont, 30);
  _menuFields[1].setColor(_fieldsColor);
  _menuFields[1].setPosition(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5);

  _menuFields[2] = sf::Text("Game", _fieldsFont, 30);
  _menuFields[2].setColor(_fieldsColor);
  _menuFields[2].setPosition(_width / 4, _height / (MAX_NUMBER_OF_FIELDS + 2) * 3);

  _login = sf::Text("Player", _loginFont, 30);
  _login.setColor(_loginColor);
  _login.setPosition(_width / 2, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2);

  _loginSizeErr = sf::Text("16 chars max", _loginFont, 30);
  _loginSizeErr.setColor(_loginSizeErrColor);
  _loginSizeErr.setPosition(_width / 1.568, _height / (MAX_NUMBER_OF_FIELDS + 1) * 1.8);
  _loginSizeErr.scale(0.7, 0.7);

  _startButton = sf::Text("START", _fieldsFont, 50);
  _startButton.setColor(_startColor);
  _startButton.setPosition(_width / 2.3, _height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7);
  initPlayerColorSelection();
}

void	Menu::initPlayerColorSelection()
{
  _playerColor[0] = sf::Text("BLUE", _fieldsFont, 21);
  _playerColor[0].setColor(_BRYGColor[0]);
  _playerColor[0].setPosition(_width / 2, (_height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5) + 10);

  _playerColor[1] = sf::Text("RED", _fieldsFont, 21);
  _playerColor[1].setColor(_BRYGColor[1]);
  _playerColor[1].setPosition(_width / 1.78, (_height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5) + 10);

  _playerColor[2] = sf::Text("YELLOW", _fieldsFont, 21);
  _playerColor[2].setColor(_BRYGColor[2]);
  _playerColor[2].setPosition(_width / 1.65, (_height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5) + 10);

  _playerColor[3] = sf::Text("GREEN", _fieldsFont, 21);
  _playerColor[3].setColor(_BRYGColor[3]);
  _playerColor[3].setPosition(_width / 1.45, (_height / (MAX_NUMBER_OF_FIELDS + 2) * 2.5) + 10);
}

void	Menu::eventHandler(sf::RenderWindow& window)
{
  sf::Event event;
  while (window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  window.close();
	  break;
	case sf::Event::MouseMoved:
	  this->handleMouseMoved(window, event);
	  break;
	case sf::Event::MouseButtonReleased:
	  this->handleMouseClick(window, event);
	  break;
	case sf::Event::TextEntered:
	  this->handleLoginEdition(window, event);
	  break;
	case sf::Event::KeyPressed:
	  if (event.key.code == sf::Keyboard::Tab)
	    this->changeCurrentRow();
	  if (_currentRow == COLOR && (event.key.code == sf::Keyboard::Left ||
				       event.key.code == sf::Keyboard::Right))
	    this->changeCurrentColor(event);
	  break;
	default:
	  break;
	}
    }
}

void	Menu::handleMouseClick(sf::RenderWindow& window, sf::Event& event)
{
  if (sf::Mouse::getPosition(window).x >= (_width / 2.3) && sf::Mouse::getPosition(window).x <= (_width / 2.3) + 93 &&
      sf::Mouse::getPosition(window).y >= (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) && sf::Mouse::getPosition(window).y <= (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) + 67)
    std::cout << "START" << std::endl;
  std::cout << "origin x pos: " << (_width / 2.3)  << std::endl;
  std::cout << "origin y pos: " << (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) << std::endl;
  std::cout << "mouse click, posx : " <<  sf::Mouse::getPosition(window).x << std::endl;

}

void	Menu::handleMouseMoved(sf::RenderWindow& window, sf::Event& event)
{
  if (sf::Mouse::getPosition(window).x >= (_width / 2.3) && sf::Mouse::getPosition(window).x <= (_width / 2.3) + 93 &&
      sf::Mouse::getPosition(window).y >= (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) && sf::Mouse::getPosition(window).y <= (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) + 67)
    _startButton.setColor(_highlightColor);
  if (sf::Mouse::getPosition(window).x < (_width / 2.3) || sf::Mouse::getPosition(window).x > (_width / 2.3) + 93 &&
      sf::Mouse::getPosition(window).y < (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) || sf::Mouse::getPosition(window).y > (_height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7) + 67)
    _startButton.setColor(_startColor);
}

void	Menu::handleLoginEdition(sf::RenderWindow& window, sf::Event& event)
{
  if (_currentRow == LOGIN)
    {
      if (_login.getString().getSize() <= 16)
	{
	  _maxLoginSize = false;
	  if (event.text.unicode >= 32 && event.text.unicode <= 126)
	    _login.setString(_login.getString() + static_cast<char>(event.text.unicode));
	}
      else
	_maxLoginSize = true;
      if (event.text.unicode == 8)
	{
	  _login.setString(std::string(_login.getString()).substr(0, _login.getString().getSize()-1));
	  _maxLoginSize = false;
	}
    }
  //std::cout << "login : " << (std::string) _login.getString() << std::endl;
}

void Menu::drawFields(sf::RenderWindow &window)
{
  for (int i = 0; i < MAX_NUMBER_OF_FIELDS; i++)
    {
      _menuFields[i].setColor(_fieldsColor);
      if (i == _currentRow)
	_menuFields[_currentRow].setColor(_highlightColor);
      window.draw(_menuFields[i]);
    }
  for (int i = 0; i < NUMBER_OF_PLAYER_COLOR; i++)
    {
      _playerColor[i].setColor(_BRYGColor[i]);
      if (i == _currentPlayerColor)
	_playerColor[_currentPlayerColor].setColor(_BRYGhighlight[i]);
      window.draw(_playerColor[i]);
    }
  window.draw(_startButton);
}

void	Menu::drawLogin(sf::RenderWindow& window)
{
  window.draw(_login);
}

void	Menu::drawLoginSizeErr(sf::RenderWindow& window)
{
  if (_maxLoginSize == true)
    window.draw(_loginSizeErr);
}

void	Menu::changeCurrentRow()
{
  switch (_currentRow)
    {
    case LOGIN:
      _currentRow = COLOR;
      break;
    case COLOR:
      _currentRow = GAME;
      break;
    case GAME:
      _currentRow = LOGIN;
      break;
    }
}

void	Menu::changeCurrentColor(sf::Event& event)
{
  switch (event.key.code)
    {
    case sf::Keyboard::Left:
      std::cout << "left" << std::endl;
      if (_currentPlayerColor > 0)
	_currentPlayerColor = static_cast<PlayerColor>(_currentPlayerColor - 1);
      else
	_currentPlayerColor = static_cast<PlayerColor>(_currentPlayerColor + 3);
      break;
    case sf::Keyboard::Right:
      if (_currentPlayerColor < 3)
	_currentPlayerColor = static_cast<PlayerColor>(_currentPlayerColor + 1);
      else
	_currentPlayerColor = static_cast<PlayerColor>(_currentPlayerColor - 3);
      break;
    default:
      break;
    }
}
