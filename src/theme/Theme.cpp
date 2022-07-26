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

    short int offset_left = 10;
    short int offset_top = 91;

    SDL_Rect icon_rect = {0, offset_top, ICON_HEIGHT, ICON_WIDTH};

    for (int i = 0; i < 4; i++) {
        icon_rect .x = offset_left + i * ICON_HEIGHT;
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
}

void Theme::drawBackground(SDL_Surface *screen)
{
    // Load common resources if not already present
    if (! this->common_resources) {
        this->common_resources = CommonResources::load(this->path);
    }
    SDL_Rect rect = {0,0,640,480};
    SDL_BlitSurface(this->common_resources->getBackground(), NULL, screen, &rect);
}
