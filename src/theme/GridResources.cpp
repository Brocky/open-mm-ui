#include "GridResources.h"

GridResources* GridResources::load(std::string path, std::vector<GridItem> items)
{
    GridResources* self = new GridResources();

    self->active_tile = IMG_Load((path + "skin/bg-game-item-f.png").c_str());
    self->inactive_tile = IMG_Load((path + "skin/bg-game-item-n.png").c_str());

    for(std::size_t i = 0; i < items.size(); i++) {
        self->icons.push_back(IMG_Load(items.at(i).icon_path.c_str()));
    }

    return self;
}

SDL_Surface *GridResources::getActiveTile()
{
    return this->active_tile;
}

SDL_Surface *GridResources::getInactiveTile()
{
    return this->inactive_tile;
}

SDL_Surface *GridResources::getIcon(int index)
{
    return this->icons.at(index);
}

GridResources::~GridResources()
{
    SDL_FreeSurface(this->active_tile);
    SDL_FreeSurface(this->inactive_tile);

    for(SDL_Surface *icon: this->icons) {
        SDL_FreeSurface(icon);
    }

    this->icons.clear();
}
