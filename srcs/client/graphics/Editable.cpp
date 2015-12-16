#include "Editable.hpp"

Editable::Editable(unsigned int posX, unsigned int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int editableSizeMax, unsigned int characterSize)
  : _posX(posX), _posY(posY), _editable(text, font, characterSize), _editableSizeMax(editableSizeMax), _maxSize(false)
{
  _editable.setPosition(posX, posY);
  _editable.setColor(color);
}

void		Editable::editionHandler(sf::Event const& event)
{
  if (_editable.getString().getSize() <= _editableSizeMax)
    {
      _maxSize = false;
      if (event.text.unicode >= 32 && event.text.unicode <= 126)
	_editable.setString(_editable.getString() + static_cast<char>(event.text.unicode));
    }
  else
    _maxSize = true;
  if (event.text.unicode == 8)
    {
      _editable.setString(std::string(_editable.getString()).substr(0, _editable.getString().getSize()-1));
      _maxSize = false;
    }
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

void		Editable::setPosX(const unsigned int newPosX)
{
  _posX = newPosX;
}

unsigned int	Editable::getPosY() const
{
  return _posY;
}

void		Editable::setPosY(const unsigned int newPosY)
{
  _posY = newPosY;
}

bool		Editable::getMaxSize() const
{
  return _maxSize;
}
