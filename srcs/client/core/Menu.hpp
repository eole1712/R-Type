#ifndef MENU_HPP
# define MENU_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Animation.hpp"
#include "ClickableBtn.hpp"
#include "Editable.hpp"
#include "GameListItem.hpp"

#define MAX_NUMBER_OF_FIELDS 3

class Menu
{
private:
  enum Row : unsigned int{
    LOGIN,
    HOST,
    SERVER
  };

private:
  int					_width;
  int					_height;
  sf::RenderWindow			_window;
  sf::Color				_fieldsColor;
  sf::Color				_loginColor;
  sf::Color				_loginSizeErrColor;
  sf::Color				_highlightColor;
  sf::Color				_startColor;
  ClickableBtn				_menuFields[MAX_NUMBER_OF_FIELDS];
  Editable				_login;
  Editable				_host;
  ClickableBtn				_loginSizeErr;
  ClickableBtn				_startButton;
  ClickableBtn				_connectButton;
  ClickableBtn				_refreshButton;
  ClickableBtn				_gameListUp;
  ClickableBtn				_gameListDown;
  sf::Font				_fieldsFont;
  sf::Font				_loginFont;
  Row					_currentRow;
  bool					_maxLoginSize;
  unsigned int				_gameListPosX;
  unsigned int				_gameListPosY;
  unsigned int				_currentGameNumber;
  std::list<GameListItem>		_gamesData;
  std::list<GameListItem>::iterator	_gameListIt;
  std::list<GameListItem>::iterator	_currentSelectedGame;
  bool					_isConnected;
  
public:
  Menu(int width, int height);
  ~Menu();

  void				initMainView();
  void				addGame(std::string&, unsigned int, std::string&);

private:
  void				initFields();
  void				initColors();
  void				initPlayerColorSelection();
  void				handleMouseClick();
  void				handleMouseMoved();
  void				handleLoginEdition(sf::Event&);
  void				handleHostEdition(sf::Event&);
  void				eventHandler();
  void				drawFields();
  void				drawEditable();
  void				drawLoginSizeErr();
  void				drawGameList();
  void				changeCurrentRow();
  void				handleGameListItem(sf::Event&);
  void				gamesToPrint(bool);
};

#endif /* !MENU_HPP */
