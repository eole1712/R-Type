#include "Error.hpp"

Error::Error(unsigned int posX, unsigned int posY, std::string error, sf::Font& font, sf::Color& color, unsigned int charSize)
  : _posX(posX), _posY(posY), _error(error, font, charSize), _charSize(charSize)
{
  _error.setPosition(_posX, _posY);
  _error.setColor(color);
}

void			Error::render(sf::RenderWindow& window)
{
  window.draw(_error);
}

sf::Text		Error::getError() const
{
  return _error;
}

void			Error::setError(sf::Text const& error)
{
  _error = error;
}

void			Error::setColor(const sf::Color& color)
{
  _error.setColor(color);
}

