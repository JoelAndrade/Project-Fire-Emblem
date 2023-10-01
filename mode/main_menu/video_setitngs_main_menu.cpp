#include "../../main.h"
#include "private_main_menu.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

static struct ap_ratio_s {
    SDL_Rect left_arrow_rect;
    SDL_Rect right_arrow_rect;
    unsigned int i;
    texture_image box[2];

    void render(SDL_Renderer* renderer)
    {
        box[i].render(renderer);
    }

} ap_ratio_box;

static void run_video_settings(void);
static void render_screen(void);
static void arrow_event(ap_ratio_s* myBox, int numBoxes);
static void apply_event(SDL_Rect* rect);
static void position_arrows(void);

void video_settings_main_menu(void)
{
    position_arrows();

    switch (settings.window_height)
    {
    case 720:
        ap_ratio_box.i = 0;
        break;
    
    default:
        ap_ratio_box.i = 1;
        break;
    }

    run_video_settings();
}

static void run_video_settings(void)
{
    SDL_Event event;
    Uint32 startingTick;

    while (main_menu_mode == VIDEO_SETTINGS)
    {
        startingTick = SDL_GetTicks();

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
                    arrow_event(&ap_ratio_box, sizeof(ap_ratio_box.box)/sizeof(ap_ratio_box.box[0]));
                    apply_event(&apply_box.flat.new_rect);
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    main_menu_mode = SETTINGS;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    main_menu_mode = SETTINGS;
                }
            }
        }

        render_screen();
        
        frame_cap(fps, startingTick);
    }
}

static void render_screen(void)
{
    check_mouse();
    update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);
    
    window.clearRender();

    background.render(window.renderer);

    ap_ratio_box.render(window.renderer);
    render_box(&apply_box);

    arrow_box.flat.new_rect  = ap_ratio_box.left_arrow_rect;
    arrow_box.light.new_rect = ap_ratio_box.left_arrow_rect;
    arrow_box.click.new_rect = ap_ratio_box.left_arrow_rect;
    render_box(&arrow_box, SDL_FLIP_HORIZONTAL);

    arrow_box.flat.new_rect  = ap_ratio_box.right_arrow_rect;
    arrow_box.light.new_rect = ap_ratio_box.right_arrow_rect;
    arrow_box.click.new_rect = ap_ratio_box.right_arrow_rect;
    render_box(&arrow_box);

    mouse_cursor.render(window.renderer);
    
    SDL_RenderPresent(window.renderer);
}

static void arrow_event(ap_ratio_s* myBox, int numBoxes)
{
    if (SDL_PointInRect(&mouse_pos, &myBox->left_arrow_rect) && (myBox->i > 0))
    {
        myBox->i--;
    }
    else if (SDL_PointInRect(&mouse_pos, &myBox->right_arrow_rect) && (myBox->i < numBoxes - 1))
    {
        myBox->i++;
    }
}

static void apply_event(SDL_Rect* rect)
{
    if (SDL_PointInRect(&mouse_pos, rect))
    {
        switch (ap_ratio_box.i)
        {
        case 0:
            settings.widow_width = 1280;
            settings.window_height = 720;
            window.set_window_size(1280, 720);
            break;
        
        default:
            settings.widow_width = 1920;
            settings.window_height = 1080;
            window.set_window_size(1920, 1080);
            break;
        }

        destroy_images_main_menu();
        images_init_main_menu();

        position_arrows();

        window.set_window_pos();
    }
}

static void position_arrows(void)
{
    ap_ratio_box.box[0] = ap_ratio_720_box.flat;
    ap_ratio_box.box[1] = ap_ratio_1080_box.flat;

    ap_ratio_box.left_arrow_rect = {
        .x = window.w/5,
        .y = window.h/2,
        .w = arrow_box.flat.new_rect.w,
        .h = arrow_box.flat.new_rect.h
    };
    ap_ratio_box.right_arrow_rect = {
        .x = 4*window.w/5,
        .y = window.h/2,
        .w = arrow_box.flat.new_rect.w,
        .h = arrow_box.flat.new_rect.h
    };

    ap_ratio_box.left_arrow_rect.makeDimensions();
    ap_ratio_box.right_arrow_rect.makeDimensions();
    ap_ratio_box.left_arrow_rect.shiftXY();
    ap_ratio_box.right_arrow_rect.shiftXY();
}