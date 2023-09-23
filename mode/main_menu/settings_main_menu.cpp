#include "../../main.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static void run_settings(void);
static void render_screen(void);

void settings_main_menu(void)
{
    while (main_menu_mode == SETTINGS)
    {
        run_settings();

        if (main_menu_mode == GAME_SETTINGS)
        {

        }
        else if (main_menu_mode == VIDEO_SETTINGS)
        {
            video_settings_main_menu();
        }
        else if (main_menu_mode == AUDIO_SETTINGS)
        {

        }
    }
}

static void run_settings(void)
{
    SDL_Event event;
    Uint32 starting_tick;

    while (main_menu_mode == SETTINGS)
    {
        starting_tick = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                main_menu_mode = QUIT_MAIN_MENU;
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    hold = event.button.state;
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {

                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    hold = event.button.state;
                    menu_event(video_box.flat.new_rect, VIDEO_SETTINGS);
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    main_menu_mode = MAIN_MENU_MAIN;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    main_menu_mode = MAIN_MENU_MAIN;
                }
            }
        }
        
        render_screen();

        frame_cap(fps, starting_tick);
    }
}

static void render_screen(void)
{
    check_mouse();
    update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);
    
    window.clearRender();

    background.render(window.renderer);

    render_box(game_box);
    render_box(video_box);
    render_box(audio_box);

    mouse_cursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

