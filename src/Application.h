#ifndef INC_APPLICATION
#define INC_APPLICATION

#include <SDL/SDL.h>
#include "ApplicationInterface.h"
#include "view/ViewInterface.h"
#include "theme/Theme.h"

class Application: public ApplicationInterface
{
private:
    ViewInterface *views[View::MAX_VIEWS];
    ViewInterface *current_view;
    SDL_Surface *video = nullptr;
    SDL_Surface *screen = nullptr;
    Theme *theme = nullptr;
    bool is_running = false;
    void initScreen();
public:
    Application() {};
    ~Application() {};
    void updateScreen();
    int run();
    void stop();
    void switchView(ViewInterface *view);
    ViewInterface *getView(View view);
};

#endif
