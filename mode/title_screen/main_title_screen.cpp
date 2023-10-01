#include "../../main.h"
#include "main_title_screen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static texture_image title_screen;

static void run_title_screen(void);
static void render_screen(void);
static void images_init(void);
static void sound_init(void);
static void destroy_images(void);
static void destroy_sound(void);

void main_title_screen(void)
{
    run_title_screen();
}

static void run_title_screen(void)
{
    SDL_Event event;
    int fps = 60;
    Uint32 starting_tick;
    
    SDL_SetWindowTitle(window.window, "Title");

    sound_init();
    images_init();

    while(mode == TITLE_SCREEN)
    {
        starting_tick = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mode = MAIN_MENU;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    mode = QUIT;
                }
                if (event.key.keysym.sym == SDLK_KP_ENTER || 
                    event.key.keysym.sym == SDLK_SPACE)
                {
                    mode = MAIN_MENU;
                }
            }
        }

        check_mouse();
        update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);
    
        render_screen();

        frame_cap(fps, starting_tick);
    }

    destroy_images();
    destroy_sound();
}

static void render_screen(void)
{
    window.clearRender();

    title_screen.render(window.renderer);
    mouse_cursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void images_init(void)
{
    update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);
    title_screen.init(window.renderer, "images/Images/title_images/startMenu.jpg", window.w, window.h);
}

static void destroy_images(void)
{
    title_screen.destroy();
}

static void sound_init(void)
{
    music = Mix_LoadMUS("sound/music/15. Understanding What We've Grown To Be.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(10);
}

static void destroy_sound(void)
{
    Mix_FadeOutMusic(1000);
}