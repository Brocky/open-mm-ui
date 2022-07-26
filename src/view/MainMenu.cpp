#include "MainMenu.h"

MainMenu::MainMenu(SDL_Surface *screen, Theme *theme)
{
    this->screen = screen;
    this->theme = theme;
}

void MainMenu::onRight()
{
    if (this->current_item < MenuItem::num_values - 1) {
        int next_item = static_cast<int>(this->current_item) + 1;
        this->current_item = static_cast<MenuItem>(next_item);

        if (next_item > 3) {
            this->first_item = static_cast<MenuItem>(static_cast<int>(this->first_item) + 1);
        }

        this->theme->drawMainMenu(this->screen, this->current_item, this->first_item);
    }
}

void MainMenu::onLeft()
{
    if (this->current_item > 0) {
        int prev_item = static_cast<int>(this->current_item) - 1;
        this->current_item = static_cast<MenuItem>(prev_item);

        if (prev_item < this->first_item) {
            this->first_item = static_cast<MenuItem>(prev_item);
        }

        this->theme->drawMainMenu(this->screen, this->current_item, this->first_item);
    }
}

void MainMenu::activate()
{
    this->active = true;
    this->theme->drawMainMenu(this->screen, this->current_item, this->first_item);
}

void MainMenu::deactivate()
{
    this->active = false;
    this->theme->freeMainMenuResources();
}

MenuItem MainMenu::getFirstDisplayedItem()
{
    return this->first_item;
}

MainMenu::~MainMenu()
{
    this->deactivate();
}
