#ifndef CULIBLOADER_HPP_
# define CULIBLOADER_HPP_

# include <string>
# include "ILibLoader.hpp"

class		CULibLoader : public ILibLoader
{
private:
  void*		_libHandle;
  void*		_externalCreator;
  void*		_externalDestructor;

  CULibLoader();

public:
  CULibLoader(std::string libName, std::string creatorName, std::string destructorName);
  virtual ~CULibLoader();
  CULibLoader(CULibLoader const&);
  CULibLoader&	operator=(CULibLoader const&);

  virtual void*		getLibHandle() const;
  virtual void*		getExternalCreator() const;
  virtual void*		getExternalDestructor() const;
};

#endif /* !CULIBLOADER_HPP_ */
