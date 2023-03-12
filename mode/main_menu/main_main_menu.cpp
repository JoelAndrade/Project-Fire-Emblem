#include "../../main.h"
#include "main_main_menu.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

int mainMenuMode;
bool hold;

SDL_Point point = {
    .x = xMousePos,
    .y = yMousePos,
};

textureImage background;

textureImage game_flat;
textureImage game_light;
textureImage game_click;
textureImage video_flat;
textureImage video_light;
textureImage video_click;
textureImage audio_flat;
textureImage audio_light;
textureImage audio_click;

textureImage apRatio1080_flat;
textureImage apRatio1080_light;
textureImage apRatio1080_click;
textureImage apRatio720_flat;
textureImage apRatio720_light;
textureImage apRatio720_click;

static textureImage newGame_flat;
static textureImage newGame_light;
static textureImage newGame_click;
static textureImage continue_flat;
static textureImage continue_light;
static textureImage continue_click;
static textureImage settings_flat;
static textureImage settings_light;
static textureImage settings_click;

textureImage apply_flat;
textureImage apply_light;
textureImage apply_click;

textureImage arrow_flat;
textureImage arrow_light;
textureImage arrow_click;

void menuEvent(SDL_Rect rect, int event);
void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click, SDL_RendererFlip);
void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click);

void imagesInit_mainMenu(void);
void destroyImages_mainMenu(void);

static void runMainMenu(void);
static void renderScreen(void);

void menuEvent(SDL_Rect rect, int event) {
    point = {
        .x = xMousePos,
        .y = yMousePos,
    };

    if (SDL_PointInRect(&point, &rect)) {
        mainMenuMode = event;
    }
}

