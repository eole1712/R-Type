#ifndef CLICKABLE_HPP_
# define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class ClickableBtn
{
private:
  sf::Text	_clickableBtn;
  
public:
  ClickableBtn(){};
  ClickableBtn(int posX, int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize = 30);
  ~ClickableBtn() {};

  sf::Text&	getClickableBtn();
  void		setColor(const sf::Color&);
};

#endif /* !CLICKABLE_HPP_*/
