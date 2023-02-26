#include "../../main.h"
#include "main_main_menu.h"
#include "settings_main_menu.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

int mainMenuMode;
static bool hold;

SDL_Point point = {
    .x = xMousePos,
    .y = yMousePos,
};

textureImage background;

static textureImage newGame_flat;
static textureImage newGame_light;
static textureImage newGame_click;
static textureImage continue_flat;
static textureImage continue_light;
static textureImage continue_click;
static textureImage settings_flat;
static textureImage settings_light;
static textureImage settings_click;

textureImage game_flat;
textureImage game_light;
textureImage game_click;
textureImage video_flat;
textureImage video_light;
textureImage video_click;
textureImage audio_flat;
textureImage audio_light;
textureImage audio_click;



static void runMainMenu(void);
static void renderScreen(void);
static void imagesInit(void);
static void destroyImages(void);

void main_main_menu(void) {
    imagesInit();
    mainMenuMode = MAIN_MENU_MAIN;

    while (mode == MAIN_MENU) {
        if (mainMenuMode == MAIN_MENU_MAIN) {
            runMainMenu();
        }
        else if (mainMenuMode == NEWGAME) {

        }
        else if (mainMenuMode == COUNTINUE) {

        }
        else if (mainMenuMode == SETTINGS) {
            settings_main_menu();
        }
        else {
            break;
        }
    }

    destroyImages();
}

static void runMainMenu(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;


    while (mainMenuMode == MAIN_MENU_MAIN) {
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
                    mainMenuMode = SETTINGS;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
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

    if (SDL_PointInRect(&point, &newGame_flat.newRect) && hold) {
        newGame_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &newGame_flat.newRect)) {
        newGame_light.render(window.renderer);
    }
    else {
        newGame_flat.render(window.renderer);
    }

    if (SDL_PointInRect(&point, &continue_flat.newRect) && hold) {
    continue_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &continue_flat.newRect)) {
        continue_light.render(window.renderer);
    }
    else {
        continue_flat.render(window.renderer);
    }

    if (SDL_PointInRect(&point, &settings_flat.newRect) && hold) {
        settings_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&point, &settings_flat.newRect)) {
        settings_light.render(window.renderer);
    }
    else {
        settings_flat.render(window.renderer);
    }

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, &xMousePos, &yMousePos);

    background.init(window.renderer,     "images/Images/main_menu_images/menuBackground.jpg", window.w, window.h);

    newGame_flat.init(window.renderer,   "images/Images/main_menu_images/NewGame.png",    0.2, window.w/2,   window.h/6);
    newGame_light.init(window.renderer,  "images/Images/main_menu_images/NewGameH.png",   0.2, window.w/2,   window.h/6);
    newGame_click.init(window.renderer,  "images/Images/main_menu_images/NewGameHL.png",  0.2, window.w/2,   window.h/6);
    continue_flat.init(window.renderer,  "images/Images/main_menu_images/Continue.png",   0.2, window.w/2,   window.h/2);
    continue_light.init(window.renderer, "images/Images/main_menu_images/ContinueH.png",  0.2, window.w/2,   window.h/2);
    continue_click.init(window.renderer, "images/Images/main_menu_images/ContinueHL.png", 0.2, window.w/2,   window.h/2);
    settings_flat.init(window.renderer,  "images/Images/main_menu_images/Settings.png",   0.2, window.w/2, 5*window.h/6);
    settings_light.init(window.renderer, "images/Images/main_menu_images/SettingsH.png",  0.2, window.w/2, 5*window.h/6);
    settings_click.init(window.renderer, "images/Images/main_menu_images/SettingsHL.png", 0.2, window.w/2, 5*window.h/6);

    game_flat.init(window.renderer,   "images/Images/main_menu_images/Game.png",    0.2, window.w/2,   window.h/6);
    game_light.init(window.renderer,  "images/Images/main_menu_images/GameH.png",   0.2, window.w/2,   window.h/6);
    game_click.init(window.renderer,  "images/Images/main_menu_images/GameHL.png",  0.2, window.w/2,   window.h/6);
    video_flat.init(window.renderer,  "images/Images/main_menu_images/Video.png",   0.2, window.w/2,   window.h/2);
    video_light.init(window.renderer, "images/Images/main_menu_images/VideoH.png",  0.2, window.w/2,   window.h/2);
    video_click.init(window.renderer, "images/Images/main_menu_images/VideoHL.png", 0.2, window.w/2,   window.h/2);
    audio_flat.init(window.renderer,  "images/Images/main_menu_images/Audio.png",   0.2, window.w/2, 5*window.h/6);
    audio_light.init(window.renderer, "images/Images/main_menu_images/AudioH.png",  0.2, window.w/2, 5*window.h/6);
    audio_click.init(window.renderer, "images/Images/main_menu_images/AudioHL.png", 0.2, window.w/2, 5*window.h/6);

    newGame_flat.newRect.makeDimensions();
    newGame_light.newRect.makeDimensions();
    newGame_click.newRect.makeDimensions();
    continue_light.newRect.makeDimensions();
    continue_flat.newRect.makeDimensions();
    continue_click.newRect.makeDimensions();
    settings_flat.newRect.makeDimensions();
    settings_light.newRect.makeDimensions();
    settings_click.newRect.makeDimensions();

    game_flat.newRect.makeDimensions();
    game_light.newRect.makeDimensions();
    game_click.newRect.makeDimensions();
    video_light.newRect.makeDimensions();
    video_flat.newRect.makeDimensions();
    video_click.newRect.makeDimensions();
    audio_flat.newRect.makeDimensions();
    audio_light.newRect.makeDimensions();
    audio_click.newRect.makeDimensions();

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
}

static void destroyImages(void) {
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
}
