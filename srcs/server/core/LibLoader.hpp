#ifndef LIBLOADER_HPP_
# define LIBLOADER_HPP_

# include <string>

class		LibLoader
{
private:
  void*		_libHandle;
  void*		_externalCreator;
  void*		_externalDestructor;

  LibLoader();

public:
  LibLoader(std::string libName, std::string creatorName, std::string destructorName);
  ~LibLoader();
  LibLoader(LibLoader const&);
  LibLoader&	operator=(LibLoader const&);

  void*		getLibHandle() const;
  void*		getExternalCreator() const;
  void*		getExternalDestructor() const;
};

#endif /* !LIBLOADER_HPP_ */
