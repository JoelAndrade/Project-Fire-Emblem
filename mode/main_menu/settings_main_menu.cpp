#include "../../main.h"
#include "settings_main_menu.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static bool hold;

static void runSettings(void);
static void renderScreen(void);

void settings_main_menu(void) {

    while (mainMenuMode == SETTINGS) {
        if (mainMenuMode == SETTINGS) {
            runSettings();
        }
        else if (mainMenuMode == GAME) {

        }
        else if (mainMenuMode == VIDEO) {

        }
        else if (mainMenuMode == AUDIO) {

        }
        else {
            break;
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
            updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
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
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mainMenuMode = MAIN_MENU_MAIN;
                }
            }

        }
        frameCap(fps, startingTick);

        renderScreen();
    }
}

static void renderScreen(void) {
    SDL_Point point = {
        .x = xMousePos,
        .y = yMousePos,
    };

    window.clearRender();

    background.render(window.renderer);

    if (SDL_PointInRect(&point, &game_flat.newRect) && hold) {
        game_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &game_flat.newRect)) {
        game_light.render(window.renderer);
    }
    else {
        game_flat.render(window.renderer);
    }

    if (SDL_PointInRect(&point, &video_flat.newRect) && hold) {
    video_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &video_flat.newRect)) {
        video_light.render(window.renderer);
    }
    else {
        video_flat.render(window.renderer);
    }

    if (SDL_PointInRect(&point, &audio_flat.newRect) && hold) {
        audio_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &audio_flat.newRect)) {
        audio_light.render(window.renderer);
    }
    else {
        audio_flat.render(window.renderer);
    }

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

