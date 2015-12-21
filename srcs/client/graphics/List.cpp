#include "List.hpp"
 
List::List(unsigned int posX, unsigned int posY, sf::Font const& listFont, sf::Color const& listColor, sf::Color const& highlightColor)
  : _posX(posX), _posY(posY), _originPosX(posX), _originPosY(posY), _list{}, _iterator(_list.begin()), _font(listFont),
  _color(listColor), _highlightColor(highlightColor),
    _scrollBtn{
      ClickableBtn((posX) * 1.5, (posY), "/\\", _font, _color, 21),
      ClickableBtn((posX) * 1.5, (posY) * 1.6, "\\/", _font, _color, 21)
    }
{
}

void			List::addItem(int id, std::string const& gameName,
				      unsigned int playerNumber, unsigned int playerReady, std::string const& daySentence, bool select)
{
  std::string		playerNumberToString;
  std::string		playerReadyToString;
  std::map<int, GameListItem>::iterator exist;

  
  playerNumberToString = std::to_string(playerNumber);
  playerReadyToString = std::to_string(playerReady);
  if ((exist = _list.find(id)) != _list.end())
    {
      exist->second.setName(gameName);
      exist->second.setPlayerNumber(playerNumber);
      exist->second.setDaySentence(daySentence);
      return ;
    }
  
  GameListItem	gameListItem(_posX, _posY, gameName, playerNumberToString, playerReadyToString, daySentence,
			     _font, _color, _highlightColor);
  _list[id] = gameListItem;
  if (_list.size() == 1)
    {
      _iterator = _list.begin();
      _selected = _iterator;
    }
  else if (select)
    {
      if (_selected != _list.end()) {
	_selected->second.setIsSelected(false);
	_selected->second.setColor(_color);
      }
      _selected = _list.find(id);
      _selected->second.setIsSelected(true);
      _selected->second.setColor(sf::Color(255, 255, 102));
    }
}

void			List::slide(bool up)
{
  if (up && _iterator != _list.begin())
    {
      _iterator--;
      for (std::map<int, GameListItem>::iterator it = _list.begin(); it != _list.end(); it++ )
	{
	  (*it).second.setPosY((*it).second.getPosY() + 30);
	  (*it).second.updatePosition();
	}
    }
  else if (!up && std::distance(_iterator, _list.end()) > 5)
    {
      _iterator++;
      for (std::map<int, GameListItem>::iterator it = _list.begin(); it != _list.end(); it++ )
	{
	  (*it).second.setPosY((*it).second.getPosY() - 30);
	  (*it).second.updatePosition();
	}
    }
}

bool			List::clickHandler(sf::RenderWindow& window, sf::Event& event)
{
  sf::Vector2f		mousePosition(event.mouseMove.x, event.mouseMove.y);
  int			i = 5;
  
  for(std::map<int, GameListItem>::iterator it = _iterator;
      it != _list.end() && i > 0; it++)
    {
      std::cout << (*it).second.getIsSelected() << std::endl;
      i--;
      if ((*it).second.getName().getGlobalBounds().contains(mousePosition) ||
	  (*it).second.getPlayerNumber().getGlobalBounds().contains(mousePosition))
	{
	  if ((*it).second.getIsSelected() == false)
	    {
	      if (_selected != _list.end())
		{
		  _selected->second.setIsSelected(false);
		  _selected->second.setColor(_color);
		}
	      (*it).second.setIsSelected(true);
	      (*it).second.setColor(sf::Color(255, 255, 102));
	      _selected = it;
	    }
	  else
	    return true;	  
	}
    }
  return false;
}

void			List::mouseMovedHandler(sf::RenderWindow& window, sf::Event& event)
{
  int			i = 5;
  sf::Vector2f		mousePosition(event.mouseMove.x, event.mouseMove.y);
  
  for(std::map<int, GameListItem>::iterator it = _iterator;
      it != _list.end() && i > 0; it++)
    {
      i--;
      (*it).second.eventHandler(window, event);
    }
  if (_list.size() > 5)
    {
      if (_scrollBtn[0].getClickableBtn().getGlobalBounds().contains(mousePosition))
	_scrollBtn[0].setColor(_highlightColor);
      else
	_scrollBtn[0].setColor(_color);
      if (_scrollBtn[1].getClickableBtn().getGlobalBounds().contains(mousePosition))
	_scrollBtn[1].setColor(_highlightColor);
      else
	_scrollBtn[1].setColor(_color);
    }
}

void			List::scrollHandler(sf::RenderWindow& window, sf::Event& event)
{
  sf::Vector2f		mousePosition(event.mouseMove.x, event.mouseMove.y);
  
  if (_list.size() >= 6 && _scrollBtn[0].getClickableBtn().getGlobalBounds().contains(mousePosition))
    this->slide(true);
  if (_list.size() >= 6 && _scrollBtn[1].getClickableBtn().getGlobalBounds().contains(mousePosition))
    this->slide(false);
}

void			List::render(sf::RenderWindow& window)
{
  int		i = 0;
  std::string	test;

  for (std::map<int, GameListItem>::iterator it = _iterator;
       it != _list.end() && i < 5; it++)
    {
      (*it).second.setPosY(_posY + 30 * i);
      window.draw((*it).second.getName());
      window.draw((*it).second.getPlayerNumber());
      window.draw((*it).second.getPlayerReady());
      i++;
    }
  if (_list.size() >= 6)
    {
      window.draw(_scrollBtn[0].getClickableBtn());
      window.draw(_scrollBtn[1].getClickableBtn());
    }
}

void			List::clean()
{
  std::cout << "clean" << std::endl;
  _posX = _originPosX;
  _posY = _originPosY;
  _list.clear();
  _iterator = _list.end();
}

std::map<int, GameListItem>const&	List::getList() const
{
  return _list;
}

std::string		List::getCurrentItem() const
{
  if (_selected == _list.end())
    return std::string("");
  return (std::string)(*_selected).second.getName().getString();
}

void			List::setFont(sf::Font const& listFont)
{
  _font = listFont;
}

unsigned int		List::getPosX() const
{
  return _posX;
}

void			List::setPosX(unsigned int x)
{
  _posX = x;
}

unsigned int		List::getPosY() const
{
  return _posY;
}

void			List::setPosY(unsigned int y)
{
  _posY = y;
}

