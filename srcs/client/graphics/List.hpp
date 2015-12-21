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
  std::map<int, GameListItem>		_list;
  std::map<int, GameListItem>::iterator	_iterator;
  std::map<int, GameListItem>::iterator	_selected;
  sf::Font				_font;
  sf::Color				_color;
  sf::Color				_highlightColor;
  ClickableBtn				_scrollBtn[2];
  
public:
  
  List(unsigned int, unsigned int, sf::Font const&, sf::Color const&, sf::Color const&);
  List();
  ~List(){};

  unsigned int				getPosX() const;
  void					setPosX(unsigned int x);
  unsigned int				getPosY() const;
  void					setPosY(unsigned int y);
  void					addItem(int, std::string const&, unsigned int, unsigned int, std::string const&, bool, bool);
  void					slide(bool up);
  bool					clickHandler(sf::Event&);
  void					mouseMovedHandler(sf::RenderWindow &, sf::Event&);
  void					scrollHandler(sf::Event&);
  void					render(sf::RenderWindow&);

  void					refresh();
  void					clean();

  std::map<int, GameListItem>const&		getList() const;
  std::string				getCurrentItem() const;
  int					getCurrentItemId() const;

  void					setFont(sf::Font const&);
};

#endif /* !LIST_HPP_ */
