#include "GameListItem.hpp"


GameListItem::GameListItem(unsigned int posX, unsigned int posY, std::string const& gameName, std::string& playerNumber, std::string& playerReady, std::string const& daySentence, sf::Font& fieldsFont, sf::Color &color, sf::Color& highlightColor)
  : _posX(posX), _posY(posY), _gameName(gameName, fieldsFont, 21), _playerNumber(playerNumber, fieldsFont, 21), _playerReady(playerReady, fieldsFont, 21), _daySentence(daySentence, fieldsFont, 21), _font(fieldsFont), _color(color), _highlightColor(highlightColor), _isHighlighted(false), _isSelected(false)
{
  std::cout << "player ready : " << playerReady<< std::endl;
  _gameName.setPosition(posX, posY);
  _gameName.setColor(_color);
  _playerNumber.setPosition(posX + 170, posY);
  _playerNumber.setColor(_color);
  _playerReady.setPosition(posX + 190, posY);
  _playerReady.setColor(_color);
}

void			GameListItem::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
  switch (event.type)
    {
    case sf::Event::MouseMoved:
      this->handleMouseMoved(window);
      break;
    case sf::Event::MouseButtonReleased:
      this->handleMouseClick(window);
    default:
      break;
    }
}

void			GameListItem::handleMouseMoved(sf::RenderWindow& window)
{
  sf::Vector2f	mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

  if (sf::Mouse::getPosition(window).x >= _posX && sf::Mouse::getPosition(window).x <= _posX + 170 &&
      sf::Mouse::getPosition(window).y >= _posY && sf::Mouse::getPosition(window).y <= _posY + 21 && _isSelected == false)
    {
      _gameName.setColor(_highlightColor);
      _playerNumber.setColor(_highlightColor);
      _playerReady.setColor(_highlightColor);
      _isHighlighted = true;
    }
  else
    if (_isHighlighted && _isSelected == false)
      {
	_gameName.setColor(_color);
	_playerNumber.setColor(_color);
	_playerReady.setColor(_color);
      }
}

void			GameListItem::handleMouseClick(sf::RenderWindow& window)
{
  if (sf::Mouse::getPosition(window).x >= _posX && sf::Mouse::getPosition(window).x <= _posX + 140  && sf::Mouse::getPosition(window).y >= _posY && sf::Mouse::getPosition(window).y <= _posY + 21)
    {
      _isSelected = true;
    }
}

void			GameListItem::updatePosition()
{
  _gameName.setPosition(sf::Vector2f(_posX, _posY));
  _playerNumber.setPosition(sf::Vector2f(_posX + 170, _posY));
  _playerReady.setPosition(sf::Vector2f(_posX + 190, _posY));
}

sf::Text		GameListItem::getName() const
{
  return _gameName;
}

void			GameListItem::setName(const std::string& gameName)
{
  _gameName.setString(gameName);
}

sf::Text		GameListItem::getPlayerNumber() const
{
  return _playerNumber;
}

void		GameListItem::setPlayerNumber(const unsigned int playerNumber)
{
  std::string	tmp;

  tmp = std::to_string(playerNumber);
  _playerNumber.setString(tmp);
}

sf::Text		GameListItem::getPlayerReady() const
{
  return _playerReady;
}

void		GameListItem::setPlayerReady(const unsigned int playerReady)
{
  std::string	tmp;

  tmp = std::to_string(playerReady);
  _playerReady.setString(tmp);
}

sf::Text	GameListItem::getDaySentence() const
{
  return _daySentence;
}

void		GameListItem::setDaySentence(const std::string& daySentence)
{
  _daySentence.setString(daySentence);
}

bool		GameListItem::getIsSelected() const
{
  return _isSelected;
}

void		GameListItem::setIsSelected(const bool isSelected)
{
  _isSelected = isSelected;
}

void		GameListItem::setColor(const sf::Color& color)
{
  _gameName.setColor(color);
  _playerNumber.setColor(color);
  _gameName.setColor(color);
}

unsigned int	GameListItem::getPosX() const
{
  return _posX;
}

void		GameListItem::setPosX(const unsigned int x)
{
  _posX = x;
  updatePosition();
}

unsigned int	GameListItem::getPosY() const
{
  return _posY;
}

void		GameListItem::setPosY(const unsigned int y)
{
  _posY = y;
  updatePosition();
}
