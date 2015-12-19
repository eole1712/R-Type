#include <iostream>
#include "Font.hpp"

Font::Font(std::string const & fontFile)
  : sf::Font()
{
  if (!this->loadFromFile(fontFile))
    std::cerr << "Error: opening font file \"" << fontFile << "\"" << std::endl;
}

Font::~Font()
{
}
