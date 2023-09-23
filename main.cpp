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
texture_image mouse_cursor;
int fps = 60; // make this a macro if the fps is fixed

int mode = TITLE_SCREEN;
bool hold = false;
SDL_Point mouse_pos;

void check_mouse(void)
{
    if(window.mouse_in_window())
    {
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    }
    else
    {
        mouse_pos.x = window.w;
        mouse_pos.y = window.h;
    }
}

int main(int argc, char* args[]) {
    //Init SDL Stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    load_settings_file();

    window.init(settings.widow_width, settings.window_height, "Loading...");
    mouse_cursor.init(window.renderer, "images/Images/Cursor.png", 0.05);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);

    while (mode != QUIT)
    {
        if (mode == TITLE_SCREEN)
        {
            main_title_screen();
        }
        if (mode == MAIN_MENU)
        {
            main_main_menu();
        }
        if (mode == LEVEL_1)
        {
            main_level_1();
        }
    }

    // Save and clean everything
    write_save(&settings, sizeof(settings), "./setting.bin");
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
// Might want add double click chort cuts

// TODO: Have all the board meckanics all on one file. 
// Have details about specific (size, characters, etc.) on a diffent file

// TODO: Remove the picture tiles and hava the map on one big image

// Note: The size the blocks does not matter right row. There will be a camera anyway.
