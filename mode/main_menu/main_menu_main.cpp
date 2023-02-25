#include "../../main.h"
#include "main_menu_main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

textureImage background;
textureImage newGame_flat;
textureImage newGame_light;
textureImage continue_flat;
textureImage continue_light;
textureImage settings_flat;
textureImage settings_light;

static void renderScreen(void);
static void imagesInit(void);
static void destroyImages(void);

void mainMenu_main(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    SDL_SetWindowTitle(window.window, "Title");
    imagesInit();

    while(mode == MAIN_MENU) {
        startingTick = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);
            if (event.type == SDL_QUIT) {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mode = TITLE_SCREEN;
                }
            }

        }
        frameCap(fps, startingTick);

        renderScreen();
    }

    destroyImages();
}

static void renderScreen(void) {
    SDL_Point point = {
        .x = xMousePos,
        .y = yMousePos,
    };

    window.clearRender();

    background.render(window.renderer);

    SDL_PointInRect(&point, &newGame_flat.newRect)  ? newGame_light.render(window.renderer)
                                                    : newGame_flat.render(window.renderer);
    SDL_PointInRect(&point, &continue_flat.newRect) ? continue_light.render(window.renderer)
                                                    : continue_flat.render(window.renderer);
    SDL_PointInRect(&point, &settings_flat.newRect) ? settings_light.render(window.renderer)
                                                    : settings_flat.render(window.renderer);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);

    background.init(window.renderer,     "images/Images/main_menu_images/menuBackground.jpg", window.w, window.h);

    newGame_flat.init(window.renderer,   "images/Images/main_menu_images/NewGame.png",    0.2, window.w/2,     window.h/6);
    continue_flat.init(window.renderer,  "images/Images/main_menu_images/Continue.png",   0.2, window.w/2,     window.h/2);
    settings_flat.init(window.renderer,  "images/Images/main_menu_images/Settings.png",   0.2, window.w/2, (5*window.h)/6);
    newGame_light.init(window.renderer,  "images/Images/main_menu_images/NewGameHL.png",  0.2, window.w/2,     window.h/6);
    continue_light.init(window.renderer, "images/Images/main_menu_images/ContinueHL.png", 0.2, window.w/2,     window.h/2);
    settings_light.init(window.renderer, "images/Images/main_menu_images/SettingsHL.png", 0.2, window.w/2, (5*window.h)/6);

    newGame_flat.newRect.makeDimensions();
    newGame_light.newRect.makeDimensions();
    continue_light.newRect.makeDimensions();
    continue_flat.newRect.makeDimensions();
    settings_flat.newRect.makeDimensions();
    settings_light.newRect.makeDimensions();

    newGame_flat.newRect.shiftXY();
    newGame_light.newRect.shiftXY();
    continue_light.newRect.shiftXY();
    continue_flat.newRect.shiftXY();
    settings_flat.newRect.shiftXY();
    settings_light.newRect.shiftXY();
}

static void destroyImages(void) {
    background.destroy();

    newGame_flat.destroy();
    newGame_light.destroy();
    continue_light.destroy();
    continue_flat.destroy();
    settings_flat.destroy();
    settings_light.destroy();
}
