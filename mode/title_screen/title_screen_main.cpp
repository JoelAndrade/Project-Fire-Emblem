#include "../../main.h"
#include "title_screen_main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

textureImage titleScreen;

static void imagesInit(void);
static void destroyImages(void);

void titleScreen_main(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    SDL_SetWindowTitle(window.window, "Title");
    imagesInit();

    while(mode == TITLE_SCREEN) {
        startingTick = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
            if (event.type == SDL_QUIT) {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mode = MAIN_MENU;
                }
            }

        }
        frameCap(fps, startingTick);

        window.clearRender();

        titleScreen.render(window.renderer);
        mouseCursor.render(window.renderer);

        SDL_RenderPresent(window.renderer);
    }

    destroyImages();
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
    titleScreen.init(window.renderer, "images/Images/title_images/startMenu.jpg", window.w, window.h);
}

static void destroyImages(void) {
    titleScreen.destroy();
}