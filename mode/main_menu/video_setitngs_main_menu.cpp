#include "../../main.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static struct apRatio_s {
    SDL_Rect leftArrowRect;
    SDL_Rect rightArrowRect;
    unsigned int i;
    textureImage box[2];

    void render(SDL_Renderer* renderer) {
        box[i].render(renderer);
    }

} apRatioBox;

static void runVideoSettings(void);
static void renderScreen(void);
static void arrowEvent(apRatio_s* myBox, int numBoxes);
static void applyEvent(SDL_Rect rect);
static void positionArrows(void);

void video_settings_main_menu(void) {
    positionArrows();

    switch (settings.windowHeight)
    {
    case 720:
        apRatioBox.i = 0;
        break;
    
    default:
        apRatioBox.i = 1;
        break;
    }

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
                    arrowEvent(&apRatioBox, sizeof(apRatioBox.box)/sizeof(apRatioBox.box[0]));
                    applyEvent(apply_flat.newRect);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mainMenuMode = SETTINGS;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mainMenuMode = SETTINGS;
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

    apRatioBox.render(window.renderer);
    renderBox(apply_flat, apply_light, apply_click);

    arrow_flat.newRect  = apRatioBox.leftArrowRect;
    arrow_light.newRect = apRatioBox.leftArrowRect;
    arrow_click.newRect = apRatioBox.leftArrowRect;
    renderBox(arrow_flat, arrow_light, arrow_click, SDL_FLIP_HORIZONTAL);

    arrow_flat.newRect  = apRatioBox.rightArrowRect;
    arrow_light.newRect = apRatioBox.rightArrowRect;
    arrow_click.newRect = apRatioBox.rightArrowRect;
    renderBox(arrow_flat, arrow_light, arrow_click);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void arrowEvent(apRatio_s* myBox, int numBoxes) {
    if (SDL_PointInRect(&mousePos, &myBox->leftArrowRect) && (myBox->i > 0)) {
        --myBox->i;
    }
    else if (SDL_PointInRect(&mousePos, &myBox->rightArrowRect) && (myBox->i < numBoxes - 1)) {
        ++myBox->i;
    }
}

static void applyEvent(SDL_Rect rect) {
    if (SDL_PointInRect(&mousePos, &rect)) {
        switch (apRatioBox.i)
        {
        case 0:
            settings.widowWidth = 1280;
            settings.windowHeight = 720;
            window.setWindowSize(1280, 720);
            break;
        
        default:
            settings.widowWidth = 1920;
            settings.windowHeight = 1080;
            window.setWindowSize(1920, 1080);
            break;
        }

        destroyImages_mainMenu();
        imagesInit_mainMenu();

        positionArrows();

        window.setWindowPos();
    }
}

static void positionArrows(void) {
    apRatioBox.box[0] = apRatio720_flat;
    apRatioBox.box[1] = apRatio1080_flat;

    apRatioBox.leftArrowRect = {
        .x = window.w/5,
        .y = window.h/2,
        .w = arrow_flat.newRect.w,
        .h = arrow_flat.newRect.h
    };
    apRatioBox.rightArrowRect = {
        .x = 4*window.w/5,
        .y = window.h/2,
        .w = arrow_flat.newRect.w,
        .h = arrow_flat.newRect.h
    };

    apRatioBox.leftArrowRect.makeDimensions();
    apRatioBox.rightArrowRect.makeDimensions();
    apRatioBox.leftArrowRect.shiftXY();
    apRatioBox.rightArrowRect.shiftXY();
}