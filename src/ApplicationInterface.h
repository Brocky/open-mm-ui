#ifndef INC_APPLICATION_INTERFACE
#define INC_APPLICATION_INTERFACE

class ApplicationInterface
{
public:
    virtual void stop() = 0;
    virtual ~ApplicationInterface() {};
};

#endif
