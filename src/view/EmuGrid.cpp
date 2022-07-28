#include <string.h>
#include <filesystem>
#include "EmuGrid.h"
namespace fs = std::filesystem;

const std::string emu_path = "/mnt/SDCARD/Emu";

void EmuGrid::buildIndex()
{
    for (const auto &entry : fs::directory_iterator(emu_path)) {
        if (!entry.is_directory()) {
            continue;
        }
        std::string conf_path = entry.path().string() + "config.json";
        Emu *emu = new Emu(conf_path);
        this->items.push_back(emu);
        this->gird_items.push_back(emu->toGridItem());
    }
}

EmuGrid::EmuGrid(SDL_Surface *screen, Theme *theme)
{
    this->screen = screen;
    this->theme = theme;
    this->buildIndex();
}

EmuGrid::~EmuGrid()
{
    this->items.clear();
}

void EmuGrid::activate()
{
    this->active = true;
    this->theme->drawGrid(this->screen, this->gird_items, this->current_item);
}

void EmuGrid::deactivate()
{
    this->active = false;
    this->theme->freeGridResources();
}

void EmuGrid::onRight()
{

}

void EmuGrid::onLeft()
{
    
}

void EmuGrid::onUp()
{
    
}

void EmuGrid::onDown()
{
    
}

void EmuGrid::onCancel(ApplicationInterface *app)
{
    app->switchView(app->getView(View::MAIN_MENU));
}
