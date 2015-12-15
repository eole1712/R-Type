#include "ClickableBtn.hpp"

ClickableBtn::ClickableBtn(unsigned int posX, unsigned int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize)
  : _posX(posX), _posY(posY), _clickableBtn(text, font, characterSize)
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

unsigned int	ClickableBtn::getPosX() const
{
  return _posX;
}

void		ClickableBtn::setPosX(unsigned int newPosX)
{
  _posX = newPosX;
}

unsigned int	ClickableBtn::getPosY() const
{
  return _posY;
}

void		ClickableBtn::setPosY(unsigned int newPosY)
{
  _posY = newPosY;
}
