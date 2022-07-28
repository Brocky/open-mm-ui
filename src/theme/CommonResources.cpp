#include <iostream>
#include "CommonResources.h"

CommonResources *CommonResources::load(std::string path)
{
    CommonResources *self = new CommonResources;

    self->background = self->loadRotatedBackground(path);
    std::cout << "CommonResources: loaded rotated background" << std::endl;
    self->header = IMG_Load((path + "skin/bg-title.png").c_str());
    std::cout << "CommonResources: title bar background" << std::endl;
    self->footer = IMG_Load((path + "skin/tips-bar-bg.png").c_str());
    std::cout << "CommonResources: loaded bottom bar" << std::endl;

    return self;
}

SDL_Surface *CommonResources::getBackground()
{
    return this->background;
}

SDL_Surface *CommonResources::getHeader()
{
    return this->header;
}

SDL_Surface *CommonResources::getFooter()
{
    return this->footer;
}

CommonResources::~CommonResources()
{
    SDL_FreeSurface(this->background);
    SDL_FreeSurface(this->header);
    SDL_FreeSurface(this->footer);
}

SDL_Surface *CommonResources::loadRotatedBackground(std::string path)
{
    SDL_Surface *src = IMG_Load((path + "skin/background.png").c_str());
    if (!src) {
        return NULL;
    }
    
    const SDL_PixelFormat *format = src->format;
    SDL_Surface *bg = SDL_CreateRGBSurface(src->flags, src->w, src->h, format->BitsPerPixel,
		format->Rmask, format->Gmask, format->Bmask, format->Amask);
    SDL_LockSurface(src);
    SDL_LockSurface(bg);

    int bytesPerPixel = format->BytesPerPixel;
    int bytesPerLine  = bytesPerPixel * src->w;
    int w, h, cnt;

	Uint8 *sLine = (Uint8*)src->pixels;
	Uint8 *dLine = (Uint8*)bg->pixels;
	Uint8 *sPixel = sLine;
	Uint8 *dPixel;

    h = bg->h;
    do
    {
        dPixel = dLine + (bytesPerLine - bytesPerPixel);
        w = bg->w;

        do
        {
            cnt = bytesPerPixel;

            do
            {
                *dPixel++ = *sPixel++;
            }
            while (--cnt != 0);

            dPixel -= (bytesPerPixel << 1);
        }
        while (--w != 0);

        // Next line
        sPixel = (sLine += src->pitch);
        dLine += bg->pitch;
    }
    while (--h != 0);

    SDL_UnlockSurface(src);
    SDL_UnlockSurface(bg);
    SDL_FreeSurface(src);

    return bg;
}
