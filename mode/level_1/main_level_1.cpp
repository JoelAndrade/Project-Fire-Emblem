#include "../../main.h"
#include "main_level_1.h"
#include "private_level_1.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>
#include <Character.h>

#define blockLength (80)

SDL_Point leftClick;
SDL_Point focus;

levelMode_t levelMode = standby;

textureImage tile;

textureImage game_flat_temp;
textureImage game_light_temp;
textureImage game_click_temp;

textureImage cursorHighlight;
textureImage moveHighlight;
textureImage attackHighlight;

textureImage textBox;

Character sprite;
map lvl1Map;

void main_level_1(void);

static void renderOptions(textureImage box_flat, textureImage box_light, textureImage box_click);
static void clickIndex(int* x, int* y);

static void pieceSelectEvent(void);

static void cursorHighlightGrid(void);

static void imagesInit(void);
static void destroyImages(void);

static void runLevel_1(void);
static void renderScreen(void);

// void menuEvent(Character* character) {
//     if (SDL_PointInRect(&leftClick, &character->image.newRect)) {
//         character->selected = true;
//     }
//     SDL_PointInRect(&leftClick, &character->image.newRect) ? character->selected = true : character->selected = false;
// }

void main_level_1(void) {
    imagesInit();

    while (mode == LEVEL_1) {
        runLevel_1();

    }

    destroyImages();
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

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = true;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = false;
                    leftClick.x = event.button.x;
                    leftClick.y = event.button.y;
                    clickIndex(&leftClick.x, &leftClick.y);

                    switch (levelMode)
                    {
                    case standby:
                        pieceSelectEvent();
                        break;
                    
                    case options:

                        break;
                    
                    case move:
                        break;

                    case stats:
                        break;

                    default:
                        levelMode = standby;
                        break;
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    levelMode = standby;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mode = MAIN_MENU;
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

    // draw the grid
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tile.changePos(j*blockLength, i*blockLength);

            if (lvl1Map.tiles[i][j] == 'n') {
                tile.render(window.renderer);
            }
        }
    }
    sprite.image.render(window.renderer); // draw the sprite

    switch (levelMode)
    {
    case standby:
        cursorHighlightGrid();
        break;
    
    case options:
        textBox.render(window.renderer);
        renderOptions(game_flat_temp, game_light_temp, game_click_temp);
        break;
    
    case move:
        break;

    case stats:
        break;

    default:
        levelMode = standby;
        break;
    }

    mouseCursor.render(window.renderer);

    SDL_RenderPresent(window.renderer);
}

static void pieceSelectEvent(void) {
    std::cout << leftClick.x << "      " << leftClick.y << std::endl;
    if (lvl1Map.collision[leftClick.y][leftClick.x] == 'p') {
        levelMode = options;
        focus = leftClick;
    }
}

static void renderOptions(textureImage box_flat, textureImage box_light, textureImage box_click) {
    if (SDL_PointInRect(&mousePos, &box_flat.newRect) && hold) {
        box_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&mousePos, &box_flat.newRect)) {
        box_light.render(window.renderer);
    }
    else {
        box_flat.render(window.renderer);
    }
}


static void cursorHighlightGrid(void) {
    cursorHighlight.newRect.x = (mousePos.x/blockLength) * blockLength;
    cursorHighlight.newRect.y = (mousePos.y/blockLength) * blockLength;
    cursorHighlight.render(window.renderer);
}

static void clickIndex(int* x, int* y) {
    *x = (*x/blockLength);
    *y = (*y/blockLength);
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);

    tile.init(window.renderer, "images/Images/level_1_images/blockDark.png", blockLength, blockLength, 0, 0);
    sprite.image.init(window.renderer, "images/Images/level_1_images/sprite.png", 0.1, 7*blockLength, 4*blockLength);

    textBox.init(window.renderer, "images/Images/level_1_images/TextBox.png", 0.28*SCALE, window.w, 0);

    game_flat_temp.init(window.renderer,   "images/Images/main_menu_images/Game.png",   0.1*SCALE, window.w, 0);
    game_light_temp.init(window.renderer,  "images/Images/main_menu_images/GameH.png",  0.1*SCALE, window.w, 0);
    game_click_temp.init(window.renderer,  "images/Images/main_menu_images/GameHL.png", 0.1*SCALE, window.w, 0);

    cursorHighlight.init(window.renderer, yellow, blockLength, blockLength);
    moveHighlight.init(window.renderer, cyan, blockLength, blockLength);
    attackHighlight.init(window.renderer, red, blockLength, blockLength);

    textBox.newRect.shiftX(2);

    game_flat_temp.newRect.shiftX(2);
    game_light_temp.newRect.shiftX(2);
    game_click_temp.newRect.shiftX(2);

    cursorHighlight.setAlpha(50);
    moveHighlight.setAlpha(100);
    attackHighlight.setAlpha(100);

}

static void destroyImages(void) {
    tile.destroy();
    sprite.~Character();
    cursorHighlight.destroy();

    textBox.destroy();

    game_flat_temp.destroy(); 
    game_light_temp.destroy(); 
    game_click_temp.destroy(); 

}
