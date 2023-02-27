#include "main.h"
#include "save/settings.h"
#include "mode/title_screen/title_screen_main.h"
#include "mode/main_menu/main_main_menu.h"

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

static double scale(double scaleNumber);

int main(int argc, char* args[]) {
    //Init SDL Stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    loadSettingsFile();

    window.init(settings.widowWidth, settings.windowHeight, "Loading...");
    mouseCursor.init(window.renderer, "images/Images/Cursor.png", 0.05);
    
    while (mode != QUIT) {
        if (mode == TITLE_SCREEN) {
            main_titleScreen();
        }
        if (mode == MAIN_MENU) {
            main_main_menu();
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

static double scale(double scaleNumber) {
     return scaleNumber * (window.h/720.0);
}

// TODO: Make main menu
// remove the 1080 highlights if not used
// Implement aspect ratio change 

// TODO: Implement sound