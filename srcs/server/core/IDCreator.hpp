#ifndef IDCreator_hpp
#define IDCreator_hpp

class  IDCreator
{
public:
    IDCreator();
    ~IDCreator();
    
public:
    unsigned int        getNewID();

private:
    unsigned int        _id;
};

#endif /* IDCreator_hpp */
