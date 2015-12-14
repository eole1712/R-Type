#include "ClickableBtn.hpp"

ClickableBtn::ClickableBtn(int posX, int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize)
  :_clickableBtn(text, font, characterSize)
{
  _clickableBtn.setPosition(posX, posY);
  _clickableBtn.setColor(color);
}

sf::Text&	ClickableBtn::getClickableBtn()
{
  return _clickableBtn;
}

void		ClickableBtn::setColor(const sf::Color& color)
{
  _clickableBtn.setColor(color);
}
