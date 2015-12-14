#ifndef MENU_HPP
# define MENU_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Animation.hpp"
#include "ClickableBtn.hpp"
#include "Editable.hpp"

#define MAX_NUMBER_OF_FIELDS 3

class Menu
{
private:
  enum Row : unsigned int{
    LOGIN,
    HOST,
    SERVER
  };

public:
  typedef struct	t_gameData
  {
    std::string		_gameName;
    unsigned int	_playerNumber;
    std::string		_daySentence;
  }			s_gameData;
  
private:
  int			_width;
  int			_height;
  sf::RenderWindow	_window;
  sf::Color		_fieldsColor;
  sf::Color		_loginColor;
  sf::Color		_loginSizeErrColor;
  sf::Color		_highlightColor;
  sf::Color		_startColor;
  ClickableBtn		_menuFields[MAX_NUMBER_OF_FIELDS];
  Editable		_login;
  Editable		_host;
  ClickableBtn		_loginSizeErr;
  ClickableBtn		_startButton;
  ClickableBtn		_connectButton;
  sf::Font		_fieldsFont;
  sf::Font		_loginFont;
  Row			_currentRow;
  bool			_maxLoginSize;
  std::list<s_gameData>	_gamesData;
  
public:
  Menu(int width, int height);
  ~Menu();

  void			initMainView();

private:
  void			initFields();
  void			initColors();
  void			initPlayerColorSelection();
  void			handleMouseClick(sf::Event&);
  void			handleMouseMoved(sf::Event&);
  void			handleLoginEdition(sf::Event&);
  void			handleHostEdition(sf::Event&);
  void			eventHandler();
  void			drawFields();
  void			drawEditable();
  void			drawLoginSizeErr();
  void			changeCurrentRow();
  void			addGame(std::string, unsigned int, std::string);
  //  void			changeCurrentColor(sf::Event&);
  /*std::list<Animation>	addRandomStars();
    void			starDrawer(std::list<Animation>, sf::RenderWindow &);*/
};

#endif /* !MENU_HPP */
