#ifndef INC_VIEW_EMU_GRID
#define INC_VIEW_EMU_GRID

#include <vector>
#include "ViewInterface.h"
#include "../theme/GridItem.h"
#include "../theme/Theme.h"
#include "../emu/Emu.h"
#include "../ApplicationInterface.h"

class EmuGrid: public ViewInterface
{
private:
    std::vector<Emu*> items;
    std::vector<GridItem> gird_items;
    short unsigned int current_item;
    SDL_Surface *screen;
    Theme *theme;
    bool active = false;
    void buildIndex();
public:
    EmuGrid(SDL_Surface *screen, Theme *theme);
    ~EmuGrid();
    void onRight();
    void onLeft();
    void onUp();
    void onDown();
    void onAccept(ApplicationInterface *app) {};
    void onCancel(ApplicationInterface *app);
    void activate();
    void deactivate();
};

#endif
