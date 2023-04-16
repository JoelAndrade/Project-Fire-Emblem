#include "../../main.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static void runSettings(void);
static void renderScreen(void);

void settings_main_menu(void) {

    while (mainMenuMode == SETTINGS) {
        runSettings();

        if (mainMenuMode == GAME_SETTINGS) {

        }
        else if (mainMenuMode == VIDEO_SETTINGS) {
            video_settings_main_menu();
        }
        else if (mainMenuMode == AUDIO_SETTINGS) {

        }
    }
}

static void runSettings(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    while (mainMenuMode == SETTINGS) {
        startingTick = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mainMenuMode = QUIT_MAIN_MENU;
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = event.button.state;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {

                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = event.button.state;
                    menuEvent(video_flat.newRect, VIDEO_SETTINGS);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mainMenuMode = MAIN_MENU_MAIN;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mainMenuMode = MAIN_MENU_MAIN;
                }
            }
        }
        
        renderScreen();

        frameCap(fps, startingTick);
    }
}

static void renderScreen(void) {
    checkMouse();
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);
    
    window.clearRender();

    background.render(window.renderer);

    renderBox(game_flat, game_light, game_click);
    renderBox(video_flat, video_light, video_click);
    renderBox(audio_flat, audio_light, audio_click);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

