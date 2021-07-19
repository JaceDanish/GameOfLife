#include "GameOfLife.h"
#include "SDL2/SDL.h"
#include "SDLwrite.h"
#include <stdio.h>
#include <stdbool.h>

enum Status{
    QUIT = 0,
    DONE = 1,
    CONTINUE = 2
};

struct cell{
    int row;
    int col;
    bool alive;
};

typedef struct{
    struct cell cellArr[SCREEN_H10][SCREEN_W10];
    SDL_Renderer *renderer;
    SDL_Window *window;
}State;

void init_state(State *state);
void render_screen(State *state);
enum Status process_init(State *state);
enum Status process_game(State *state);
void draw_button(int row, int col, char *name, SDL_Renderer *renderer);
void pentadecathlon(State *state, int x, int y);
void acorn(State *state, int x, int y);
void diehard(State *state, int x, int y);
void rpentomino(State *state, int x, int y);
void gospergg(State *state, int x, int y);
void infiniteone(State *state, int x, int y);
void infinitetwo(State *state, int x, int y);
void infinitethree(State *state, int x, int y);
void clear_screen(State *state);

int main(int argc, char *argv[])
{
    bool initDone = false;
    enum Status status = CONTINUE;
    State state;
    init_state(&state);
    while (status != QUIT){
        while (initDone == false && status == CONTINUE){
            render_screen(&state);
            status = process_init(&state);
        }
        initDone = true;
        render_screen(&state);
        status = process_game(&state);
        if (status == DONE){
            initDone = false;
            status = CONTINUE;
        }
    }

}

enum Status process_init(State *state)
{
    SDL_Event event;
    int x, y;
    static int lastX, lastY;

    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN :
                if (event.key.keysym.sym != SDLK_ESCAPE)
                    if (event.key.keysym.sym == SDLK_RETURN){
                        return DONE;
                        break;
                    }
            case SDL_WINDOWEVENT_CLOSE :
            case SDL_QUIT :
                return QUIT;
                break;
            case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x, &y);
                //if mouse is in button zone
                if (x > SCREEN_WIDTH){
                    if (y > 10 && y < 35){
                        clear_screen(state);
                    }
                    else if (y > 40 && y < 75){
                        pentadecathlon(state, lastX, lastY);
                    }
                    else if (y > 70 && y < 105){
                        acorn(state, lastX, lastY);
                    }
                    else if (y > 100 && y < 135){
                        diehard(state, lastX, lastY);
                    }
                    else if (y > 130 && y < 165){
                        rpentomino(state, lastX, lastY);
                    }
                    else if (y > 160 && y < 195){
                        gospergg(state, lastX, lastY);
                    }
                    else if (y > 190 && y < 225){
                        infiniteone(state, lastX, lastY);
                    }
                    else if (y > 220 && y < 255){
                        infinitetwo(state, lastX, lastY);
                    }
                    else if (y > 250 && y < 285){
                        infinitethree(state, lastX, lastY);
                    }
                }
                else{
                    state->cellArr[y/PXL_SIZE][x/PXL_SIZE].alive = !state->cellArr[y/PXL_SIZE][x/PXL_SIZE].alive;
                    lastX = x/PXL_SIZE;
                    lastY = y/PXL_SIZE;
                }
                break;
        }
    }
    return CONTINUE;
}

enum Status process_game(State *state)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN :
                if (event.key.keysym.sym != SDLK_ESCAPE){
                    if (event.key.keysym.sym == SDLK_RETURN)
                        return DONE;
                    break;
                }
            case SDL_WINDOWEVENT_CLOSE :
            case SDL_QUIT :
                return QUIT;
                break;
        }
    }

    //copy cell grid
    struct cell copyArr[SCREEN_H10][SCREEN_W10];
    for (int i = 0; i < SCREEN_H10; i++){
        for (int j = 0; j < SCREEN_W10; j++){
            copyArr[i][j] = state->cellArr[i][j];
        }
    }

    //read from copy and change original
    for (int i = 0; i < SCREEN_H10; i++){
        for (int j = 0; j < SCREEN_W10; j++){
            int count = 0;
            for (int k = -1; k < 2; k++){
                for (int h = -1; h < 2; h++){
                    if (copyArr[i + k][j + h].alive &&
                        i + k != -1 && j + h != -1 &&
                        i + k != SCREEN_H10 && j + h != SCREEN_W10){
                        count++;
                    }
                }
            }
            if (count == 3){
                state->cellArr[i][j].alive = true;
            }
            else if (count == 4 && state->cellArr[i][j].alive){
                state->cellArr[i][j].alive = true;
            }
            else{
                state->cellArr[i][j].alive = false;
            }
        }
    }

    SDL_Delay(260);

    return CONTINUE;
}

