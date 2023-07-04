#ifndef PRIVATE_MAIN_MENU_H
#define PRIVATE_MAIN_MENU_H

#include "../../main.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>

typedef enum Main_Menu_e {
    QUIT_MAIN_MENU,
    MAIN_MENU_MAIN,
    NEWGAME,
    COUNTINUE,
    SETTINGS,
    GAME_SETTINGS,
    VIDEO_SETTINGS,
    AUDIO_SETTINGS,

} Main_Menu_t;

extern int mainMenuMode;

extern textureImage background;

extern option_box_t game_box;
extern option_box_t video_box;
extern option_box_t audio_box;

extern option_box_t apRatio1080_box;
extern option_box_t apRatio720_box;

extern option_box_t apply_box;
extern option_box_t arrow_box;

void renderBox(option_box_t box);
void renderBox(option_box_t box, SDL_RendererFlip);
void menuEvent(SDL_Rect rect, int event);

void settings_main_menu(void);
void video_settings_main_menu(void);

void imagesInit_mainMenu(void);
void destroyImages_mainMenu(void);

#endif // PRIVATE_MAIN_MENU
