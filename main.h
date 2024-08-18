#ifndef MAIN_H
#define MAIN_H

#include "save/settings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>

#include <iostream>

#define SCALE (settings.window_height/720)

typedef enum modes_e
{
    QUIT,
    TITLE_SCREEN,
    MAIN_MENU,
    LEVEL_1,
} modes_t;

typedef struct option_box_s
{
    TextureText text;
    TextureImage flat;
    TextureImage light;
    TextureImage click;
} option_box_t;

extern Window window;
extern MouseCursor cursor;
extern Mix_Music* music;
extern int fps;
extern int mode;

#endif // MAIN_H 