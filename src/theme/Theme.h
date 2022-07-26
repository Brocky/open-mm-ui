#ifndef INC_THEME
#define INC_THEME

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <string>
#include <optional>
#include "GridItem.h"
#include "MainMenuResources.h"
#include "CommonResources.h"
#include "GridResources.h"

struct FontStyle
{
    TTF_Font *face;
    int size;
    SDL_Color color;
};

class Theme
{
private:
    std::string path;
    MainMenuRessources *main_menu_resources = nullptr;
    CommonResources *common_resources = nullptr;
    GridResources *grid_resources = nullptr;
    
    void drawBackground(SDL_Surface *screen);
    void drawFrame(SDL_Surface *screen);
    CommonResources *getCommonRessources();

public:
    Theme(std::string path);
    ~Theme() {};
    void drawMainMenu(SDL_Surface *screen, int active_item, int first_item);
    void drawList(SDL_Surface *screen, std::string title, std::string items[], int active_item);
    void drawGrid(SDL_Surface *screen, std::vector<GridItem> items, int active_item);
    void freeMainMenuResources();
    void freeGridResources();
};

#endif
