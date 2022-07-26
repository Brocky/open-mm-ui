#ifndef INC_APPLICATION
#define INC_APPLICATION

#include <SDL/SDL.h>
#include "ApplicationInterface.h"
#include "view/ViewInterface.h"

class Application: public ApplicationInterface
{
private:
    ViewInterface *current_view;
    SDL_Surface *video;
    SDL_Surface *screen;
    bool is_running = false;
    void initScreen();
public:
    Application() {};
    ~Application() {};
    void updateScreen();
    int run();
    void stop();
};

#endif
