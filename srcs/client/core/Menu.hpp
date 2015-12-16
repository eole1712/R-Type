#ifndef MENU_HPP
# define MENU_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Animation.hpp"
#include "ClickableBtn.hpp"
#include "Editable.hpp"
#include "GameListItem.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "List.hpp"

#define MAX_NUMBER_OF_FIELDS 4

class Client;

class Menu
{
private:
  enum Row : unsigned int{
    LOGIN,
      CREATE,
      HOST,
      SERVER
      };

private:
  int					_width;
  int					_height;
  Client*				_client;
  sf::RenderWindow			_window;
  sf::Color				_fieldsColor;
  sf::Color				_loginColor;
  sf::Color				_loginSizeErrColor;
  sf::Color				_highlightColor;
  sf::Color				_startColor;
  unsigned int				_gameListPosX;
  unsigned int				_gameListPosY;
  unsigned int				_currentGameNumber;
  bool					_isConnected;
  ClickableBtn				_menuFields[MAX_NUMBER_OF_FIELDS];
  Editable				_login;
  Editable				_gameName;
  Editable				_host;
  ClickableBtn				_loginSizeErr;
  ClickableBtn				_createButton;
  ClickableBtn				_connectButton;
  ClickableBtn				_refreshButton;
  ClickableBtn				_startButton;
  List					_gameList;
  sf::Font				_fieldsFont;
  sf::Font				_loginFont;
  Row					_currentRow;
  //  bool					_maxLoginSize;
  /*  std::list<GameListItem>		_gamesData;
  stxd::list<GameListItem>::iterator	_gameListIt;
  std::list<GameListItem>::iterator	_currentSelectedGame;*/
   //  sf::String				_currentGameName;
  
public:
  Menu(int width, int height, Client *client);
  ~Menu();

  void				initMainView();
  void				addGame(std::string const&, unsigned int, std::string const&);

private:
  void				loadFonts();
  void				initColors();
  void				initPlayerColorSelection();
  void				handleMouseClick();
  void				handleMouseMoved();
  void				editionHandler(sf::Event const&);
  void				handleLoginEdition(sf::Event&);
  void				handleHostEdition(sf::Event&);
  void				eventHandler();
  void				drawFields();
  void				drawEditable();
  void				drawLoginSizeErr();
  void				changeCurrentRow();
  void				handleGameListItem(sf::Event&);
  void				setConnected();
};

#endif /* !MENU_HPP */
