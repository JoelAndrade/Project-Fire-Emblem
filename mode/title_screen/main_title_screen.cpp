#include "../../main.h"
#include "main_title_screen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static textureImage titleScreen;

static Mix_Music* music = NULL;

static void runTitleScreen(void);
static void renderScreen(void);
static void imagesInit(void);
static void soundInit(void);
static void destroyImages(void);
static void destroySound(void);

void main_titleScreen(void) {
    runTitleScreen();
}

static void runTitleScreen(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;
    
    SDL_SetWindowTitle(window.window, "Title");

    soundInit();
    imagesInit();

    while(mode == TITLE_SCREEN) {
        startingTick = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mode = MAIN_MENU;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mode = QUIT;
                }
                if (event.key.keysym.sym == SDLK_KP_ENTER || 
                    event.key.keysym.sym == SDLK_SPACE)
                {
                    mode = MAIN_MENU;
                }
            }
        }

        checkMouse();
        updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);
    
        renderScreen();

        frameCap(fps, startingTick);
    }

    destroyImages();
    destroySound();
}

static void renderScreen(void) {
    window.clearRender();

    titleScreen.render(window.renderer);
    mouseCursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);
    titleScreen.init(window.renderer, "images/Images/title_images/startMenu.jpg", window.w, window.h);
}

static void destroyImages(void) {
    titleScreen.destroy();
}

static void soundInit(void) {
    music = Mix_LoadMUS("sound/music/15. Understanding What We've Grown To Be.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(0);
}

static void destroySound(void) {
    Mix_FreeMusic(music);
}