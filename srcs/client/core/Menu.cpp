#include <unistd.h>
#include "Menu.hpp"

Menu::Menu(int width, int height, Client* client):
  _width(width), _height(height), _client(client), _window(sf::VideoMode(_width, _height), "R-Type"),
  _fieldsColor(102,78,255), _loginColor(178,102,255), _loginSizeErrColor(204, 0, 0),
  _highlightColor(255, 255, 255), _startColor(121, 248, 248), _gameListPosX(width / 2.5),
  _gameListPosY(_height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1), _currentGameNumber(0), _isConnected(false),
  _menuFields{ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Login", _fieldsFont, _fieldsColor),
	ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Host", _fieldsFont, _fieldsColor),
	ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Games", _fieldsFont, _fieldsColor)},
  _login(_width / 2.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Player", _loginFont, _loginColor),
  _host(_width / 2.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Host", _loginFont, _loginColor),
  _loginSizeErr(_width / 1.568, _height / (MAX_NUMBER_OF_FIELDS + 1) * 1.1, "16 chars max", _fieldsFont, _loginSizeErrColor, 21),
  _connectButton(_width / 1.3, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.7, "Connect", _fieldsFont, _startColor, 21),
  _refreshButton(_width / 1.15, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.7, "Refresh", _fieldsFont, _startColor, 21),
  _startButton(_width / 2.3, _height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7, "START", _fieldsFont, _startColor, 50),
  _gameList(_width / 1.5,  _height / (MAX_NUMBER_OF_FIELDS + 2), _fieldsFont, _fieldsColor, _highlightColor)
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
  this->loadFonts();
  _window.setVerticalSyncEnabled(true);
  while (_window.isOpen())
    {
      eventHandler();
      _window.clear();
      _window.draw(background.getFrame());
      this->drawFields();
      this->drawEditable();
      this->drawLoginSizeErr();
      if (_isConnected == true && _gameList.getGameList().size() != 0)
	_gameList.drawGameList(_window);
      _window.display();
    }
}

void		Menu::loadFonts()
{
  if (!_fieldsFont.loadFromFile("../../resources/menu/fonts/BebasNeue Bold.ttf"))
    std::cout << "error loading Font" << std::endl;
  if (!_loginFont.loadFromFile("../../resources/menu/fonts/BebasNeue Book.ttf"))
    std::cout << "error loading Font" << std::endl;

  /*_menuFields[0] = ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Login", _fieldsFont, _fieldsColor);
  _menuFields[1] = ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Host", _fieldsFont, _fieldsColor);
  _menuFields[2] = ClickableBtn(_width / 5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "Games", _fieldsFont, _fieldsColor);
  _login = Editable(_width / 2.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.1, "Player", _loginFont, _loginColor);
  _loginSizeErr = ClickableBtn(_width / 1.568, _height / (MAX_NUMBER_OF_FIELDS + 1) * 1.1, "16 chars max", _fieldsFont, _loginSizeErrColor, 21);
  _host = Editable(_width / 2.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.6, "Host", _loginFont, _loginColor);
  _connectButton = ClickableBtn(_width / 1.3, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.7, "Connect", _fieldsFont, _startColor, 21);
  _refreshButton = ClickableBtn(_width / 1.15, _height / (MAX_NUMBER_OF_FIELDS + 2) * 1.7, "Refresh", _fieldsFont, _startColor, 21);
  //  _gameListUp = ClickableBtn(_width / 1.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 2.1, "/\\", _fieldsFont, _fieldsColor, 21);
  //_gameListDown = ClickableBtn(_width / 1.5, _height / (MAX_NUMBER_OF_FIELDS + 2) * 3.4, "\\/", _fieldsFont, _fieldsColor, 21);
  _gameList = List(_width / 1.5,  _height / (MAX_NUMBER_OF_FIELDS + 2), _fieldsFont, _fieldsColor, _highlightColor);
  _startButton = ClickableBtn(_width / 2.3, _height / (MAX_NUMBER_OF_FIELDS + 3) * 4.7, "START", _fieldsFont, _startColor, 50);*/
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
	  if (_gameList.getGameList().size() != 0)
	    //this->handleGameListItem(event);
	    _gameList.mouseMovedHandler(_window, event);
	  break;
	case sf::Event::MouseButtonReleased:
	  this->handleMouseClick();
	  if (_gameList.getGameList().size() != 0)
	    //this->handleGameListItem(event);
	    _gameList.clickHandler(_window, event);
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

void		Menu::handleMouseClick()
{
   sf::Vector2f	mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);

   if (_startButton.getClickableBtn().getGlobalBounds().contains(mousePosition) && !_gameList.getCurrentGameName().empty())
     {
       Unit::Player	player(100, 290, 1, 0, _login.getEditable().getString());
       Game		game(_client, _window, player, _gameList.getCurrentGameName());
     }
   else if (_connectButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     {
       _client->connect(_host.getEditable().getString(), _login.getEditable().getString());
       //       _isConnected = true;
     }
   else if (_refreshButton.getClickableBtn().getGlobalBounds().contains(mousePosition))
     std::cout << "Refresh" << std::endl;
   else
     _gameList.scrollHandler(_window);
   /*else if (_gameList.getGameList().size() != 0 && _gameListUp.getClickableBtn().getGlobalBounds().contains(mousePosition))
     _gameList.slide(true);
   else if (_gameList.getGameList().size() != 0 && _gameListDown.getClickableBtn().getGlobalBounds().contains(mousePosition))
   _gameList.slide(false);*/
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
  /*  else if (_isConnected && _gamesData.size() != 0 && _gameListUp.getClickableBtn().getGlobalBounds().contains(mousePosition))
    _gameListUp.getClickableBtn().setColor(_highlightColor);
  else if (_isConnected && _gamesData.size() != 0 && _gameListDown.getClickableBtn().getGlobalBounds().contains(mousePosition))
  _gameListDown.getClickableBtn().setColor(_highlightColor);*/
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
      _refreshButton.getClickableBtn().setColor(_startColor);
      /*     if (_isConnected)
	{
	  _gameListUp.getClickableBtn().setColor(_fieldsColor);
	  _gameListDown.getClickableBtn().setColor(_fieldsColor);
	  }*/
    }
}

void		Menu::handleLoginEdition(sf::Event& event)
{
  if (_login.getEditable().getString().getSize() <= 15)
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
/*
void		Menu::handleGameListItem(sf::Event& event)
{
  int		i = 5;

  switch (event.type)
    {
    case sf::Event::MouseMoved:
      //_gameList.listMouseMovedHandler();
      for(std::list<GameListItem>::iterator it = _gameListIt;
	  it != _gamesData.end() && i > 0; it++)
	{
	  i--;
	  (*it).eventHandler(_window, event);
	}
      break;
    case sf::Event::MouseButtonReleased:
      //_gameList.listClickHandler();
      for(std::list<GameListItem>::iterator it = _gameListIt;
	  it != _gamesData.end() && i > 0; it++)
	{
	  i--;
	  if ((*it).getIsSelected() == true)
	    {
	      (*it).setIsSelected(false);
	      (*it).setColor(_fieldsColor);
	    }
	  if (sf::Mouse::getPosition(_window).x >= (*it).getPosX() && sf::Mouse::getPosition(_window).x <= (*it).getPosX() + 140
	      && sf::Mouse::getPosition(_window).y >= (*it).getPosY() && sf::Mouse::getPosition(_window).y <= (*it).getPosY() + 21)
	    {
	      (*it).setIsSelected(true);
	      //std::string name = (*it).getName().getString();
	      (*it).setColor(sf::Color(255, 255, 102));
	      _currentGameName = (*it).getName().getString();
	      //	      _client->selectGame((*it).getName().getString());
	    }
	  (*it).eventHandler(_window, event);
	  }
      break;
    }
}

void		Menu::gamesToPrint(bool up)
{
  //  std::cout << "what to print" << std::endl;
  if (_gamesData.size() > 5)
    {
      // std::cout << "what to print in if" << std::endl;
      if (up == true && _gameListIt != _gamesData.begin())
	{
	  _gameListIt--;
	  for (std::list<GameListItem>::iterator it = _gamesData.begin(); it != _gamesData.end(); it++ )
	    {
	      (*it).setPosY((*it).getPosY() + 30);
	      (*it).updatePosition();
	    }
	}
      else if (up == false && std::distance(_gameListIt, _gamesData.end()) > 5)
	{
	  // std::cout << "what to print in else" << std::endl;
	  _gameListIt++;
	  for (std::list<GameListItem>::iterator it = _gamesData.begin(); it != _gamesData.end(); it++ )
	    {
	      (*it).setPosY((*it).getPosY() - 30);
	      (*it).updatePosition();
	    }
	}
    }
}*/

void		Menu::drawFields()
{
  for (int i = 0; i < MAX_NUMBER_OF_FIELDS; i++)
    {
      _menuFields[i].getClickableBtn().setColor(_fieldsColor);
      if (i == _currentRow)
	_menuFields[_currentRow].setColor(_highlightColor);
      _window.draw(_menuFields[i].getClickableBtn());
    }
  _window.draw(_refreshButton.getClickableBtn());
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
/*
void		Menu::drawGameList()
{
  int		i = 5;

  if (_isConnected == true && _gamesData.size() != 0)
    {
      for (std::list<GameListItem>::iterator it = _gameListIt;
	   it != _gamesData.end() && i > 0; it++)
	{
	  i--;
	  _window.draw((*it).getName());
	  _window.draw((*it).getPlayerNumber());
	}
      _window.draw(_gameListUp.getClickableBtn());
      _window.draw(_gameListDown.getClickableBtn());
    }
    }*/

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
/*
void		Menu::addGame(std::string const& gameName, unsigned int playerNumber, std::string const& daySentence)
{
  std::string	playerNumberToString;

  playerNumberToString = std::to_string(playerNumber);
  GameListItem	gameListItem(_gameListPosX, _gameListPosY + (30 * _currentGameNumber), gameName, playerNumberToString, daySentence, _fieldsFont, _fieldsColor, _highlightColor);
  _gamesData.push_back(gameListItem);
  if (_gamesData.size() == 1)
    _gameListIt = _gamesData.begin();
  _currentGameNumber += 1;
}*/

void		Menu::setConnected()
{
  _isConnected = true;
}
