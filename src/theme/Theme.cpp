#include "Theme.h"

#define ICON_HEIGHT 156
#define ICON_WIDTH 278

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

    // draw visible icons
    short int offset_left = 10;
    short int offset_top = 91;

    SDL_Rect icon_rect = {0, offset_top, ICON_HEIGHT, ICON_WIDTH};
    for (int i = 0; i < 4; i++) {
        icon_rect.x = offset_left + i * ICON_HEIGHT;
        int current_item = first_item + i;
        MainMenuIcon *icon = this->main_menu_resources->getIcon(current_item);
        
        SDL_Surface *icon_img;
        if (active_item == current_item) {
            icon_img = icon->active;
        } else {
            icon_img = icon->inactive;
        }

        // Render to screen
        SDL_BlitSurface(icon_img, NULL, screen, &icon_rect);
    }

    // draw dots giving menu overview
    offset_left = 276;
    SDL_Rect dot_rect = {0, 388, 10, 10};
    MainMenuIcon *dot = this->main_menu_resources->getDot();
    for (int i = 0; i < 6; i++) {
        dot_rect.x = offset_left + i * 14;
        SDL_Surface *img;
        if (i == active_item) {
            img = dot->active;
        } else {
            img = dot->inactive;
        }

        SDL_BlitSurface(img, NULL, screen, &dot_rect);
    }

    this->drawFrame(screen);
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
