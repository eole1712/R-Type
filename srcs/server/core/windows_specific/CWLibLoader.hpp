#ifndef CWLIBLOADER_HPP_
# define CWLIBLOADER_HPP_

# include <string>
# include "ILibLoader.hpp"

class		CWLibLoader : public ILibLoader
{
private:
  HINSTANCE	_libHandle;
  void*		_externalCreator;
  void*		_externalDestructor;

  CWLibLoader();

public:
  CWLibLoader(std::string libName, std::string creatorName, std::string destructorName);
  virtual ~CWLibLoader();
  CWLibLoader(CWLibLoader const&);
  CWLibLoader&	operator=(CWLibLoader const&);

  virtual void*		getLibHandle() const;
  virtual void*		getExternalCreator() const;
  virtual void*		getExternalDestructor() const;
};

#endif /* !CWLIBLOADER_HPP_ */
