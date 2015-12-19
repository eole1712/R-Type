#ifndef LIST_HPP_
# define LIST_HPP_

#include <list>
#include "GameListItem.hpp"
#include "ClickableBtn.hpp"

class List
{
private:

  unsigned int				_posX;
  unsigned int				_posY;
  unsigned int				_originPosX;
  unsigned int				_originPosY;
  std::list<GameListItem>		_list;
  std::list<GameListItem>::iterator	_iterator;
  sf::Font				_font;
  sf::Color				_color;
  sf::Color				_highlightColor;
  unsigned int				_currentIndex;
  ClickableBtn				_scrollBtn[2];
  
public:
  
  List(unsigned int, unsigned int, sf::Font const&, sf::Color const&, sf::Color const&);
  List();
  ~List(){};

  unsigned int				getPosX() const;
  void					setPosX(unsigned int x);
  unsigned int				getPosY() const;
  void					setPosY(unsigned int y);
  void					addItem(std::string const&, unsigned int, std::string const&);
  void					slide(bool up);
  void					clickHandler(sf::RenderWindow&, sf::Event&);
  void					mouseMovedHandler(sf::RenderWindow&, sf::Event&);
  void					scrollHandler(sf::RenderWindow&);
  void					render(sf::RenderWindow&);

  void					refresh();
  void					clean();

  std::list<GameListItem>		getList() const;
  std::string				getCurrentItem() const;

  void					setFont(sf::Font const&);
};

#endif /* !LIST_HPP_ */
