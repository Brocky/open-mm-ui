#ifndef INC_VIEW_INTERFACE
#define INC_VIEW_INTERFACE

#include "../ApplicationInterface.h"

class ViewInterface
{
public:
    virtual void onRight() = 0;
    virtual void onLeft() = 0;
    virtual void onUp() = 0;
    virtual void onDown() = 0;
    virtual void onAccept() = 0;
    virtual void onCancel(ApplicationInterface *app) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual ~ViewInterface() {};
};
#endif
