#ifndef PRIVATE_MAIN_MENU
#define PRIVATE_MAIN_MENU

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>

typedef enum Main_Menu_e {
    QUIT_MAIN_MENU,
    MAIN_MENU_MAIN,
    NEWGAME,
    COUNTINUE,
    SETTINGS,
    GAME,
    VIDEO,
    AUDIO,

} Main_Menu_t;

extern int mainMenuMode;

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

#endif // PRIVATE_MAIN_MENU
