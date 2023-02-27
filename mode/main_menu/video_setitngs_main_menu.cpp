#include "../../main.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static void runVideoSettings(void);
static void renderScreen(void);

void video_settings_main_menu(void) {
    runVideoSettings();
}

static void runVideoSettings(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    while (mainMenuMode == VIDEO_SETTINGS) {
        startingTick = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mainMenuMode = QUIT_MAIN_MENU;
                mode = QUIT;
            }

            if (event.motion.type) {
                updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
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
                    mainMenuMode = SETTINGS;
                }
            }

        }
        frameCap(fps, startingTick);

        renderScreen();
    }
}

static void renderScreen(void) {
    point = {
        .x = xMousePos,
        .y = yMousePos,
    };


    window.clearRender();

    background.render(window.renderer);

    apRatio1080_flat.render(window.renderer);

    arrow_flat.changePos(window.w/5, window.h/2);
    arrow_light.changePos(window.w/5, window.h/2);
    arrow_click.changePos(window.w/5, window.h/2);
    arrow_flat.newRect.shiftXY();
    arrow_light.newRect.shiftXY();
    arrow_click.newRect.shiftXY();
    renderBox(arrow_flat, arrow_light, arrow_click, SDL_FLIP_HORIZONTAL);

    arrow_flat.changePos(4*window.w/5, window.h/2);
    arrow_light.changePos(4*window.w/5, window.h/2);
    arrow_click.changePos(4*window.w/5, window.h/2);
    arrow_flat.newRect.shiftXY();
    arrow_light.newRect.shiftXY();
    arrow_click.newRect.shiftXY();
    renderBox(arrow_flat, arrow_light, arrow_click);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

