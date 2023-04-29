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
    LEVEL_1,

} Modes_t;

extern win window;
extern textureImage mouseCursor;

extern int mode;
extern bool hold;
extern SDL_Point mousePos;

void checkMouse(void);

#endif // MAIN_H 