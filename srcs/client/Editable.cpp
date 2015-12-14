#include "Editable.hpp"

Editable::Editable(unsigned int posX, unsigned int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize)
  : _posX(posX), _posY(posY), _editable(text, font, characterSize)
{
  _editable.setPosition(posX, posY);
  _editable.setColor(color);
}

sf::Text&	Editable::getEditable()
{
  return _editable;
}

void		Editable::setColor(const sf::Color& color)
{
  _editable.setColor(color);
}

unsigned int	Editable::getPosX() const
{
  return _posX;
}

void		Editable::setPosX(unsigned int newPosX)
{
  _posX = newPosX;
}

unsigned int	Editable::getPosY() const
{
  return _posY;
}

void		Editable::setPosY(unsigned int newPosY)
{
  _posY = newPosY;
}
