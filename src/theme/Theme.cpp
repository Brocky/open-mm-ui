#include <math.h>
#include "Theme.h"

#define MAIN_MENU_ICON_WIDTH 156
#define MAIN_MENU_ICON_HEIGHT 278
#define MAIN_MENU_ICON_OFFSET_LEFT 10
#define MAIN_MENU_ICON_OFFSET_TOP 91

#define MAIN_MENU_DOT_HEIGHT 10
#define MAIN_MENU_DOT_WIDTH 10
#define MAIN_MENU_DOT_OFFSET_LEFT 276
#define MAIN_MENU_DOT_OFFSET_TOP 388

Theme::Theme(std::string path)
{
    this->path = path;
    this->main_menu_resources = nullptr;
}

void Theme::drawMainMenu(SDL_Surface *screen, int active_item, int first_item)
{
    this->drawBackground(screen);

    // Load menue resources if not already present
    if (! this->main_menu_resources) {
        this->main_menu_resources = MainMenuRessources::load(this->path);
    }

    SDL_Rect icon_rect = {
        0,
        MAIN_MENU_ICON_OFFSET_TOP,
        MAIN_MENU_ICON_WIDTH,
        MAIN_MENU_ICON_HEIGHT
    };

    // draw visible icons
    for (int i = 0; i < 4; i++) {
        icon_rect.x = MAIN_MENU_ICON_OFFSET_LEFT + i * icon_rect.h;
        int current_item = first_item + i;
        MainMenuIcon *icon = this->main_menu_resources->getIcon(current_item);
        
        if (active_item == current_item) {
            SDL_BlitSurface(icon->active, NULL, screen, &icon_rect);
        } else {
            SDL_BlitSurface(icon->inactive, NULL, screen, &icon_rect);
        }
    }

    // draw dots giving menu overview
    SDL_Rect dot_rect = {0, MAIN_MENU_DOT_OFFSET_TOP, MAIN_MENU_DOT_WIDTH, MAIN_MENU_ICON_HEIGHT};
    MainMenuIcon *dot = this->main_menu_resources->getDot();
    for (int i = 0; i < 6; i++) {
        dot_rect.x = MAIN_MENU_DOT_OFFSET_LEFT + i * 14;
        if (i == active_item) {
            SDL_BlitSurface(dot->active, NULL, screen, &dot_rect);
        } else {
            SDL_BlitSurface(dot->inactive, NULL, screen, &dot_rect);
        }
    }

    this->drawFrame(screen);
}

void Theme::drawGrid(SDL_Surface *screen, std::vector<GridItem> items, int active_item)
{
    // calculate number of pages and current page
    unsigned int total_pages = ceil(items.size() / 8.0f);
    unsigned int current_page = active_item / 8;

    this->drawBackground(screen);

    if (!this->grid_resources) {
        this->grid_resources = GridResources::load(this->path, items);
    }

    // prepare layout
    int offset_top  = 60;
    int offset_left = 10;
    int row_spacing = 1;
    int col_spacing = 1;

    SDL_Rect cell_rect = {0, 0, 154, 170};
    SDL_Rect icon_rect = {0, 0, 120, 130};

    // render tiles
    for(int i = 0; i < 8; i++) {

        int item_index = current_page * 8 + i;
        int row = i / 4;
        int col = i - row * 4;

        // position and render background
        cell_rect.x = offset_left + col * cell_rect.w + row_spacing;
        cell_rect.y = offset_top + row * cell_rect.h + col_spacing; 
        if (item_index == active_item) {
            SDL_BlitSurface(this->grid_resources->getActiveTile(), NULL, screen, &cell_rect);
        } else {
            SDL_BlitSurface(this->grid_resources->getInactiveTile(), NULL, screen, &cell_rect);
        }

        // position and render icon
        icon_rect.x = cell_rect.x + 17;
        icon_rect.y = cell_rect.y;
        SDL_BlitSurface(this->grid_resources->getIcon(item_index), NULL, screen, &icon_rect);
    }
}

void Theme::drawBackground(SDL_Surface *screen)
{
    SDL_Rect rect = {0,0,640,480};
    SDL_BlitSurface(this->getCommonRessources()->getBackground(), NULL, screen, &rect);
}

void Theme::drawFrame(SDL_Surface *screen)
{
    SDL_Rect rect_top = {0,0,640,60};
    SDL_Rect rect_bottom = {0,420,640,60};
    
    SDL_BlitSurface(this->getCommonRessources()->getHeader(), NULL, screen, &rect_top);
    SDL_BlitSurface(this->getCommonRessources()->getFooter(), NULL, screen, &rect_bottom);
}

CommonResources *Theme::getCommonRessources()
{
    // Load common resources if not already present
    if (! this->common_resources) {
        this->common_resources = CommonResources::load(this->path);
    }
    return this->common_resources;
}

void Theme::freeGridResources()
{
    if (!this->grid_resources) {
        return;
    }
    delete this->grid_resources;
    this->grid_resources = NULL;
}

void Theme::freeMainMenuResources()
{
    if (!this->main_menu_resources) {
        return;
    }
    delete this->main_menu_resources;
    this->main_menu_resources = NULL;
}
