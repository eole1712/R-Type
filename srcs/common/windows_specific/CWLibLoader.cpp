#include <iostream>
#include "CWLibLoader.hpp"

CWLibLoader::CWLibLoader(std::string libName, std::string creatorName, std::string destructorName)
{
  if ((this->_libHandle = LoadLibrary(TEXT(libName.c_str()))) == NULL)
    {
      std::cerr << GetLastError() << std::endl;
      exit(EXIT_FAILURE);
    }
  if ((this->_externalCreator = GetProcAddress(this->_libHandle, TEXT(creatorName.c_str()))) == NULL)
    {
      std::cerr << GetLastError() << std::endl;
      exit(EXIT_FAILURE);
    }
  if ((this->_externalDestructor = GetProcAddress(this->_libHandle,
						  TEXT(destructorName.c_str()))) == NULL)
    {
      std::cerr << GetLastError() << std::endl;
      exit(EXIT_FAILURE);
    }
}

CWLibLoader::~CWLibLoader()
{
  if (FreeLibrary(this->_libHandle) != 0)
    std::cerr << GetLastError() << std::endl;
}

CWLibLoader::CWLibLoader(CWLibLoader const& other)
  : _libHandle(other._libHandle), _externalCreator(other._externalCreator),
    _externalDestructor(other._externalDestructor)
{}

CWLibLoader&	CWLibLoader::operator=(CWLibLoader const& other)
{
  if (this != &other)
    {
      this->_libHandle = other._libHandle;
      this->_externalCreator = other._externalCreator;
      this->_externalDestructor = other._externalDestructor;
    }
  return (*this);
}

void*	CWLibLoader::getLibHandle() const
{
  return (this->_libHandle);
}

void*	CWLibLoader::getExternalCreator() const
{
  return (this->_externalCreator);
}

void*	CWLibLoader::getExternalDestructor() const
{
  return (this->_externalDestructor);
}
