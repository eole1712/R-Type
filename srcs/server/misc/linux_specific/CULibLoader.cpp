#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "CULibLoader.hpp"

CULibLoader::CULibLoader(std::string libName, std::string creatorName, std::string destructorName)
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

CULibLoader::~CULibLoader()
{
  if (dlclose(this->_libHandle) != 0)
    std::cerr << dlerror() << std::endl;
}

CULibLoader::CULibLoader(CULibLoader const& other)
  : _libHandle(other._libHandle), _externalCreator(other._externalCreator),
    _externalDestructor(other._externalDestructor)
{}

CULibLoader&	CULibLoader::operator=(CULibLoader const& other)
{
  if (this != &other)
    {
      this->_libHandle = other._libHandle;
      this->_externalCreator = other._externalCreator;
      this->_externalDestructor = other._externalDestructor;
    }
  return (*this);
}

void*	CULibLoader::getLibHandle() const
{
  return (this->_libHandle);
}

void*	CULibLoader::getExternalCreator() const
{
  return (this->_externalCreator);
}

void*	CULibLoader::getExternalDestructor() const
{
  return (this->_externalDestructor);
}
