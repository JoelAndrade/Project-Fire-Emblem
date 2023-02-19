#include "../../main.h"
#include "title_screen_main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

textureImage titleScreen;

static void imagesInit();

void runTitleScreen(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    SDL_GetMouseState(&xMousePos, &yMousePos);
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
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mode = MAIN_MENU;
                    return;
                }
            }

        }
        frameCap(fps, startingTick);

        window.clearRender();

        titleScreen.render(window.renderer);
        mouseCursor.render(window.renderer);

        SDL_RenderPresent(window.renderer);
    }

}

static void imagesInit() {
    mouseCursor.init(window.renderer, "images/Images/Cursor.png", 100, 100, xMousePos, yMousePos);
    titleScreen.init(window.renderer, "images/Images/title_images/Start Menu.jpg", window.w, window.h);
}