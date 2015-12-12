#ifndef MENU_HPP
# define MENU_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Animation.hpp"

#define MAX_NUMBER_OF_FIELDS 3
#define NUMBER_OF_PLAYER_COLOR 4

class Menu
{

  enum Row {
    LOGIN,
    COLOR,
    GAME
  };

  enum PlayerColor {
    BLUE,
    RED,
    YELLOW,
    GREEN
  };
  
private:
  int			_width;
  int			_height;
  sf::Text		_menuFields[MAX_NUMBER_OF_FIELDS];
  sf::Text		_login;
  sf::Text		_loginSizeErr;
  sf::Text		_playerColor[NUMBER_OF_PLAYER_COLOR];
  sf::Text		_startButton;
  sf::Font		_fieldsFont;
  sf::Font		_loginFont;
  sf::Color		_fieldsColor;
  sf::Color		_loginColor;
  sf::Color		_loginSizeErrColor;
  sf::Color		_highlightColor;
  sf::Color		_blueColor;
  sf::Color		_redColor;
  sf::Color		_yellowColor;
  sf::Color		_greenColor;
  sf::Color		_startColor;
  sf::Color		_BRYGColor[NUMBER_OF_PLAYER_COLOR];
  sf::Color		_BRYGhighlight[NUMBER_OF_PLAYER_COLOR];
  Row			_currentRow;
  PlayerColor		_currentPlayerColor;
  bool			_maxLoginSize;
  
public:
  Menu(int width, int height);
  ~Menu();

  void			initMainView();

private:
  void			initFields();
  void			initColors();
  void			initPlayerColorSelection();
  void			handleMouseClick(sf::RenderWindow&, sf::Event&);
  void			handleMouseMoved(sf::RenderWindow&, sf::Event&);
  void			handleLoginEdition(sf::RenderWindow&, sf::Event&);
  void			eventHandler(sf::RenderWindow&);
  void			drawFields(sf::RenderWindow &);
  void			drawLogin(sf::RenderWindow&);
  void			drawLoginSizeErr(sf::RenderWindow&);
  void			changeCurrentRow();
  void			changeCurrentColor(sf::Event&);
  /*std::list<Animation>	addRandomStars();
    void			starDrawer(std::list<Animation>, sf::RenderWindow &);*/
};

#endif /* !MENU_HPP */
