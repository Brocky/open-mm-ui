#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <iostream>
#include "sys/ioctl.h"
#include "system/SystemJSON.h"
#include "view/MainMenu.h"
#include "theme/Theme.h"
#include "theme/ExceptionCodes.h"
#include "util/ExceptionCodes.h"
#include "Application.h"

#define	BUTTON_A	KEY_SPACE
#define	BUTTON_B	KEY_LEFTCTRL  

#define	BUTTON_X	KEY_LEFTSHIFT
#define	BUTTON_Y	KEY_LEFTALT  

#define	BUTTON_START	KEY_ENTER
#define	BUTTON_SELECT	KEY_RIGHTCTRL

void Application::initScreen()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    this->video = SDL_SetVideoMode(640,480, 32, SDL_HWSURFACE);
    this->screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 640,480, 32, 0,0,0,0);
}

void Application::stop()
{
    this->is_running = false;
}

void Application::updateScreen()
{
    SDL_BlitSurface(this->screen, NULL, this->video, NULL);
    SDL_Flip(this->video);
}

int Application::run()
{
    this->initScreen();
    std::cout << "Screen initialized" << std::endl;

    try {
        SystemJSON *system_config = SystemJSON::load();
        std::cout << "Loaded system.json" << std::endl;
        std::cout << "Themepath is " << system_config->getThemePath() << std::endl;
        Theme current_theme(system_config->getThemePath());
        std::cout << "Intitialized theme" << std::endl;
        
        this->current_view = new MainMenu(screen, &current_theme);
        std::cout << "Intitialized main menu view" << std::endl;
        this->current_view->activate();
        std::cout << "Activated main menu view" << std::endl;
        this->updateScreen();
        std::cout << "Redrew screen" << std::endl;

        struct input_event ev;
        int input = open("/dev/input/event0", O_RDONLY);

        // main loop, poll for button input
        this->is_running = true;
        while(read(input, &ev, sizeof(ev)) == sizeof(ev)) {
            if(!this->is_running) {
                // application has been stopped
                return 0;
            }

            // ignore events neither button nor pressed
            if (( ev.type != EV_KEY ) || ( ev.value != 1 )) continue;

            switch (ev.code)
            {
            case KEY_LEFT:
                this->current_view->onLeft();
                break;

            case KEY_RIGHT:
                this->current_view->onRight();
                break;
            
            case BUTTON_B:
                this->current_view->onCancel(this);
                break;
            
            default:
                break;
            }
            this->updateScreen();
        }
    }
    catch (int code) {
        switch (code) {
            case ICON_LOADING_FAILED:
                std::cerr << "could not load one or more main menu items from theme" << std::endl;
                break;
            
            case COULD_NOT_READ_JSON:
                std::cerr << "could not open a json file for reading" << std::endl;
                break;

            default:
                std::cerr << "a unknown exception stopped the programm" << std::endl;
                break;
        }
        return code;
    }

    // we should never end up here, but it makes the compiler happy
    return 1;
}
