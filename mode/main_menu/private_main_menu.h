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

extern int main_menu_mode;

extern texture_image background;

extern option_box_t game_box;
extern option_box_t video_box;
extern option_box_t audio_box;

extern option_box_t ap_ratio_1080_box;
extern option_box_t ap_ratio_720_box;

extern option_box_t apply_box;
extern option_box_t arrow_box;

void render_box(option_box_t box);
void render_box(option_box_t box, SDL_RendererFlip);
void menu_event(SDL_Rect rect, int event);

void settings_main_menu(void);
void video_settings_main_menu(void);

void images_init_main_menu(void);
void destroy_images_main_menu(void);

#endif // PRIVATE_MAIN_MENU
