#ifndef INC_VIEW_EMU_GRID
#define INC_VIEW_EMU_GRID

#include <vector>
#include "ViewInterface.h"
#include "../theme/Theme.h"

class EmuGrid: public ViewInterface
{
private:
    static std::string getIconPath(std::string name);
    std::vector<GridItem> items;
    SDL_Surface *screen;
    Theme *theme;
    void buildIndex();
public:
    EmuGrid(SDL_Surface *screen, Theme *theme);
    ~EmuGrid();
    void onRight() {};
    void onLeft() {};
    void onUp() {};
    void onDown() {};
    void activate() {};
    void deactivate() {};
};

#endif
