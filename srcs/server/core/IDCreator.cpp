#include "IDCreator.hpp"

IDCreator::IDCreator()
: _id(5)
{
}

IDCreator::~IDCreator()
{
}

unsigned int        IDCreator::getNewID()
{
    unsigned int    id = _id;
    _id++;
    
    return id;
}