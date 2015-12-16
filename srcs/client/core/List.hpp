#ifndef LIST_HPP_
# define LIST_HPP_

#include <iostream>
#include <list>
#include "GameListItem.hpp"
#include "ClickableBtn.hpp"

class List
{
private:

  unsigned int				_posX;
  unsigned int				_posY;
  std::list<GameListItem>		_gameList;
  std::list<GameListItem>::iterator	_gameListIt;
  sf::Font				_listFont;
  sf::Color				_listColor;
  sf::Color				_highlightColor;
  unsigned int				_currentGameNumber;
  ClickableBtn				_scrollBtn[2];
  std::string				_currentGameName;
  
public:
  
  List(unsigned int, unsigned int, sf::Font const&, sf::Color const&, sf::Color const&);
  List();
  ~List(){};

  void					addGame(std::string const&, unsigned int, std::string const&);
  void					slide(bool up);
  void					clickHandler(sf::RenderWindow&, sf::Event&);
  void					mouseMovedHandler(sf::RenderWindow&, sf::Event&);
  void					scrollHandler(sf::RenderWindow&);
  void					drawGameList(sf::RenderWindow&);
  void					refresh();
  void					clean();
  std::list<GameListItem>		getGameList() const;
  std::string				getCurrentGameName() const;
  void					setCurrentGameName(std::string const&);
  void					setFont(sf::Font const&);
};

#endif /* !LIST_HPP_ */