void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click) {
    if (SDL_PointInRect(&point, &box_flat.newRect) && hold) {
        box_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &box_flat.newRect)) {
        box_light.render(window.renderer);
    }
    else {
        box_flat.render(window.renderer);
    }
}
void renderBox(textureImage box_flat, textureImage box_light, textureImage box_click, SDL_RendererFlip) {
    if (SDL_PointInRect(&point, &box_flat.newRect) && hold) {
        box_click.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else if (SDL_PointInRect(&point, &box_flat.newRect)) {
        box_light.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else {
        box_flat.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
}

void main_main_menu(void) {
    imagesInit_mainMenu();
    mainMenuMode = MAIN_MENU_MAIN;

    while (mode == MAIN_MENU) {
        runMainMenu();

        if (mainMenuMode == NEWGAME) {
            mode = LEVEL_1;
        }
        else if (mainMenuMode == COUNTINUE) {

        }
        else if (mainMenuMode == SETTINGS) {
            settings_main_menu();
        }
    }

    destroyImages_mainMenu();
}

static void runMainMenu(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;


    while (mainMenuMode == MAIN_MENU_MAIN) {
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
                    menuEvent(newGame_flat.newRect, NEWGAME);
                    menuEvent(settings_flat.newRect, SETTINGS);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mainMenuMode = QUIT_MAIN_MENU;
                    mode = TITLE_SCREEN;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mainMenuMode = QUIT_MAIN_MENU;
                    mode = TITLE_SCREEN;
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

    renderBox(newGame_flat, newGame_light, newGame_click);
    renderBox(continue_flat, continue_light, continue_click);
    renderBox(settings_flat, settings_light, settings_click);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

void imagesInit_mainMenu(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);

    background.init(window.renderer, "images/Images/main_menu_images/menuBackground.jpg", window.w, window.h);

    newGame_flat.init(window.renderer,   "images/Images/main_menu_images/NewGame.png",    0.2*SCALE, window.w/2,   window.h/6);
    newGame_light.init(window.renderer,  "images/Images/main_menu_images/NewGameH.png",   0.2*SCALE, window.w/2,   window.h/6);
    newGame_click.init(window.renderer,  "images/Images/main_menu_images/NewGameHL.png",  0.2*SCALE, window.w/2,   window.h/6);
    continue_flat.init(window.renderer,  "images/Images/main_menu_images/Continue.png",   0.2*SCALE, window.w/2,   window.h/2);
    continue_light.init(window.renderer, "images/Images/main_menu_images/ContinueH.png",  0.2*SCALE, window.w/2,   window.h/2);
    continue_click.init(window.renderer, "images/Images/main_menu_images/ContinueHL.png", 0.2*SCALE, window.w/2,   window.h/2);
    settings_flat.init(window.renderer,  "images/Images/main_menu_images/Settings.png",   0.2*SCALE, window.w/2, 5*window.h/6);
    settings_light.init(window.renderer, "images/Images/main_menu_images/SettingsH.png",  0.2*SCALE, window.w/2, 5*window.h/6);
    settings_click.init(window.renderer, "images/Images/main_menu_images/SettingsHL.png", 0.2*SCALE, window.w/2, 5*window.h/6);

    game_flat.init(window.renderer,   "images/Images/main_menu_images/Game.png",          0.2*SCALE, window.w/2,   window.h/6);
    game_light.init(window.renderer,  "images/Images/main_menu_images/GameH.png",         0.2*SCALE, window.w/2,   window.h/6);
    game_click.init(window.renderer,  "images/Images/main_menu_images/GameHL.png",        0.2*SCALE, window.w/2,   window.h/6);
    video_flat.init(window.renderer,  "images/Images/main_menu_images/Video.png",         0.2*SCALE, window.w/2,   window.h/2);
    video_light.init(window.renderer, "images/Images/main_menu_images/VideoH.png",        0.2*SCALE, window.w/2,   window.h/2);
    video_click.init(window.renderer, "images/Images/main_menu_images/VideoHL.png",       0.2*SCALE, window.w/2,   window.h/2);
    audio_flat.init(window.renderer,  "images/Images/main_menu_images/Audio.png",         0.2*SCALE, window.w/2, 5*window.h/6);
    audio_light.init(window.renderer, "images/Images/main_menu_images/AudioH.png",        0.2*SCALE, window.w/2, 5*window.h/6);
    audio_click.init(window.renderer, "images/Images/main_menu_images/AudioHL.png",       0.2*SCALE, window.w/2, 5*window.h/6);
    
    apRatio1080_flat.init(window.renderer,  "images/Images/main_menu_images/1080.png",    0.2*SCALE, window.w/2,   window.h/2);
    apRatio720_flat.init(window.renderer,   "images/Images/main_menu_images/720.png",     0.2*SCALE, window.w/2,   window.h/2);

    apply_flat.init(window.renderer,   "images/Images/main_menu_images/Apply.png",        0.2*SCALE, window.w/2, 5*window.h/6);
    apply_light.init(window.renderer,  "images/Images/main_menu_images/ApplyH.png",       0.2*SCALE, window.w/2, 5*window.h/6);
    apply_click.init(window.renderer,  "images/Images/main_menu_images/ApplyHL.png",      0.2*SCALE, window.w/2, 5*window.h/6);

    arrow_flat.init(window.renderer,  "images/Images/main_menu_images/Arrow.png",         0.2*SCALE);
    arrow_light.init(window.renderer, "images/Images/main_menu_images/ArrowH.png",        0.2*SCALE);
    arrow_click.init(window.renderer, "images/Images/main_menu_images/ArrowHL.png",       0.2*SCALE);

    newGame_flat.newRect.shiftXY();
    newGame_light.newRect.shiftXY();
    newGame_click.newRect.shiftXY();
    continue_light.newRect.shiftXY();
    continue_flat.newRect.shiftXY();
    continue_click.newRect.shiftXY();
    settings_flat.newRect.shiftXY();
    settings_light.newRect.shiftXY();
    settings_click.newRect.shiftXY();

    game_flat.newRect.shiftXY();
    game_light.newRect.shiftXY();
    game_click.newRect.shiftXY();
    video_light.newRect.shiftXY();
    video_flat.newRect.shiftXY();
    video_click.newRect.shiftXY();
    audio_flat.newRect.shiftXY();
    audio_light.newRect.shiftXY();
    audio_click.newRect.shiftXY();

    apRatio1080_flat.newRect.shiftXY();
    apRatio720_flat.newRect.shiftXY();

    apply_flat.newRect.shiftXY();
    apply_light.newRect.shiftXY();
    apply_click.newRect.shiftXY();

    arrow_flat.newRect.shiftXY();
    arrow_light.newRect.shiftXY();
    arrow_click.newRect.shiftXY();
}

void destroyImages_mainMenu(void) {
    background.destroy();

    newGame_flat.destroy();
    newGame_light.destroy();
    newGame_click.destroy();
    continue_light.destroy();
    continue_flat.destroy();
    continue_click.destroy();
    settings_flat.destroy();
    settings_light.destroy();
    settings_click.destroy();

    game_flat.destroy();
    game_light.destroy();
    game_click.destroy();
    video_light.destroy();
    video_flat.destroy();
    video_click.destroy();
    audio_flat.destroy();
    audio_light.destroy();
    audio_click.destroy();

    apRatio1080_flat.destroy();
    apRatio1080_light.destroy();
    apRatio1080_click.destroy();
    apRatio720_flat.destroy();
    apRatio720_light.destroy();
    apRatio720_click.destroy();

    apply_flat.destroy();
    apply_light.destroy();
    apply_click.destroy();

    arrow_flat.destroy();
    arrow_light.destroy();
    arrow_click.destroy();
}
