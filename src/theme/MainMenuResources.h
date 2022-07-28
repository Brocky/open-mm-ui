#ifndef INC_RESOURCES_MAIN_MENU
#define INC_RESOURCES_MAIN_MENU

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

struct MainMenuIcon
{
    SDL_Surface *active = nullptr;
    SDL_Surface *inactive = nullptr;
};

class MainMenuRessources
{
private:
    MainMenuRessources() {};
    MainMenuIcon icons[6];
    MainMenuIcon dot;
    void verifyResources();
    
public:
    static MainMenuRessources *load(std::string path);
    ~MainMenuRessources();
    MainMenuIcon *getIcon(int item);
    MainMenuIcon *getDot();
};

#endif
