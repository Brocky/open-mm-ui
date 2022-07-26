#ifndef INC_VIEW_MAIN_MENU
#define INC_VIEW_MAIN_MENU

#include <SDL/SDL.h>
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

class MainMenu
{
private:
    MenuItem current_item = MenuItem::RECENT;
    MenuItem first_item = MenuItem::RECENT;
    SDL_Surface *screen;
    Theme *theme;

public:
    MainMenu(SDL_Surface *screen, Theme *theme);
    ~MainMenu() {};
    void onRight();
    void onLeft();
    MenuItem getFirstDisplayedItem();
};

#endif
