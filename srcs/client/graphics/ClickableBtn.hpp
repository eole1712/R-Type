#ifndef CLICKABLE_HPP_
# define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class ClickableBtn
{
private:
  unsigned int	_posX;
  unsigned int	_posY;
  sf::Text	_clickableBtn;
  
public:
  ClickableBtn(){};
  ClickableBtn(unsigned int posX, unsigned int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize = 30);
  ~ClickableBtn() {};

  sf::Text&	getClickableBtn();
  void		setColor(const sf::Color&);
  unsigned int	getPosX() const;
  void		setPosX(unsigned int);
  unsigned int	getPosY() const;
  void		setPosY(unsigned int);
};

#endif /* !CLICKABLE_HPP_*/
