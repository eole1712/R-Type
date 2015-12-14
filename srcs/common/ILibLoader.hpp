#ifndef LIBLOADER_HPP_
# define LIBLOADER_HPP_

# include <string>

class		ILibLoader
{
public:
  ILibLoader() {}
  virtual ~ILibLoader() {}

  virtual void*		getLibHandle() const = 0;
  virtual void*		getExternalCreator() const = 0;
  virtual void*		getExternalDestructor() const = 0;
};

#endif /* !LIBLOADER_HPP_ */
