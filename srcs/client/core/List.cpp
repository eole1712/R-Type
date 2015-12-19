#include "List.hpp"

List::List(unsigned int posX, unsigned int posY, sf::Font const& listFont, sf::Color const& listColor, sf::Color const& highlightColor)
  : _posX(posX), _posY(posY), _listFont(listFont), _listColor(listColor), _highlightColor(highlightColor), _currentGameNumber(0),
    _scrollBtn{ClickableBtn((posX) * 1.5, (posY), "/\\", _listFont, _listColor, 21), ClickableBtn((posX) * 1.5, (posY) * 1.6, "\\/", _listFont, _listColor, 21)}
{

}

void			List::addGame(std::string const& gameName, unsigned int playerNumber,
				      std::string const& daySentence)
{
  std::string		playerNumberToString;

  playerNumberToString = std::to_string(playerNumber);
  GameListItem	gameListItem(_posX, _posY + (30 * _currentGameNumber), gameName,
			     playerNumberToString, daySentence, _listFont, _listColor, _highlightColor);
  _gameList.push_back(gameListItem);
  if (_gameList.size() == 1)
    _gameListIt = _gameList.begin();
  _currentGameNumber += 1;
}

void			List::slide(bool up)
{
  if (up == true && _gameListIt != _gameList.begin())
	{
	  _gameListIt--;
	  for (std::list<GameListItem>::iterator it = _gameList.begin(); it != _gameList.end(); it++ )
	    {
	      (*it).setPosY((*it).getPosY() + 30);
	      (*it).updatePosition();
	    }
	}
  else if (up == false && std::distance(_gameListIt, _gameList.end()) > 5)
    {
      // std::cout << "what to print in else" << std::endl;
      _gameListIt++;
      for (std::list<GameListItem>::iterator it = _gameList.begin(); it != _gameList.end(); it++ )
	{
	  (*it).setPosY((*it).getPosY() - 30);
	  (*it).updatePosition();
	}
    }
}

void			List::clickHandler(sf::RenderWindow& window, sf::Event& event)
{
  int			i = 5;
  
  for(std::list<GameListItem>::iterator it = _gameListIt;
      it != _gameList.end() && i > 0; it++)
    {
      i--;
      if ((*it).getIsSelected() == true)
	{
	  (*it).setIsSelected(false);
	  (*it).setColor(_listColor);
	}
      if (sf::Mouse::getPosition(window).x >= (*it).getPosX() && sf::Mouse::getPosition(window).x <= (*it).getPosX() + 140
	  && sf::Mouse::getPosition(window).y >= (*it).getPosY() && sf::Mouse::getPosition(window).y <= (*it).getPosY() + 21)
	{
	  (*it).setIsSelected(true);
	  //std::string name = (*it).getName().getString();
	  (*it).setColor(sf::Color(255, 255, 102));
	  _currentGameName = (std::string) (*it).getName().getString();
	  //	      _client->selectGame((*it).getName().getString());
	}
      (*it).eventHandler(window, event);
    }
}

void			List::mouseMovedHandler(sf::RenderWindow& window, sf::Event& event)
{
  int			i = 5;
  sf::Vector2f		mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
  
  for(std::list<GameListItem>::iterator it = _gameListIt;
      it != _gameList.end() && i > 0; it++)
    {
      i--;
      (*it).eventHandler(window, event);
    }
  if (_gameList.size() > 5)
    {
      if (_scrollBtn[0].getClickableBtn().getGlobalBounds().contains(mousePosition))
	_scrollBtn[0].setColor(_highlightColor);
      else
	_scrollBtn[0].setColor(_listColor);
      if (_scrollBtn[1].getClickableBtn().getGlobalBounds().contains(mousePosition))
	_scrollBtn[1].setColor(_highlightColor);
      else
	_scrollBtn[1].setColor(_listColor);
    }
}

void			List::scrollHandler(sf::RenderWindow& window)
{
  sf::Vector2f		mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
  
  if (_gameList.size() >= 6 && _scrollBtn[0].getClickableBtn().getGlobalBounds().contains(mousePosition))
    this->slide(true);
  if (_gameList.size() >= 6 && _scrollBtn[1].getClickableBtn().getGlobalBounds().contains(mousePosition))
    this->slide(false);
}

void			List::drawGameList(sf::RenderWindow& window)
{
  int		i = 5;
  std::string	test;
  
  for (std::list<GameListItem>::iterator it = _gameListIt;
       it != _gameList.end() && i > 0; it++)
    {
      i--;
      test = (std::string) (*it).getName().getString();
      window.draw((*it).getName());
      window.draw((*it).getPlayerNumber());
    }
  if (_gameList.size() >= 6)
    {
      window.draw(_scrollBtn[0].getClickableBtn());
      window.draw(_scrollBtn[1].getClickableBtn());
    }
}

void			List::clean()
{
  _gameList = {};
  _currentGameName = "";
}

std::list<GameListItem>	List::getGameList() const
{
  return _gameList;
}

std::string		List::getCurrentGameName() const
{
  return _currentGameName;
}

void			List::setCurrentGameName(std::string const& currentGameName)
{
  _currentGameName = currentGameName;
}

void			List::setFont(sf::Font const& listFont)
{
  _listFont = listFont;
}
