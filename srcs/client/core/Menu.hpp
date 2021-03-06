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
#include "IMenuHandler.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "List.hpp"
#include "Message.hpp"

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

  typedef struct
  {
    unsigned int	posX;
    unsigned int	posY;
    Time::stamp		time;
  }			s_star;

private:
  int					_width;
  int					_height;
  float					_scale[2];
  IMenuHandler*				_client;
  sf::RenderWindow			_window;
  sf::Color				_fieldsColor;
  sf::Color				_loginColor;
  sf::Color				_loginSizeErrColor;
  sf::Color				_highlightColor;
  sf::Color				_startColor;
  unsigned int				_currentGameNumber;
  bool					_isConnected;
  bool					_isReady;
  Font					_fieldsFont;
  Font					_loginFont;
  ClickableBtn				_menuFields[MAX_NUMBER_OF_FIELDS];
  Editable				_login;
  Editable				_gameName;
  Editable				_host;
  Message				_loginSizeErr;
  Message				_serverMessage;
  ClickableBtn				_createButton;
  ClickableBtn				_connectButton;
  ClickableBtn				_refreshButton;
  ClickableBtn				_readyButton;
  List					_gameList;
  Row					_currentRow;
  Game *				_game;
  bool					_gameStart;
  SoundPlayer				_soundPlayer;
  Animation				_star;
  s_star				_stars[15];
  std::list<std::function<void()> >	_eventChecks;
  std::map<int, std::tuple<std::string, unsigned int, unsigned int, bool> > _roomsBuf;
  unsigned long				_time;
  std::string				_message;
  bool					_error;

public:
  Menu(int width, int height, IMenuHandler *client);
  ~Menu();

  void				initMainView();
  void				addGame(unsigned int id, std::string const&, unsigned int, unsigned int, std::string const &, bool);
  void				startGame(unsigned long time);
  void				setMessage(std::string const&, bool);

private:
  void				initColors();
  void				initStars();
  void				handleMouseClick(sf::Event&);
  void				handleMouseMoved(sf::Event&);
  void				editionHandler(sf::Event const&);
  void				handleLoginEdition(sf::Event&);
  void				handleHostEdition(sf::Event&);
  void				eventHandler();
  void				drawFields();
  void				drawEditable();
  void				drawMessage();
  void				drawStars();
  void				changeCurrentRow();
  void				handleGameListItem(sf::Event&);
  void				setConnected();
  void				reset();
};

#endif /* !MENU_HPP */
