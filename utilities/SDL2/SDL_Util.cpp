#include "SDL_Util.h"

#include <SDL2/SDL.h>

//RGB
SDL_Color violet = {255,   0, 255};
SDL_Color green =  {  0, 255,   0};
SDL_Color red =    {255,   0,   0};
SDL_Color cyan =   {  0, 255, 255};
SDL_Color blue =   {  0,   0, 255};
SDL_Color black =  {  0,   0,   0};
SDL_Color white =  {255, 255, 255};
SDL_Color orange = {255, 100,   0};

void frameCap(int fps, Uint32 startingTick) {
    if (1000/fps > SDL_GetTicks() - startingTick) {
        SDL_Delay(1000/fps - (SDL_GetTicks() - startingTick));
    }
}

void updateCursorPos(SDL_Rect* rect, int* xPos, int* yPos) {
    SDL_GetMouseState(xPos, yPos);
    rect->x = *xPos;
    rect->y = *yPos;
}
