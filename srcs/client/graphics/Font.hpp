#ifndef FONT_HPP
# define FONT_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Font : public sf::Font
{
public:
  Font(std::string const & fontFile);
  virtual ~Font();
};

#endif /* !FONT_HPP */
