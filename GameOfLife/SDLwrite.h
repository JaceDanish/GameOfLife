#include "SDL2/SDL.h"
#ifndef SDLWRITE_H
#define SDLWRITE_H


//Struct to pass info to SDLwrite_renderDigit()
//Height & width of each pixel making up a digit of [5]by[4]
typedef struct{
    int pixlHeight;
    int pixlWidth;
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
    unsigned short int alpha;
}SDLwrite_info;


//Renders a single digit in a [5]by[4] format
//Parameters:
//instanciated renderer and info struct,
//digit to be rendered and it's position,
//offsets: +/-1 for every preceding digit
//returns 1 if successful, negative no. if not
int SDLwrite_renderDigit(SDL_Renderer *renderer,
                         SDLwrite_info *info,
                         int digit,
                         int startY,
                         int startX,
                         float offsetY,
                         float offsetX
                         );

int SDLwrite_renderLetter(SDL_Renderer *renderer,
                         SDLwrite_info *info,
                         char letter,
                         int startY,
                         int startX,
                         float offsetY,
                         float offsetX
                         );

#endif