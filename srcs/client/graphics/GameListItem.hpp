#ifndef GAMELISTITEM_HPP_
# define GAMELISTITEM_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

class GameListItem
{
private:
  unsigned int		_posX;
  unsigned int		_posY;
  sf::Text		_gameName;
  sf::Text		_playerNumber;
  sf::Text		_daySentence;
  sf::Font		_font;
  sf::Color		_color;
  sf::Color		_highlightColor;
  bool			_isHighlighted;
  bool			_isSelected;
  
public:
  GameListItem(){};
  GameListItem(unsigned int, unsigned int, std::string&, std::string&, std::string&, sf::Font&, sf::Color&, sf::Color& highlightColor);
  ~GameListItem(){};

  sf::Text		getName() const;
  void			setName(const std::string&);
  sf::Text		getPlayerNumber() const;
  void			setPlayerNumber(const unsigned int);
  sf::Text		getDaySentence() const;
  void			setDaySentence(const std::string&);
  bool			getIsSelected() const;
  void			setIsSelected(const bool isSelected);
  void			setColor(const sf::Color&);
  unsigned int		getPosX() const;
  void			setPosX(const unsigned int);
  unsigned int		getPosY() const;
  void			setPosY(const unsigned int);
  void			eventHandler(sf::RenderWindow&, sf::Event&);
  void			handleMouseMoved(sf::RenderWindow&);
  void			handleMouseClick(sf::RenderWindow&);
  void			updatePosition();
};

#endif /* !GAMELISTITEM_HPP_ */
