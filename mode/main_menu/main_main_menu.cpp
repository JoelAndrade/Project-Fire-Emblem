#include "../../main.h"
#include "main_main_menu.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

int main_menu_mode;

texture_image background;

option_box_t game_box;
option_box_t video_box;
option_box_t audio_box;

option_box_t ap_ratio_1080_box;
option_box_t ap_ratio_720_box;

static option_box_t new_game_box;
static option_box_t continue_box;
static option_box_t settings_box;

option_box_t apply_box;
option_box_t arrow_box;

static Mix_Music* music = NULL;

static void run_main_menu(void);
static void render_screen(void);
static void sound_init(void);
static void destroy_sound(void);

void menu_event(SDL_Rect rect, int event)
{
    if (SDL_PointInRect(&mouse_pos, &rect))
    {
        main_menu_mode = event;
    }
}

void render_box(option_box_t box)
{
    if (SDL_PointInRect(&mouse_pos, &box.flat.new_rect) && hold)
    {
        box.click.render(window.renderer);
    }
    else if (SDL_PointInRect(&mouse_pos, &box.flat.new_rect))
    {
        box.light.render(window.renderer);
    }
    else
    {
        box.flat.render(window.renderer);
    }
}
void render_box(option_box_t box, SDL_RendererFlip)
{
    if (SDL_PointInRect(&mouse_pos, &box.flat.new_rect) && hold)
    {
        box.click.render_flip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else if (SDL_PointInRect(&mouse_pos, &box.flat.new_rect))
    {
        box.light.render_flip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        box.flat.render_flip(window.renderer, SDL_FLIP_HORIZONTAL);
    }
}

void main_main_menu(void)
{
    sound_init();
    images_init_main_menu();
    main_menu_mode = MAIN_MENU_MAIN;

    while (mode == MAIN_MENU)
    {
        run_main_menu();

        if (main_menu_mode == NEWGAME)
        {
            mode = LEVEL_1;
        }
        else if (main_menu_mode == COUNTINUE)
        {

        }
        else if (main_menu_mode == SETTINGS)
        {
            settings_main_menu();
        }
    }

    destroy_images_main_menu();
    destroy_sound();
}

static void run_main_menu(void) {
    SDL_Event event;
    Uint32 starting_tick;

    while (main_menu_mode == MAIN_MENU_MAIN)
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
                    menu_event(new_game_box.flat.new_rect, NEWGAME);
                    menu_event(settings_box.flat.new_rect, SETTINGS);
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    main_menu_mode = QUIT_MAIN_MENU;
                    mode = TITLE_SCREEN;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    main_menu_mode = QUIT_MAIN_MENU;
                    mode = TITLE_SCREEN;
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

    render_box(new_game_box);
    render_box(continue_box);
    render_box(settings_box);

    mouse_cursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

void images_init_main_menu(void)
{
    update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);

    background.init(window.renderer, "images/Images/main_menu_images/menuBackground.jpg", window.w, window.h);

    new_game_box.flat.init(window.renderer,   "images/Images/main_menu_images/NewGame.png",    0.2*SCALE, window.w/2,   window.h/6);
    new_game_box.light.init(window.renderer,  "images/Images/main_menu_images/NewGameH.png",   0.2*SCALE, window.w/2,   window.h/6);
    new_game_box.click.init(window.renderer,  "images/Images/main_menu_images/NewGameHL.png",  0.2*SCALE, window.w/2,   window.h/6);
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
    
    ap_ratio_1080_box.flat.init(window.renderer,  "images/Images/main_menu_images/1080.png",    0.2*SCALE, window.w/2,   window.h/2);
    ap_ratio_720_box.flat.init(window.renderer,   "images/Images/main_menu_images/720.png",     0.2*SCALE, window.w/2,   window.h/2);

    apply_box.flat.init(window.renderer,   "images/Images/main_menu_images/Apply.png",        0.2*SCALE, window.w/2, 5*window.h/6);
    apply_box.light.init(window.renderer,  "images/Images/main_menu_images/ApplyH.png",       0.2*SCALE, window.w/2, 5*window.h/6);
    apply_box.click.init(window.renderer,  "images/Images/main_menu_images/ApplyHL.png",      0.2*SCALE, window.w/2, 5*window.h/6);

    arrow_box.flat.init(window.renderer,  "images/Images/main_menu_images/Arrow.png",         0.2*SCALE);
    arrow_box.light.init(window.renderer, "images/Images/main_menu_images/ArrowH.png",        0.2*SCALE);
    arrow_box.click.init(window.renderer, "images/Images/main_menu_images/ArrowHL.png",       0.2*SCALE);

    new_game_box.flat.new_rect.shiftXY();
    new_game_box.light.new_rect.shiftXY();
    new_game_box.click.new_rect.shiftXY();
    continue_box.light.new_rect.shiftXY();
    continue_box.flat.new_rect.shiftXY();
    continue_box.click.new_rect.shiftXY();
    settings_box.flat.new_rect.shiftXY();
    settings_box.light.new_rect.shiftXY();
    settings_box.click.new_rect.shiftXY();

    game_box.flat.new_rect.shiftXY();
    game_box.light.new_rect.shiftXY();
    game_box.click.new_rect.shiftXY();
    video_box.light.new_rect.shiftXY();
    video_box.flat.new_rect.shiftXY();
    video_box.click.new_rect.shiftXY();
    audio_box.flat.new_rect.shiftXY();
    audio_box.light.new_rect.shiftXY();
    audio_box.click.new_rect.shiftXY();

    ap_ratio_1080_box.flat.new_rect.shiftXY();
    ap_ratio_720_box.flat.new_rect.shiftXY();

    apply_box.flat.new_rect.shiftXY();
    apply_box.light.new_rect.shiftXY();
    apply_box.click.new_rect.shiftXY();

    arrow_box.flat.new_rect.shiftXY();
    arrow_box.light.new_rect.shiftXY();
    arrow_box.click.new_rect.shiftXY();
}

void destroy_images_main_menu(void)
{
    background.destroy();

    new_game_box.flat.destroy();
    new_game_box.light.destroy();
    new_game_box.click.destroy();
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

    ap_ratio_1080_box.flat.destroy();
    ap_ratio_720_box.flat.destroy();

    apply_box.flat.destroy();
    apply_box.light.destroy();
    apply_box.click.destroy();

    arrow_box.flat.destroy();
    arrow_box.light.destroy();
    arrow_box.click.destroy();
}

static void sound_init(void)
{
    music = Mix_LoadMUS("sound/music/Fire Emblem Theme.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(10);
}

static void destroy_sound(void)
{
    Mix_FreeMusic(music);
}
