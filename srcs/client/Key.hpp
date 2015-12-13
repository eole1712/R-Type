#ifndef KEY_HPP_
# define KEY_HPP_

#include <map>
#include <SFML/Graphics.hpp>
#include "Time.hpp"

namespace Key
{
  typedef sf::Keyboard::Key	key;
  enum event { PRESS, RELEASE, UNKNOWN };
  typedef std::pair<key, event>	bindKey;
  typedef std::map<key, event>	keyState;

  template <typename T>
  class Bind
  {
    
  public:
    typedef void	(*bindFunct)(Time::stamp tick, keyState & keys, T param);
    typedef std::map<bindKey, bindFunct>	bind;
    
  public:
    Bind(bind b)
      : _bind(b)
    {
    };
    virtual ~Bind(){};
    
  private:
    keyState	_keyState;
    bind	_bind;
    
  public:
    void				process(Time::stamp tick, T param)
    {
      typename keyState::const_iterator	ks;
      
      for (typename bind::const_iterator b = _bind.begin(); b != _bind.end(); b++)
      {
	if ((ks = _keyState.find(b->first.first)) != _keyState.end() && b->first.second == ks->second)
	  b->second(Time::getTimeStamp() - tick, _keyState, param);
      }
    }
    
    event &			operator[](key k)
    {
      return _keyState[k];
    }
  };
}

#endif /* !KEY_HPP_ */
