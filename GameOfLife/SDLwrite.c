#include "SDLwrite.h"
#include "SDL2/SDL.h"
//version 2.0

int SDLwrite_renderDigit(SDL_Renderer *renderer,
                         SDLwrite_info *info,
                         int digit,
                         int startY,
                         int startX,
                         float offsetY,
                         float offsetX
                         )
{
    if (!renderer || !info)
        return -1;

    //set blendermode to enable alpha
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    short unsigned int pixlGrid[5][4] = {0};
    short unsigned int alpha = info->alpha;
    startX += info->pixlWidth * 4 * offsetX;
    startY += info->pixlHeight * 6 * offsetY;

    switch (digit){
        case 0 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[3][0] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 1 :
            pixlGrid[0][1] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[1][1] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[3][1] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 2 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][0] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 3 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 4 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 5 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][1] = alpha;
            break;
        case 6 :
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][0] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 7 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[3][0] = alpha;
            pixlGrid[4][0] = alpha;
            break;
        case 8 :
            pixlGrid[0][0] = alpha;
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][0] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][1] = alpha;
            pixlGrid[4][2] = alpha;
            break;
        case 9 :
            pixlGrid[0][1] = alpha;
            pixlGrid[0][2] = alpha;
            pixlGrid[1][0] = alpha;
            pixlGrid[1][2] = alpha;
            pixlGrid[2][0] = alpha;
            pixlGrid[2][1] = alpha;
            pixlGrid[2][2] = alpha;
            pixlGrid[3][2] = alpha;
            pixlGrid[4][0] = alpha;
            pixlGrid[4][1] = alpha;
            break;
        default : return -2;
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 4; j++){
            SDL_Rect rect = {(startX + j * info->pixlWidth), (startY + i * info->pixlHeight), info->pixlWidth, info->pixlHeight};
            SDL_SetRenderDrawColor(renderer, info->red, info->green, info->blue, pixlGrid[i][j]);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    return 1;
}

int SDLwrite_renderLetter(SDL_Renderer *renderer,
                         SDLwrite_info *info,
                         char letter,
                         int startY,
                         int startX,
                         float offsetY,
                         float offsetX
                         )
{
    if (!renderer || !info)
        return -1;

    startX += info->pixlWidth * 7 * offsetX;
    startY += info->pixlHeight * 9 * offsetY;

    //set blendermode to enable alpha
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    letter = toupper(letter);
    Uint8 a = info->alpha;
    Uint8 letters[] = {
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, //A
        a, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, 0,
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, 0, //B
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, 0, a, 0, 0, 0, 0,
        a, 0, 0, 0, 0, a, 0, 0, 0, a, 0, a, a, a, 0, //C
        a, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, 0, //D
        a, a, a, a, a, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, a, a, a, 0,
        a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, a, a, a, a, //E
        a, a, a, a, a, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, a, a, a, 0,
        a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, //F
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, 0, a, 0, 0, 0, 0,
        a, 0, a, a, a, a, 0, 0, 0, a, 0, a, a, a, 0, //G
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, //H
        a, a, a, a, a, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0,
        0, 0, a, 0, 0, 0, 0, a, 0, 0, a, a, a, a, a, //I
        a, a, a, a, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, 0, a, a, a, 0, //J
        a, 0, 0, 0, a, a, 0, 0, a, 0, a, 0, a, 0, 0, a, a, 0, 0, 0,
        a, 0, a, 0, 0, a, 0, 0, a, 0, a, 0, 0, 0, a, //K
        a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0,
        a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, a, a, a, a, //L
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, 0, a, a, a, 0, a, 0, a,
        a, 0, a, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, //M
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, 0, 0, a, a, 0, a, 0, a,
        a, 0, 0, a, a, a, 0, 0, 0, a, a, 0, 0, 0, a, //N
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, 0, a, a, a, 0, //O
        a, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, 0,
        a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, //P
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a,
        a, 0, a, 0, a, a, 0, 0, a, a, 0, a, a, a, a, //Q
        a, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, a, a, a, a, a, 0,
        a, 0, a, 0, 0, a, 0, 0, a, 0, a, 0, 0, 0, a, //R
        0, a, a, a, 0, a, 0, 0, 0, a, a, 0, 0, 0, 0, 0, a, a, a, 0,
        0, 0, 0, 0, a, a, 0, 0, 0, a, 0, a, a, a, 0, //S
        a, a, a, a, a, 0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0,
        0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, //T
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a,
        a, 0, 0, 0, a, a, 0, 0, 0, a, 0, a, a, a, 0, //U
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, 0, 0, a,
        a, 0, 0, 0, a, 0, a, 0, a, 0, 0, 0, a, 0, 0, //V
        a, 0, 0, 0, a, a, 0, 0, 0, a, a, 0, a, 0, a, a, 0, a, 0, a,
        a, 0, a, 0, a, a, 0, a, 0, a, 0, a, 0, a, 0, //W
        a, 0, 0, 0, a, 0, a, 0, a, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0,
        0, 0, a, 0, 0, 0, a, 0, a, 0, a, 0, 0, 0, a, //X
        a, 0, 0, 0, a, 0, a, 0, a, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0,
        0, 0, a, 0, 0, 0, 0, a, 0, 0, 0, 0, a, 0, 0, //Y
        a, a, a, a, a, 0, 0, 0, 0, a, 0, 0, 0, a, 0, 0, 0, a, 0, 0,
        0, a, 0, 0, 0, a, 0, 0, 0, 0, a, a, a, a, a //Z
    };

    Uint8 *ptr = &letters[(letter - 65) * 35];

    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 5; j++){
            SDL_Rect rect = {(startX + j * info->pixlWidth), (startY + i * info->pixlHeight), info->pixlWidth, info->pixlHeight};
            SDL_SetRenderDrawColor(renderer, info->red, info->green, info->blue, *(ptr++));
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    return 1;
}