void init_state(State *state)
{
    state->window = SDL_CreateWindow("Game Of Life",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SCREEN_WIDTH + 200,//+ to leave room for UI
                                     SCREEN_HEIGHT + 1, //+1 to show lowest grid line
                                     0);

    state->renderer = SDL_CreateRenderer(state->window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED |
                                         SDL_RENDERER_PRESENTVSYNC);


    for (int i = 0; i < SCREEN_H10; i++){
        for (int j = 0; j < SCREEN_W10; j++){
            state->cellArr[i][j].row = i * PXL_SIZE;
            state->cellArr[i][j].col = j * PXL_SIZE;
            state->cellArr[i][j].alive = false;
        }
    }

}

void render_screen(State *state)
{
    //background
    SDL_SetRenderDrawColor(state->renderer, 30, 30, 30, 255);
    SDL_RenderClear(state->renderer);

    //cell grid
    SDL_SetRenderDrawColor(state->renderer, 0, 200, 0, 255);
    for (int i = 0; i <= SCREEN_HEIGHT / PXL_SIZE; i++){    
        SDL_Rect rect = {0, i * PXL_SIZE, SCREEN_WIDTH, 1};
        SDL_RenderFillRect(state->renderer, &rect);
    }
    for (int i = 0; i <= SCREEN_WIDTH / PXL_SIZE; i++){
        SDL_Rect rect = {i * PXL_SIZE, 0, 1, SCREEN_HEIGHT};
        SDL_RenderFillRect(state->renderer, &rect);
    }

    //cells
    SDL_SetRenderDrawColor(state->renderer, 40, 100, 40, 255);
    for (int i = 0; i < SCREEN_H10; i++){
        for (int j = 0; j < SCREEN_W10; j++){
            if (state->cellArr[i][j].alive){
                SDL_Rect rect = {state->cellArr[i][j].col + 1,//adjusted to make
                                 state->cellArr[i][j].row + 1,//space for grid
                                 PXL_SIZE - 1, PXL_SIZE - 1};
                SDL_RenderFillRect(state->renderer, &rect);
            }
        }
    }
    draw_button(10, SCREEN_WIDTH + 10, "ClearScreen", state->renderer);
    draw_button(40, SCREEN_WIDTH + 10, "Pdecathlon", state->renderer);
    draw_button(70, SCREEN_WIDTH + 10, "Acorn", state->renderer);
    draw_button(100, SCREEN_WIDTH + 10, "Diehard", state->renderer);
    draw_button(130, SCREEN_WIDTH + 10, "RPentomino", state->renderer);
    draw_button(160, SCREEN_WIDTH + 10, "GosperGG", state->renderer);
    draw_button(190, SCREEN_WIDTH + 10, "InfiniteOne", state->renderer);
    draw_button(220, SCREEN_WIDTH + 10, "InfiniteTwo", state->renderer);
    draw_button(250, SCREEN_WIDTH + 10, "InfThree", state->renderer);

    SDL_RenderPresent(state->renderer);
}

void draw_button(int row, int col, char *name, SDL_Renderer *renderer)
{
    int nameLen = 0;
    while(*(name++) != '\0')
        nameLen++;

    SDLwrite_info info = {2, 2, 0, 0, 0, 255};

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_Rect rect = {col, row, 180, 25};
    SDL_RenderFillRect(renderer, &rect);

    for (int i = 0; i < nameLen; i++){
        SDLwrite_renderLetter(renderer, &info, name[i - nameLen - 1], row + 5, col + 5, 0, i);

    }
}

void pentadecathlon(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 9){    
        state->cellArr[y][x].alive = true;
        state->cellArr[y+1][x].alive = true;
        state->cellArr[y+2][x-1].alive = true;
        state->cellArr[y+2][x+1].alive = true;
        state->cellArr[y+3][x].alive = true;
        state->cellArr[y+4][x].alive = true;
        state->cellArr[y+5][x].alive = true;
        state->cellArr[y+6][x].alive = true;
        state->cellArr[y+7][x-1].alive = true;
        state->cellArr[y+7][x+1].alive = true;
        state->cellArr[y+8][x].alive = true;
        state->cellArr[y+9][x].alive = true;
    }
}

void acorn(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 2){
        state->cellArr[y][x].alive = true;
        state->cellArr[y+1][x+2].alive = true;
        state->cellArr[y+2][x-1].alive = true;
        state->cellArr[y+2][x].alive = true;
        state->cellArr[y+2][x+3].alive = true;
        state->cellArr[y+2][x+4].alive = true;
        state->cellArr[y+2][x+5].alive = true;
    }
}

void diehard(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 2){
        state->cellArr[y][x].alive = true;
        state->cellArr[y+1][x-6].alive = true;
        state->cellArr[y+1][x-5].alive = true;
        state->cellArr[y+2][x-5].alive = true;
        state->cellArr[y+2][x-1].alive = true;
        state->cellArr[y+2][x].alive = true;
        state->cellArr[y+2][x+1].alive = true;
    }
}

void rpentomino(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 2){
        state->cellArr[y][x].alive = true;
        state->cellArr[y][x+1].alive = true;
        state->cellArr[y+1][x-1].alive = true;
        state->cellArr[y+1][x].alive = true;
        state->cellArr[y+2][x].alive = true;
    }
}

