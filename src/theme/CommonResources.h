#ifndef INC_RESOURCES_COMMON
#define INC_RESOURCES_COMMON

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

class CommonResources
{
private:
    SDL_Surface *background;    
    CommonResources() {};
    SDL_Surface *loadRotatedBackground(std::string path);
public:
    static CommonResources *load(std::string path);
    ~CommonResources();
    SDL_Surface *getBackground();
};

#endif
