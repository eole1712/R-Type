#ifndef MESSAGE_HPP_
# define MESSAGE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Message
{
private:
  unsigned int		_posX;
  unsigned int		_posY;
  sf::Text		_message;
  
public:
  Message(unsigned int posX, unsigned int posY, std::string message, sf::Font& font,
	  sf::Color color, unsigned int charSize = 21);
  Message(){};
  ~Message(){};

  void			render(sf::RenderWindow&);
  sf::Text		getMessage() const;
  void			setMessage(sf::Text const&);
  void			setColor(sf::Color const&);
};

#endif /* !ERROR_HPP_ */
