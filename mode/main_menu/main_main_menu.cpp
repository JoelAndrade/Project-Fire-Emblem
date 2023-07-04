#include "../../main.h"
#include "main_main_menu.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

int mainMenuMode;

textureImage background;

option_box_t game_box;
option_box_t video_box;
option_box_t audio_box;

option_box_t apRatio1080_box;
option_box_t apRatio720_box;

static option_box_t newGame_box;
static option_box_t continue_box;
static option_box_t settings_box;

option_box_t apply_box;
option_box_t arrow_box;

static Mix_Music* music = NULL;

void menuEvent(SDL_Rect rect, int event);

void imagesInit_mainMenu(void);
void destroyImages_mainMenu(void);

static void runMainMenu(void);
static void renderScreen(void);
static void soundInit(void);
static void destroySound(void);

void menuEvent(SDL_Rect rect, int event) {
    if (SDL_PointInRect(&mousePos, &rect)) {
        mainMenuMode = event;
    }
}

void renderBox(option_box_t box) {
    if (SDL_PointInRect(&mousePos, &box.flat.newRect) && hold) {
        box.click.render(window.renderer);
    }
    else if (SDL_PointInRect(&mousePos, &box.flat.newRect)) {
        box.light.render(window.renderer);
    }
    else {
        box.flat.render(window.renderer);
    }
}
void renderBox(option_box_t box, SDL_RendererFlip) {
    if (SDL_PointInRect(&mousePos, &box.flat.newRect) && hold) {
        box.click.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else if (SDL_PointInRect(&mousePos, &box.flat.newRect)) {
        box.light.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else {
        box.flat.renderFlip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
}

void main_main_menu(void) {
    soundInit();
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
    destroySound();
}

static void runMainMenu(void) {
    SDL_Event event;
    Uint32 startingTick;

    while (mainMenuMode == MAIN_MENU_MAIN) {
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
                    menuEvent(newGame_box.flat.newRect, NEWGAME);
                    menuEvent(settings_box.flat.newRect, SETTINGS);
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

        renderScreen();

        frameCap(fps, startingTick);
    }
}

static void renderScreen(void) {
    checkMouse();
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);
    
    window.clearRender();

    background.render(window.renderer);

    renderBox(newGame_box);
    renderBox(continue_box);
    renderBox(settings_box);

    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

void imagesInit_mainMenu(void) {
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);

    background.init(window.renderer, "images/Images/main_menu_images/menuBackground.jpg", window.w, window.h);

    newGame_box.flat.init(window.renderer,   "images/Images/main_menu_images/NewGame.png",    0.2*SCALE, window.w/2,   window.h/6);
    newGame_box.light.init(window.renderer,  "images/Images/main_menu_images/NewGameH.png",   0.2*SCALE, window.w/2,   window.h/6);
    newGame_box.click.init(window.renderer,  "images/Images/main_menu_images/NewGameHL.png",  0.2*SCALE, window.w/2,   window.h/6);
    continue_box.flat.init(window.renderer,  "images/Images/main_menu_images/Continue.png",   0.2*SCALE, window.w/2,   window.h/2);
    continue_box.light.init(window.renderer, "images/Images/main_menu_images/ContinueH.png",  0.2*SCALE, window.w/2,   window.h/2);
    continue_box.click.init(window.renderer, "images/Images/main_menu_images/ContinueHL.png", 0.2*SCALE, window.w/2,   window.h/2);
    settings_box.flat.init(window.renderer,  "images/Images/main_menu_images/Settings.png",   0.2*SCALE, window.w/2, 5*window.h/6);
    settings_box.light.init(window.renderer, "images/Images/main_menu_images/SettingsH.png",  0.2*SCALE, window.w/2, 5*window.h/6);
    settings_box.click.init(window.renderer, "images/Images/main_menu_images/SettingsHL.png", 0.2*SCALE, window.w/2, 5*window.h/6);

    game_box.flat.init(window.renderer,   "images/Images/main_menu_images/Game.png",          0.2*SCALE, window.w/2,   window.h/6);
    game_box.light.init(window.renderer,  "images/Images/main_menu_images/GameH.png",         0.2*SCALE, window.w/2,   window.h/6);
    game_box.click.init(window.renderer,  "images/Images/main_menu_images/GameHL.png",        0.2*SCALE, window.w/2,   window.h/6);
    video_box.flat.init(window.renderer,  "images/Images/main_menu_images/Video.png",         0.2*SCALE, window.w/2,   window.h/2);
    video_box.light.init(window.renderer, "images/Images/main_menu_images/VideoH.png",        0.2*SCALE, window.w/2,   window.h/2);
    video_box.click.init(window.renderer, "images/Images/main_menu_images/VideoHL.png",       0.2*SCALE, window.w/2,   window.h/2);
    audio_box.flat.init(window.renderer,  "images/Images/main_menu_images/Audio.png",         0.2*SCALE, window.w/2, 5*window.h/6);
    audio_box.light.init(window.renderer, "images/Images/main_menu_images/AudioH.png",        0.2*SCALE, window.w/2, 5*window.h/6);
    audio_box.click.init(window.renderer, "images/Images/main_menu_images/AudioHL.png",       0.2*SCALE, window.w/2, 5*window.h/6);
    
    apRatio1080_box.flat.init(window.renderer,  "images/Images/main_menu_images/1080.png",    0.2*SCALE, window.w/2,   window.h/2);
    apRatio720_box.flat.init(window.renderer,   "images/Images/main_menu_images/720.png",     0.2*SCALE, window.w/2,   window.h/2);

    apply_box.flat.init(window.renderer,   "images/Images/main_menu_images/Apply.png",        0.2*SCALE, window.w/2, 5*window.h/6);
    apply_box.light.init(window.renderer,  "images/Images/main_menu_images/ApplyH.png",       0.2*SCALE, window.w/2, 5*window.h/6);
    apply_box.click.init(window.renderer,  "images/Images/main_menu_images/ApplyHL.png",      0.2*SCALE, window.w/2, 5*window.h/6);

    arrow_box.flat.init(window.renderer,  "images/Images/main_menu_images/Arrow.png",         0.2*SCALE);
    arrow_box.light.init(window.renderer, "images/Images/main_menu_images/ArrowH.png",        0.2*SCALE);
    arrow_box.click.init(window.renderer, "images/Images/main_menu_images/ArrowHL.png",       0.2*SCALE);

    newGame_box.flat.newRect.shiftXY();
    newGame_box.light.newRect.shiftXY();
    newGame_box.click.newRect.shiftXY();
    continue_box.light.newRect.shiftXY();
    continue_box.flat.newRect.shiftXY();
    continue_box.click.newRect.shiftXY();
    settings_box.flat.newRect.shiftXY();
    settings_box.light.newRect.shiftXY();
    settings_box.click.newRect.shiftXY();

    game_box.flat.newRect.shiftXY();
    game_box.light.newRect.shiftXY();
    game_box.click.newRect.shiftXY();
    video_box.light.newRect.shiftXY();
    video_box.flat.newRect.shiftXY();
    video_box.click.newRect.shiftXY();
    audio_box.flat.newRect.shiftXY();
    audio_box.light.newRect.shiftXY();
    audio_box.click.newRect.shiftXY();

    apRatio1080_box.flat.newRect.shiftXY();
    apRatio720_box.flat.newRect.shiftXY();

    apply_box.flat.newRect.shiftXY();
    apply_box.light.newRect.shiftXY();
    apply_box.click.newRect.shiftXY();

    arrow_box.flat.newRect.shiftXY();
    arrow_box.light.newRect.shiftXY();
    arrow_box.click.newRect.shiftXY();
}

void destroyImages_mainMenu(void) {
    background.destroy();

    newGame_box.flat.destroy();
    newGame_box.light.destroy();
    newGame_box.click.destroy();
    continue_box.light.destroy();
    continue_box.flat.destroy();
    continue_box.click.destroy();
    settings_box.flat.destroy();
    settings_box.light.destroy();
    settings_box.click.destroy();

    game_box.flat.destroy();
    game_box.light.destroy();
    game_box.click.destroy();
    video_box.light.destroy();
    video_box.flat.destroy();
    video_box.click.destroy();
    audio_box.flat.destroy();
    audio_box.light.destroy();
    audio_box.click.destroy();

    apRatio1080_box.flat.destroy();
    apRatio720_box.flat.destroy();

    apply_box.flat.destroy();
    apply_box.light.destroy();
    apply_box.click.destroy();

    arrow_box.flat.destroy();
    arrow_box.light.destroy();
    arrow_box.click.destroy();
}

static void soundInit(void) {
    music = Mix_LoadMUS("sound/music/Fire Emblem Theme.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(10);
}

static void destroySound(void) {
    Mix_FreeMusic(music);
}
