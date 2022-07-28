#ifndef INC_RESOURCES_GRID
#define INC_RESOURCES_GRID

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>
#include "GridItem.h"

class GridResources
{
private:
    SDL_Surface *active_tile = nullptr;
    SDL_Surface *inactive_tile = nullptr;
    std::vector<SDL_Surface*> icons;
    GridResources() {};
public:
    static GridResources *load(std::string path, std::vector<GridItem> items);
    ~GridResources();
    SDL_Surface *getActiveTile();
    SDL_Surface *getInactiveTile();
    SDL_Surface *getIcon(int index);
};

#endif
