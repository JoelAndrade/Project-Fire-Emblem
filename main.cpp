#include "main.h"
#include "save/settings.h"
#include "mode/title_screen/main_title_screen.h"
#include "mode/main_menu/main_main_menu.h"
#include "mode/level_1/main_level_1.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

win window;
textureImage mouseCursor;
int fps = 60; // make this a macro if the fps is fixed

int mode = TITLE_SCREEN;
bool hold = false;
SDL_Point mousePos;

void checkMouse(void) {
    if(window.mouseInWindow()) {
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
    }
    else {
        mousePos.x = window.w;
        mousePos.y = window.h;
    }
}

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

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);

    while (mode != QUIT) {
        if (mode == TITLE_SCREEN) {
            main_titleScreen();
        }
        if (mode == MAIN_MENU) {
            main_main_menu();
        }
        if (mode == LEVEL_1) {
            main_level_1();
        }
    }

    // Save and clean everything
    writeSave(&settings, sizeof(settings), "./setting.bin");
    SDL_DestroyWindow(window.window); //This closed the window
    SDL_DestroyRenderer(window.renderer);
    SDL_Quit(); //Closed the SDL program
    IMG_Quit();
    Mix_Quit();
    return 0;
}

// TODO: Make main menu
// Make audio settings
// Add transparentcy to game settings

// TODO: Implement sound
// Smooth the transitions of the music

// TODO: Make basic board
// Add a villian on the board with vilain interactions
// Need a functions that calculates the damage, crit, and misses
// Might want to make the board a square to leave the side with menuing and camera
// Need to be able to handle animation
// Add keyboard shortcuts

// TODO: Have the all the board meckanics all on one file. 
// Have details about specific (size, characters, etc.) on a diffent file

// Note: The size the blocks does not matter right row. There will be a camera anyway.
