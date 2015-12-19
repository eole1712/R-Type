#ifndef MENU_HPP
# define MENU_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "Animation.hpp"
#include "ClickableBtn.hpp"
#include "Font.hpp"
#include "Editable.hpp"
#include "GameListItem.hpp"
#include "SoundPlayer.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "List.hpp"
#include "Error.hpp"

#define MAX_NUMBER_OF_FIELDS 4

class Player;
class Client;
class Game;

class Menu
{
private:
  enum Row : unsigned int
  {
    LOGIN,
    CREATE,
    HOST,
    SERVER
  };

private:
  int					_width;
  int					_height;
  float					_scale[2];
  Client*				_client;
  sf::RenderWindow			_window;
  sf::Color				_fieldsColor;
  sf::Color				_loginColor;
  sf::Color				_loginSizeErrColor;
  sf::Color				_highlightColor;
  sf::Color				_startColor;
  unsigned int				_currentGameNumber;
  bool					_isConnected;
  Font					_fieldsFont;
  Font					_loginFont;
  ClickableBtn				_menuFields[MAX_NUMBER_OF_FIELDS];
  Editable				_login;
  Editable				_gameName;
  Editable				_host;
  Error					_loginSizeErr;
  ClickableBtn				_createButton;
  ClickableBtn				_connectButton;
  ClickableBtn				_refreshButton;
  ClickableBtn				_startButton;
  List					_gameList;
  Row					_currentRow;
  Game *				_game;
  bool					_gameStart;
  SoundPlayer				_soundPlayer;
  std::list<std::function<void()> >	_eventChecks;
  std::map<int, std::pair<std::string, unsigned int>> _roomsBuf;
public:
  Menu(int width, int height, Client *client);
  ~Menu();

  void				initMainView();
  void				addGame(std::string const&, unsigned int, int);
  void				startGame();

private:
  void				initColors();
  void				initPlayerColorSelection();
  void				handleMouseClick(sf::Event&);
  void				handleMouseMoved(sf::Event&);
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
