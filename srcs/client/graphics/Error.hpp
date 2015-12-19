#ifndef ERROR_HPP_
# define ERROR_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Error
{
private:
  unsigned int		_posX;
  unsigned int		_posY;
  sf::Text		_error;
  unsigned int		_charSize;
  
public:
  Error(unsigned int posX, unsigned int posY, std::string error, sf::Font& font,
	sf::Color& color, unsigned int charSize);
  Error(){};
  ~Error(){};

  void			render(sf::RenderWindow&);
 sf::Text		getError() const;
  void			setError(sf::Text const&);
  void			setColor(sf::Color const&);
};

#endif /* !ERROR_HPP_ */
