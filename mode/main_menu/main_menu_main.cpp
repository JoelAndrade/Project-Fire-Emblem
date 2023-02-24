#include "../../main.h"
#include "main_menu_main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static void imagesInit(void);

void runMainMenu(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    SDL_SetWindowTitle(window.window, "Title");
    imagesInit();

    while(true) {
        startingTick = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
            if (event.type == SDL_QUIT) {
                mode = QUIT;
                return;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mode = TITLE_SCREEN;
                    return;
                }
            }

        }
        frameCap(fps, startingTick);

        window.clearRender();

        mouseCursor.render(window.renderer);

        SDL_RenderPresent(window.renderer);
    }

}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
}

static void destroyImages(void) {

}