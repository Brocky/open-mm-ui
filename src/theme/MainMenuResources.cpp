#include "../view/MainMenu.h"
#include "MainMenuResources.h"
#include "ExceptionCodes.h"

MainMenuRessources *MainMenuRessources::load(std::string path)
{
    MainMenuRessources *self = new MainMenuRessources();

    self->icons[MenuItem::RECENT] = { 
        IMG_Load((path + "skin/ic-recent-f.png").c_str()),
        IMG_Load((path + "skin/ic-recent-n.png").c_str()) 
    };

    self->icons[MenuItem::FAVORITES] = { 
        IMG_Load((path + "skin/ic-favorite-f.png").c_str()),
        IMG_Load((path + "skin/ic-favorite-n.png").c_str()) 
    };

    self->icons[MenuItem::GAMES] = { 
        IMG_Load((path + "skin/ic-game-f.png").c_str()), 
        IMG_Load((path + "skin/ic-game-n.png").c_str()) 
    };

    self->icons[MenuItem::EXPERT] = { 
        IMG_Load((path + "skin/ic-retroarch-f.png").c_str()), 
        IMG_Load((path + "skin/ic-retroarch-n.png").c_str()) 
    };

    self->icons[MenuItem::APP] = { 
        IMG_Load((path + "skin/ic-app-f.png").c_str()), 
        IMG_Load((path + "skin/ic-app-n.png").c_str())
    };

    self->icons[MenuItem::SETTINGS] = { 
        IMG_Load((path + "skin/ic-setting-f.png").c_str()),
        IMG_Load((path + "skin/ic-setting-n.png").c_str())
    };

    self->verifyIcons();

    return self;
}

void MainMenuRessources::verifyIcons()
{
    for(MainMenuIcon &icon : this->icons) {
        if (!icon.active || !icon.inactive) {
            throw ICON_LOADING_FAILED;
        }
    }
}

MainMenuIcon *MainMenuRessources::getIcon(int item)
{
    return &this->icons[item];
}

MainMenuRessources::~MainMenuRessources()
{
    for(MainMenuIcon &icon : this->icons) {
        SDL_FreeSurface(icon.active);
        SDL_FreeSurface(icon.inactive);
    }
}
