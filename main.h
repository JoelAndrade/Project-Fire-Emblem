#ifndef MAIN_H
#define MAIN_H

#include "save/settings.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <File_Util.h>

#define SCALE (settings.window_height/720)

typedef enum modes_e {
    QUIT,
    TITLE_SCREEN,
    MAIN_MENU,
    LEVEL_1,
} modes_t;

typedef struct option_box_s {
    texture_image flat;
    texture_image light;
    texture_image click;
} option_box_t;

extern win window;
extern texture_image mouse_cursor;
extern int fps;

extern int mode;
extern bool hold;
extern SDL_Point mouse_pos;

void check_mouse(void);

#endif // MAIN_H 