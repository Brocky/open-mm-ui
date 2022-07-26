#ifndef INC_VIEW_MAIN_MENU
#define INC_VIEW_MAIN_MENU

#include <SDL/SDL.h>
#include "ViewInterface.h"
#include "../theme/Theme.h"

enum MenuItem {
    RECENT,
    FAVORITES,
    GAMES,
    EXPERT,
    APP,
    SETTINGS,
    num_values
};

class MainMenu: public ViewInterface
{
private:
    MenuItem current_item = MenuItem::RECENT;
    MenuItem first_item = MenuItem::RECENT;
    SDL_Surface *screen;
    Theme *theme;
    bool active = false;
public:
    MainMenu(SDL_Surface *screen, Theme *theme);
    ~MainMenu();
    void onRight();
    void onLeft();
    void onUp() {};
    void onDown() {};
    void onAccept() {};
    void onCancel() {};
    void activate();
    void deactivate();
    MenuItem getFirstDisplayedItem();
};

#endif
