#ifndef INC_RESOURCES_MAIN_MENU
#define INC_RESOURCES_MAIN_MENU

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

struct MainMenuIcon
{
    SDL_Surface *active;
    SDL_Surface *inactive;
};

class MainMenuRessources
{
private:
    MainMenuRessources() {};
    MainMenuIcon icons[6];
    void verifyIcons();
    
public:
    static MainMenuRessources *load(std::string path);
    ~MainMenuRessources();
    MainMenuIcon *getIcon(int item);
};

#endif
