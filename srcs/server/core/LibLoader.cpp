#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "LibLoader.hpp"

LibLoader::LibLoader(std::string libName, std::string creatorName, std::string destructorName)
{
  if ((this->_libHandle = dlopen(libName.c_str(), RTLD_LAZY)) == NULL)
    {
      std::cerr << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }
  if ((this->_externalCreator = dlsym(this->_libHandle, creatorName.c_str())) == NULL)
    {
      std::cerr << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }
  if ((this->_externalDestructor = dlsym(this->_libHandle, destructorName.c_str())) == NULL)
    {
      std::cerr << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }
}

LibLoader::~LibLoader()
{
  if (dlclose(this->_libHandle) != 0)
    std::cerr << dlerror() << std::endl;
}

LibLoader::LibLoader(LibLoader const& other)
  : _libHandle(other._libHandle), _externalCreator(other._externalCreator),
    _externalDestructor(other._externalDestructor)
{}

LibLoader&	LibLoader::operator=(LibLoader const& other)
{
  if (this != &other)
    {
      this->_libHandle = other._libHandle;
      this->_externalCreator = other._externalCreator;
      this->_externalDestructor = other._externalDestructor;
    }
  return (*this);
}

void*	LibLoader::getLibHandle() const
{
  return (this->_libHandle);
}

void*	LibLoader::getExternalCreator() const
{
  return (this->_externalCreator);
}

void*	LibLoader::getExternalDestructor() const
{
  return (this->_externalDestructor);
}
