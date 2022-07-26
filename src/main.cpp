#include <SDL/SDL.h>
#include<fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "sys/ioctl.h"
#include "system/SystemJSON.h"
#include "view/MainMenu.h"
#include "theme/Theme.h"
#include "theme/ExceptionCodes.h"
#include "system/ExceptionCodes.h"
#include <iostream>

#define	BUTTON_A	KEY_SPACE
#define	BUTTON_B	KEY_LEFTCTRL  

#define	BUTTON_X	KEY_LEFTSHIFT
#define	BUTTON_Y	KEY_LEFTALT  

#define	BUTTON_START	KEY_ENTER
#define	BUTTON_SELECT	KEY_RIGHTCTRL

SDL_Surface *video;
SDL_Surface *screen;

SystemJSON *system_config;
Theme      *current_theme;

void initScreen()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_ShowCursor(SDL_DISABLE);
    video = SDL_SetVideoMode(640,480, 32, SDL_HWSURFACE);
    screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 640,480, 32, 0,0,0,0);
}

void renderScreen()
{
    SDL_BlitSurface(screen, NULL, video, NULL);
    SDL_Flip(video);
}

int main(int argc, char *argv[])
{
    initScreen();
    std::cout << "initialized screen" << std::endl;

    try {
        SystemJSON *system_config = SystemJSON::load();
        std::cout << "loaded config from system.json" << std::endl;

        Theme current_theme(system_config->getThemePath());
        std::cout << "initialized current theme" << std::endl;
        std::cout << "path to theme is "+system_config->getThemePath() << std::endl;

        MainMenu current_view(screen, &current_theme);
        renderScreen();
        std::cout << "initialized current view as main menu" << std::endl;

        struct input_event ev;
        int input = open("/dev/input/event0", O_RDONLY);
        
        // main loop, poll for button input
        while(read(input, &ev, sizeof(ev)) == sizeof(ev)) {

            if (( ev.type != EV_KEY ) || ( ev.value != 1 )) continue;

            std::cout << "button pressed: ";
            switch (ev.code)
            {
            case KEY_LEFT:
                std::cout << "left" << std::endl;
                current_view.onLeft();
                break;

            case KEY_RIGHT:
                std::cout << "right" << std::endl;
                current_view.onRight();
                break;
            
            // only in test: Quit when pressing B
            case BUTTON_B:
                std::cout << "B" << std::endl;
                goto programmEnd;
            
            default:
                break;
            }
            renderScreen();
        }
    }
    catch (int code) {
        switch (code)
        {
        case ICON_LOADING_FAILED:
            std::cerr << "could not load one or more main menu items from theme" << std::endl;
            break;
        
        case COULD_NOT_READ_SYSTEMJSON:
            std::cerr << "could not open system.json for reading" << std::endl;
            break;

        default:
            std::cerr << "a unknown exception stopped the programm" << std::endl;
            break;
        }
        exit(code);
    }

    programmEnd:
    std::cout << "programm stopped normal" << std::endl;
    return 0;
}
