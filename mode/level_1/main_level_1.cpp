#include "../../main.h"
#include "main_level_1.h"
#include "map_level_1.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

#define blockLength (80)

textureImage tile;
textureImage highlight;

void main_level_1(void);

static void highlightGrid(void);
static void imagesInit_level_1(void);
static void destroyImages_level_1(void);

static void runLevel_1(void);
static void renderScreen(void);

void main_level_1(void) {
    imagesInit_level_1();

    while (mode == LEVEL_1) {
        runLevel_1();

    }

    destroyImages_level_1();
}

static void runLevel_1(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    while (mode == LEVEL_1) {
        startingTick = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mode = QUIT;
            }

            if (event.motion.type) {
                updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);

            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {

                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {

                }
                if (event.button.button == SDL_BUTTON_RIGHT) {

                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mode = MAIN_MENU;
                }
            }
        }

        frameCap(fps, startingTick);

        renderScreen();
    }
}

static void renderScreen(void) {
    window.clearRender();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tile.changePos(j*blockLength, i*blockLength);

            if (mapTiles[i][j] == 'n') {
                tile.render(window.renderer);
            }
        }
    }

    highlightGrid();
    mouseCursor.render(window.renderer);

    SDL_RenderPresent(window.renderer);
}

static void highlightGrid(void) {
    highlight.newRect.x = (xMousePos/blockLength) * blockLength;
    highlight.newRect.y = (yMousePos/blockLength) * blockLength;
    highlight.render(window.renderer);
}

void imagesInit_level_1(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);

    tile.init(window.renderer, "images/Images/level_1_images/blockDark.png", blockLength, blockLength, 0, 0);
    highlight.init(window.renderer, blue, blockLength, blockLength);
    highlight.setAlpha(100);
}

void destroyImages_level_1(void) {
    tile.destroy();
    highlight.destroy();
}
