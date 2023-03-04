#ifndef MAIN_H
#define MAIN_H

#include "save/settings.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <File_Util.h>

#define SCALE settings.windowHeight/720

typedef enum Modes_e {
    QUIT,
    TITLE_SCREEN,
    MAIN_MENU,

} Modes_t;

extern win window;
extern textureImage mouseCursor;

extern int mode;
extern int xMousePos;
extern int yMousePos;

#endif // MAIN_H 