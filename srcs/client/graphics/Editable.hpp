#ifndef EDITABLE_HPP_
# define EDITABLE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Editable
{
private:
  unsigned int	_posX;
  unsigned int	_posY;
  sf::Text	_editable;
  
public:
  Editable(){};
  Editable(unsigned int posX, unsigned int posY, std::string text, sf::Font & font, sf::Color & color, unsigned int characterSize = 30);
  ~Editable() {};

  sf::Text&	getEditable();
  void		setColor(const sf::Color&);
  unsigned int	getPosX() const;
  void		setPosX(const unsigned int);
  unsigned int	getPosY() const;
  void		setPosY(const unsigned int);
};

#endif /* !EDITABLE_HPP_*/
