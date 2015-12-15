#ifndef AUNIT_HPP_
# define AUNIT_HPP_

# include "Animation.hpp"

class  UnitRender
{
public:
  UnitRender();
  ~UnitRender();

protected:
  std::map<std::string, Animation> _sprites;
  
public:
  void		render(sf::RenderWindow & window);
}

#endif /* !AUNIT_HPP_ */
