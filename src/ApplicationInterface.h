#ifndef INC_APPLICATION_INTERFACE
#define INC_APPLICATION_INTERFACE

class ViewInterface;

enum View {
    MAIN_MENU,
    EMU,
    MAX_VIEWS
};

class ApplicationInterface
{
public:
    virtual void stop() = 0;
    virtual ~ApplicationInterface() {};
    virtual void switchView(ViewInterface *view) = 0;
    virtual ViewInterface *getView(View view) = 0;
};

#endif
