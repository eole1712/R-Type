#include "Message.hpp"

Message::Message(unsigned int posX, unsigned int posY, std::string message, sf::Font& font, sf::Color color, unsigned int charSize)
  : _posX(posX), _posY(posY), _message(message, font, charSize)
{
  _message.setPosition(_posX, _posY);
  _message.setColor(color);
}

void			Message::render(sf::RenderWindow& window)
{
  window.draw(_message);
}

sf::Text		Message::getMessage() const
{
  return _message;
}

void			Message::setMessage(sf::Text const& message)
{
  _message = message;
}

void			Message::setColor(const sf::Color& color)
{
  _message.setColor(color);
}