void gospergg(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 7){
        state->cellArr[y][x].alive = true;
        state->cellArr[y+1][x].alive = true;
        state->cellArr[y+1][x-2].alive = true;
        state->cellArr[y+2][x-3].alive = true;
        state->cellArr[y+2][x-4].alive = true;
        state->cellArr[y+3][x-3].alive = true;
        state->cellArr[y+3][x-4].alive = true;
        state->cellArr[y+4][x-3].alive = true;
        state->cellArr[y+4][x-4].alive = true;
        state->cellArr[y+5][x-2].alive = true;
        state->cellArr[y+5][x].alive = true;
        state->cellArr[y+6][x].alive = true;//first figure ends here
        state->cellArr[y+2][x-11].alive = true;
        state->cellArr[y+2][x-12].alive = true;
        state->cellArr[y+3][x-13].alive = true;
        state->cellArr[y+3][x-9].alive = true;
        state->cellArr[y+4][x-14].alive = true;
        state->cellArr[y+4][x-8].alive = true;
        state->cellArr[y+5][x-14].alive = true;
        state->cellArr[y+5][x-10].alive = true;
        state->cellArr[y+5][x-8].alive = true;
        state->cellArr[y+5][x-7].alive = true;
        state->cellArr[y+6][x-14].alive = true;
        state->cellArr[y+6][x-8].alive = true;
        state->cellArr[y+7][x-13].alive = true;
        state->cellArr[y+7][x-9].alive = true;
        state->cellArr[y+8][x-12].alive = true;
        state->cellArr[y+8][x-11].alive = true; //second figure ends here
        state->cellArr[y+2][x+10].alive = true;
        state->cellArr[y+2][x+11].alive = true;
        state->cellArr[y+3][x+10].alive = true;
        state->cellArr[y+3][x+11].alive = true;
        state->cellArr[y+4][x-23].alive = true;
        state->cellArr[y+4][x-24].alive = true;
        state->cellArr[y+5][x-23].alive = true;
        state->cellArr[y+5][x-24].alive = true;
    }
}

void infiniteone(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 4){
        state->cellArr[y][x].alive = true;
        state->cellArr[y+1][x].alive = true;
        state->cellArr[y+2][x].alive = true;
        state->cellArr[y+1][x+1].alive = true;
        state->cellArr[y+1][x-2].alive = true;
        state->cellArr[y+2][x-2].alive = true;
        state->cellArr[y+3][x-2].alive = true;
        state->cellArr[y+4][x-4].alive = true;
        state->cellArr[y+5][x-4].alive = true;
        state->cellArr[y+5][x-6].alive = true;
    }
}

void infinitetwo(State *state, int x, int y)
{
    if (y < SCREEN_H10 - 3){
        state->cellArr[y][x].alive = true;
        state->cellArr[y][x+2].alive = true;
        state->cellArr[y][x-1].alive = true;
        state->cellArr[y][x-2].alive = true;
        state->cellArr[y+1][x-2].alive = true;
        state->cellArr[y+2][x+1].alive = true;
        state->cellArr[y+2][x+2].alive = true;
        state->cellArr[y+3][x-1].alive = true;
        state->cellArr[y+3][x].alive = true;
        state->cellArr[y+3][x+2].alive = true;
        state->cellArr[y+4][x-2].alive = true;
        state->cellArr[y+4][x].alive = true;
        state->cellArr[y+4][x+2].alive = true;
    }
}

void infinitethree(State *state, int x, int y)
{
    state->cellArr[y][x-19].alive = true;
    state->cellArr[y][x-18].alive = true;
    state->cellArr[y][x-17].alive = true;
    state->cellArr[y][x-16].alive = true;
    state->cellArr[y][x-15].alive = true;
    state->cellArr[y][x-14].alive = true;
    state->cellArr[y][x-13].alive = true;
    state->cellArr[y][x-12].alive = true;

    state->cellArr[y][x-10].alive = true;
    state->cellArr[y][x-9].alive = true;
    state->cellArr[y][x-8].alive = true;
    state->cellArr[y][x-7].alive = true;
    state->cellArr[y][x-6].alive = true;

    state->cellArr[y][x].alive = true;
    state->cellArr[y][x-1].alive = true;
    state->cellArr[y][x-2].alive = true;

    state->cellArr[y][x+7].alive = true;
    state->cellArr[y][x+8].alive = true;
    state->cellArr[y][x+9].alive = true;
    state->cellArr[y][x+10].alive = true;
    state->cellArr[y][x+11].alive = true;
    state->cellArr[y][x+12].alive = true;
    state->cellArr[y][x+13].alive = true;

    state->cellArr[y][x+15].alive = true;
    state->cellArr[y][x+16].alive = true;
    state->cellArr[y][x+17].alive = true;
    state->cellArr[y][x+18].alive = true;
    state->cellArr[y][x+19].alive = true;
}

void clear_screen(State *state)
{
    for (int i = 0; i < SCREEN_H10; i++){
        for (int j = 0; j < SCREEN_W10; j++){
            state->cellArr[i][j].alive = false;
        }
    }
}