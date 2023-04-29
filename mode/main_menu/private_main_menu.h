#ifndef PRIVATE_MAIN_MENU_H
#define PRIVATE_MAIN_MENU_H

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
extern bool hold;

extern textureImage background;
extern textureImage game_flat;
extern textureImage game_light;
extern textureImage game_click;
extern textureImage video_flat;
extern textureImage video_light;
extern textureImage video_click;
extern textureImage audio_flat;
extern textureImage audio_light;
extern textureImage audio_click;

extern textureImage apRatio1080_flat;
extern textureImage apRatio1080_light;
extern textureImage apRatio1080_click;
extern textureImage apRatio720_flat;
extern textureImage apRatio720_light;
extern textureImage apRatio720_click;

extern textureImage apply_flat;
extern textureImage apply_light;
extern textureImage apply_click;

extern textureImage arrow_flat;
extern textureImage arrow_light;
extern textureImage arrow_click;

void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click);
void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click, SDL_RendererFlip);
void menuEvent(SDL_Rect rect, int event);

void settings_main_menu(void);
void video_settings_main_menu(void);

void imagesInit_mainMenu(void);
void destroyImages_mainMenu(void);

#endif // PRIVATE_MAIN_MENU
