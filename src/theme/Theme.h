#ifndef INC_THEME
#define INC_THEME

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <optional>
#include "MainMenuResources.h"
#include "CommonResources.h"

struct FontStyle
{
    TTF_Font *face;
    int size;
    SDL_Color color;
};

struct GridItem
{
    std::string icon_path;
    std::string title;
};

class Theme
{
private:
    std::string path;
    MainMenuRessources *main_menu_resources;
    CommonResources *common_resources;
    void drawBackground(SDL_Surface *screen);

public:
    Theme(std::string path);
    ~Theme() {};
    void drawMainMenu(SDL_Surface *screen, int active_item, int first_item);
    void drawList(SDL_Surface *screen, std::string title, std::string items[], int active_item);
    void drawGrid(SDL_Surface *screen, GridItem items[], int active_item);
};

#endif
