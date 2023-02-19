#include "main.h"
#include "save/settings.h"
#include "mode/title_screen/title_screen_main.h"
#include "mode/main_menu/main_menu_main.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

win window;
textureImage mouseCursor;

int mode = TITLE_SCREEN;
int xMousePos;
int yMousePos;

int main(int argc, char* args[]) {
    //Init SDL Stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);

    loadSettingsFile();
    window.init(settings.widowWidth, settings.windowHeight, "Loading...");
    
    while(mode != QUIT) {
        if (mode == TITLE_SCREEN) {
            runTitleScreen(); 
        }
        if (mode == MAIN_MENU) {
            runMainMenu();
        }
          
    }

    // Save and clean everything
    writeSave(&settings, sizeof(settings), "./setting.bin");
    SDL_DestroyWindow(window.window); //This closed the window
    SDL_DestroyRenderer(window.renderer);
    window.window = NULL;
    SDL_Quit(); //Closed the SDL program
    IMG_Quit();
    return 0;
}

// TODO: Make main menu
// TODO: Make video settings (1920|1080 && 1280|720)
