#ifndef KEYBIND_HPP_
# define KEYBIND_HPP_

#include <map>
#include "Time.hpp"

namespace RType
{

template <typename T, typename U>
class KeyBind
{

public:
  enum event { PRESS, RELEASE };
  typedef T	bindKey;
  typedef std::map<bindKey, bool>	keyState;
  typedef void	(*bindFunct)(Time::stamp tick, keyState keys, U param);
  typedef std::map<bindKey, bindFunct>	bind;

public:
  KeyBind(bind b)
    : _bind(b)
  {
  };
  virtual ~KeyBind(){};

private:
  keyState	_keyState;
  bind		_bind;

public:
  void				process(Time::stamp tick, U param) const
  {
    typename keyState::const_iterator	ks;

    for (typename bind::const_iterator b = _bind.begin(); b != _bind.end(); b++)
      {
	if ((ks = _keyState.find(b->first)) != _keyState.end() && ks->second)
	  b->second(RType::Time::getTimeStamp() - tick, _keyState, param);
      }
  }

  bool &			operator[](bindKey key)
  {
    return _keyState[key];
  }
};

}

#endif /* !KEYBIND_HPP_ */
