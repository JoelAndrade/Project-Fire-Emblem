#include "../../main.h"
#include "../../debug.h"
#include "main_level_1.h"
#include "private_level_1.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>
#include <character.h>

#define BLOCK_LENGTH     (80)
#define OPTION_BLOCK  (0.075)
#define CAMERA_CHANGE    (10)
#define REVERT (true)

SDL_Point left_click;
SDL_Point focus;
SDL_Point camera;

levelMode_t level_mode;

texture_image tile;
texture_image dirt_tile;
texture_image grass_tile;
texture_image house_tile;
texture_image stone_tile;
texture_image tree_tile;
texture_image water_tile;

option_box_t attack_box;
option_box_t items_box;
option_box_t move_box;
option_box_t stats_box;
option_box_t wait_box;
option_box_t settings_box;

texture_image cursor_highlight;
texture_image move_highlight;
texture_image attack_highlight;

texture_image text_box;

Character hero_sprite;
Character villain_sprite;
Character* character_select;
map lvl1_map;

static void render_options(option_box_t* box);
static void render_move_highlight(void);
static void render_attck_highlight(void);
static bool render_attack_box(int i, int j);
static void render_post_move_attack(int i, int j);
static void render_cursor_highlight_grid(void);

static void piece_select_event(void);
static bool outside_textbox_event(void);
static bool option_select_event(SDL_Rect* rect, levelMode_t modeSelect);
static bool move_event(bool revert = false);
static void attack_event(void);

static void click_index(int* x, int* y);
static void ajust_sprites(int xAjust, int yAjust);
static void arrage_text(int numBoxes, ...);

static void images_init(void);
static void destroy_images(void);
static void sprites_init(void);

static void run_level_1(void);
static void render_screen(void);

void main_level_1(void)
{
    images_init();
    sprites_init();
    level_mode = DEFAULT;
    camera.x = 0;
    camera.y = 0;
    while (mode == LEVEL_1)
    {
        run_level_1();
    }

    destroy_images();
}

static void run_level_1(void)
{
    SDL_Event event;
    Uint32 starting_tick;

    while (mode == LEVEL_1)
    {
        starting_tick = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    hold = true;
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    hold = false;
                    left_click.x = event.button.x;
                    left_click.y = event.button.y;
                    click_index(&left_click.x, &left_click.y);

                    switch (level_mode)
                    {
                    case DEFAULT:
                        piece_select_event();
                        break;
                    
                    case OPTIONS:
                        if (!outside_textbox_event())
                        {
                            option_select_event(&settings_box.flat.new_rect, SETTINGS);
                        }
                        break;
                    
                    case PIECE_SELECT:
                        if (character_select->allegiance == HERO)
                        {
                            if (move_event());
                            else if (!outside_textbox_event())
                            {
                                option_select_event(&move_box.flat.new_rect, MOVE);
                                if (option_select_event(&items_box.flat.new_rect, ITEM))
                                {
                                    arrage_text(5, &wait_box, &attack_box, &move_box, &items_box, &stats_box);
                                }
                                option_select_event(&settings_box.flat.new_rect, SETTINGS);
                            }
                        }
                        else
                        {
                            if (!outside_textbox_event())
                            {
                                option_select_event(&stats_box.flat.new_rect, STATS);
                                option_select_event(&settings_box.flat.new_rect, SETTINGS);
                            }
                        }
                        break;
                    
                    case MOVE:
                        move_event();
                        break;

                    case ITEM:
                        break;

                    case POSTMOVE:
                        option_select_event(&wait_box.flat.new_rect, DEFAULT);
                        if (render_attack_box(character_select->i, character_select->j))
                        {
                            option_select_event(&attack_box.flat.new_rect, ATTACK);
                        }
                        break;

                    case ATTACK:
                        attack_event();
                        break;

                    case STATS:
                        break;

                    case SETTINGS:
                        break;

                    default:
                        level_mode = DEFAULT;
                        break;
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    switch (level_mode)
                    {
                    case DEFAULT:
                        break;
                    
                    case OPTIONS:
                        level_mode = DEFAULT;
                        break;
                    
                    case PIECE_SELECT:
                        level_mode = DEFAULT;
                        break;
                    
                    case MOVE:
                        level_mode = PIECE_SELECT;
                        break;
                    
                    case ITEM:
                        level_mode = PIECE_SELECT;
                        arrage_text(4, &move_box, &items_box, &stats_box, &settings_box);
                        break;

                    case POSTMOVE:
                        move_event(REVERT);
                        break;

                    case ATTACK:
                        level_mode = POSTMOVE;
                        break;

                    case STATS:
                        level_mode = DEFAULT;
                        break;

                    case SETTINGS:
                        level_mode = DEFAULT;
                        break;

                    default:
                        level_mode = DEFAULT;
                        break;
                    }
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    mode = MAIN_MENU;
                }
                if (event.key.keysym.sym == SDLK_w)
                {
                    if (camera.y > 0)
                    {
                        camera.y -= CAMERA_CHANGE;
                        ajust_sprites(0, -CAMERA_CHANGE);
                    }
                }
                if (event.key.keysym.sym == SDLK_a)
                {
                    if (camera.x > 0)
                    {
                        camera.x -= CAMERA_CHANGE;
                        ajust_sprites(-CAMERA_CHANGE, 0);
                    }
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    if (camera.y < window.h)
                    {
                        camera.y += CAMERA_CHANGE;
                        ajust_sprites(0, CAMERA_CHANGE);
                    }
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    if (camera.x < window.w)
                    {
                        camera.x += CAMERA_CHANGE;
                        ajust_sprites(CAMERA_CHANGE, 0);
                    }
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

    // draw the grid
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            switch (lvl1_map.tiles[i][j])
            {
            case 'n':
                tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                tile.render(window.renderer);
                break;
            
            case 'd':
                dirt_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                dirt_tile.render(window.renderer);
                break;

            case 'g':
                grass_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                grass_tile.render(window.renderer);
                break;

            case 'h':
                house_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                house_tile.render(window.renderer);
                break;

            case 's':
                stone_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                stone_tile.render(window.renderer);
                break;

            case 't':
                tree_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                tree_tile.render(window.renderer);
                break;

            case 'w':
                water_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                water_tile.render(window.renderer);
                break;

            default:
                break;
            }
        }
    }

    // draw the sprites
    hero_sprite.image.render(window.renderer);
    villain_sprite.image.render(window.renderer);

    switch (level_mode)
    {
    case DEFAULT:
        render_cursor_highlight_grid();
        break;
    
    case OPTIONS:
        text_box.render(window.renderer);
        render_options(&settings_box);
        break;
    
    case PIECE_SELECT:
        render_move_highlight();
        render_attck_highlight();
        render_cursor_highlight_grid();

        text_box.render(window.renderer);
        if (character_select->allegiance == HERO)
        {
            render_options(&move_box);
            render_options(&items_box);
            render_options(&stats_box);
            render_options(&settings_box);
        }
        else
        {
            render_options(&items_box);
            render_options(&stats_box);
            render_options(&settings_box);
        }
        break;

    case MOVE:
        render_move_highlight();
        render_attck_highlight();
        render_cursor_highlight_grid();
        break;

    case ITEM:
        text_box.render(window.renderer);
        render_options(&wait_box);
        render_options(&attack_box);
        render_options(&move_box);
        render_options(&items_box);
        render_options(&stats_box);
        break;

    case POSTMOVE:
        render_cursor_highlight_grid();
        
        text_box.render(window.renderer);
        render_options(&wait_box);
        if (render_attack_box(character_select->i, character_select->j))
        {
            render_options(&attack_box);
        }
        break;

    case ATTACK:
        render_post_move_attack(character_select->i, character_select->j);
        render_cursor_highlight_grid();
        break;

    case STATS:
        break;

    case SETTINGS:
        break;

    default:
        level_mode = DEFAULT;
        break;
    }

    mouse_cursor.render(window.renderer);

    SDL_RenderPresent(window.renderer);
}

static void render_move_highlight(void)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (LIMITS('1', lvl1_map.move_attack_spaces[i][j], character_select->moves + '0'))
            {
                move_highlight.new_rect.x = j*BLOCK_LENGTH - camera.x;
                move_highlight.new_rect.y = i*BLOCK_LENGTH - camera.y;
                move_highlight.render(window.renderer);
            }
        }
    }
}

static void render_attck_highlight(void)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (lvl1_map.move_attack_spaces[i][j] == 'a')
            {
                attack_highlight.new_rect.x = j*BLOCK_LENGTH - camera.x;
                attack_highlight.new_rect.y = i*BLOCK_LENGTH - camera.y;
                attack_highlight.render(window.renderer);
            }
        }
    }
}

static void render_post_move_attack(int i, int j)
{
    if (lvl1_map.piece_locations[i - 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i - 1][j]->allegiance != HERO)
        {                                                                 // [ ][x][ ]
            attack_highlight.new_rect.x =       j*BLOCK_LENGTH - camera.x; // [ ][o][ ]
            attack_highlight.new_rect.y = (i - 1)*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render(window.renderer);
        }
    }

    if (lvl1_map.piece_locations[i][j - 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j - 1]->allegiance != HERO)
        {                                                                 // [ ][ ][ ]
            attack_highlight.new_rect.x = (j - 1)*BLOCK_LENGTH - camera.x; // [x][o][ ]
            attack_highlight.new_rect.y =       i*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render(window.renderer);
        }
    }

    if (lvl1_map.piece_locations[i][j + 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j + 1]->allegiance != HERO)
        {                                                                 // [ ][ ][ ]
            attack_highlight.new_rect.x = (j + 1)*BLOCK_LENGTH - camera.x; // [ ][o][x]
            attack_highlight.new_rect.y =       i*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render(window.renderer);
        }
    }

    if (lvl1_map.piece_locations[i + 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i + 1][j]->allegiance != HERO)
        {                                                                 // [ ][ ][ ]
            attack_highlight.new_rect.x =       j*BLOCK_LENGTH - camera.x; // [ ][o][ ]
            attack_highlight.new_rect.y = (i + 1)*BLOCK_LENGTH - camera.y; // [ ][x][ ]
            attack_highlight.render(window.renderer);
        }
    }
}

static bool render_attack_box(int i, int j)
{
    if (lvl1_map.piece_locations[i - 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i - 1][j]->allegiance != HERO)
        {
            return true;
        }
    }

    if (lvl1_map.piece_locations[i][j - 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j - 1]->allegiance != HERO)
        {
            return true;
        }
    }

    if (lvl1_map.piece_locations[i][j + 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j + 1]->allegiance != HERO)
        {
            return true;
        }
    }

    if (lvl1_map.piece_locations[i + 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i + 1][j]->allegiance != HERO)
        {
            return true;
        }
    }

    return false;
}

static void render_options(option_box_t* box)
{
    if (SDL_PointInRect(&mouse_pos, &box->flat.new_rect) && hold)
    {
        box->click.render(window.renderer);
    }
    else if (SDL_PointInRect(&mouse_pos, &box->flat.new_rect))
    {
        box->light.render(window.renderer);
    }
    else
    {
        box->flat.render(window.renderer);
    }
}

static void render_cursor_highlight_grid(void)
{
    cursor_highlight.new_rect.x = ((mouse_pos.x + camera.x)/BLOCK_LENGTH) * BLOCK_LENGTH - camera.x;
    cursor_highlight.new_rect.y = ((mouse_pos.y + camera.y)/BLOCK_LENGTH) * BLOCK_LENGTH - camera.y;
    cursor_highlight.render(window.renderer);
}


static bool outside_textbox_event(void)
{
    if (!SDL_PointInRect(&mouse_pos, &text_box.new_rect))
    {
        level_mode = DEFAULT;
        return true;
    }
    return false;
}

static void piece_select_event(void)
{
    if (lvl1_map.collision[left_click.y][left_click.x] == 'p')
    {
        character_select = lvl1_map.piece_locations[left_click.y][left_click.x];
        lvl1_map.fill_move_attack_spaces(character_select->i, character_select->j, character_select->moves);
        // print_field(lvl1_map.move_attack_spaces[0], ROW, COL); // TODO: remove this line
        level_mode = PIECE_SELECT;

        if (character_select->allegiance == HERO)
        {
            arrage_text(4, &move_box, &items_box, &stats_box, &settings_box);
        }
        else
        {
            arrage_text(3, &items_box, &stats_box, &settings_box);
        }
    }
    else
    {
        level_mode = OPTIONS;
        arrage_text(1, &settings_box);
    }
}

static bool option_select_event(SDL_Rect* rect, levelMode_t modeSelect)
{
    if (SDL_PointInRect(&mouse_pos, rect))
    {
        level_mode = modeSelect;
        return true;
    }

    return false;
}

static bool move_event(bool revert)
{
    static SDL_Point prevCharacterPos;

    if (LIMITS('0', lvl1_map.move_attack_spaces[left_click.y][left_click.x], '0' + character_select->moves) || revert)
    {
        if (!revert)
        {
            prevCharacterPos.x = character_select->j;
            prevCharacterPos.y = character_select->i;
        }
        else
        {
            left_click.x = prevCharacterPos.x;
            left_click.y = prevCharacterPos.y;
        }

        char tempChar = lvl1_map.collision[left_click.y][left_click.x];
        lvl1_map.collision[left_click.y][left_click.x] = lvl1_map.collision[character_select->i][character_select->j];
        lvl1_map.collision[character_select->i][character_select->j] = tempChar;

        Character* tempCharacter = lvl1_map.piece_locations[left_click.y][left_click.x];
        lvl1_map.piece_locations[left_click.y][left_click.x] = lvl1_map.piece_locations[character_select->i][character_select->j];
        lvl1_map.piece_locations[character_select->i][character_select->j] = tempCharacter;

        character_select->i = left_click.y;
        character_select->j = left_click.x;
        character_select->image.new_rect.x = character_select->j*BLOCK_LENGTH - camera.x;
        character_select->image.new_rect.y = character_select->i*BLOCK_LENGTH - camera.y;

        if (!revert)
        {
            level_mode = POSTMOVE;
            if (render_attack_box(character_select->i, character_select->j))
            {
                arrage_text(2, &wait_box, &attack_box);
            }
            else
            {
                arrage_text(1, &wait_box);
            }
        }
        else
        {
            level_mode = PIECE_SELECT;
            arrage_text(4, &move_box, &items_box, &stats_box, &settings_box);
        }

        return true;
    }

    return false;
}

void attack_event(void)
{
    if (lvl1_map.piece_locations[left_click.y][left_click.x] != NULL)
    {
        if (lvl1_map.piece_locations[left_click.y][left_click.x]->allegiance == VILLAIN)
        {
            // TODO: Need a functions that calculates the damage, crit, and misses
            lvl1_map.piece_locations[left_click.y][left_click.x]->hp -= character_select->attack;
            std::cout << lvl1_map.piece_locations[left_click.y][left_click.x]->hp << std::endl; // TODO: remove this line
            level_mode = DEFAULT;
        }
    }
}

static void arrage_text(int numBoxes, ...)
{
    text_box.new_rect.h = numBoxes*85*SCALE;
    text_box.new_rect.makeDimensions();

    va_list args;
    va_start(args, numBoxes);
    for (int i = 1; i < (2*numBoxes); i = i + 2)
    {
        option_box_t* box = va_arg(args, option_box_t*);

        box->flat.new_rect.y  = (i*text_box.new_rect.h)/(2*numBoxes);
        box->light.new_rect.y = (i*text_box.new_rect.h)/(2*numBoxes);
        box->click.new_rect.y = (i*text_box.new_rect.h)/(2*numBoxes);

        box->flat.new_rect.makeDimensions();
        box->light.new_rect.makeDimensions();
        box->click.new_rect.makeDimensions();

        box->flat.new_rect.shiftY();
        box->light.new_rect.shiftY();
        box->click.new_rect.shiftY();
    }
    va_end(args);
}

static void click_index(int* x, int* y)
{
    *x = (*x + camera.x)/BLOCK_LENGTH;
    *y = (*y + camera.y)/BLOCK_LENGTH;
}

static void ajust_sprites(int xAjust, int yAjust)
{
    hero_sprite.image.new_rect.x -= xAjust;
    hero_sprite.image.new_rect.y -= yAjust;
    hero_sprite.image.new_rect.makeDimensions();

    villain_sprite.image.new_rect.x -= xAjust;
    villain_sprite.image.new_rect.y -= yAjust;
    villain_sprite.image.new_rect.makeDimensions();
}

static void images_init(void)
{
    update_cursor_pos(&mouse_cursor.new_rect, mouse_pos.x, mouse_pos.y);

    tile.init(window.renderer,      "images/Images/level_1_images/blockDark.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    dirt_tile.init(window.renderer,  "images/Images/level_1_images/dirttile.png",  BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    grass_tile.init(window.renderer, "images/Images/level_1_images/grasstile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    house_tile.init(window.renderer, "images/Images/level_1_images/housetile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    stone_tile.init(window.renderer, "images/Images/level_1_images/stonetile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    tree_tile.init(window.renderer,  "images/Images/level_1_images/treetile.png",  BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    water_tile.init(window.renderer, "images/Images/level_1_images/watertile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);

    hero_sprite.image.init(window.renderer,    "images/Images/level_1_images/sprite.png",        0.1, 7*BLOCK_LENGTH, 4*BLOCK_LENGTH);
    villain_sprite.image.init(window.renderer, "images/Images/level_1_images/badGuySprite.png", 0.13, 7*BLOCK_LENGTH, 1*BLOCK_LENGTH);

    text_box.init(window.renderer, "images/Images/level_1_images/TextBox.png", 0.28*SCALE, window.w, 0);
    text_box.new_rect.shiftX(2); // This is here to fix all the other boxes

    cursor_highlight.init(window.renderer, yellow, BLOCK_LENGTH, BLOCK_LENGTH);
    move_highlight.init(window.renderer,   cyan,   BLOCK_LENGTH, BLOCK_LENGTH);
    attack_highlight.init(window.renderer, red,    BLOCK_LENGTH, BLOCK_LENGTH);

    move_box.flat.init(window.renderer,  "images/Images/level_1_images/Move.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);
    move_box.light.init(window.renderer, "images/Images/level_1_images/MoveH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);
    move_box.click.init(window.renderer, "images/Images/level_1_images/MoveHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);

    items_box.flat.init(window.renderer,  "images/Images/level_1_images/Items.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);
    items_box.light.init(window.renderer, "images/Images/level_1_images/ItemsH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);
    items_box.click.init(window.renderer, "images/Images/level_1_images/ItemsHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);

    stats_box.flat.init(window.renderer,  "images/Images/level_1_images/Stats.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, 5*text_box.new_rect.h/8);
    stats_box.light.init(window.renderer, "images/Images/level_1_images/StatsH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, 5*text_box.new_rect.h/8);
    stats_box.click.init(window.renderer, "images/Images/level_1_images/StatsHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, 5*text_box.new_rect.h/8);

    settings_box.flat.init(window.renderer,  "images/Images/level_1_images/Settings.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, 7*text_box.new_rect.h/8);
    settings_box.light.init(window.renderer, "images/Images/level_1_images/SettingsH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, 7*text_box.new_rect.h/8);
    settings_box.click.init(window.renderer, "images/Images/level_1_images/SettingsHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, 7*text_box.new_rect.h/8);

    wait_box.flat.init(window.renderer,  "images/Images/level_1_images/Wait.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);
    wait_box.light.init(window.renderer, "images/Images/level_1_images/WaitH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);
    wait_box.click.init(window.renderer, "images/Images/level_1_images/WaitHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, text_box.new_rect.h/8);

    attack_box.flat.init(window.renderer,  "images/Images/level_1_images/Attack.png",   OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);
    attack_box.light.init(window.renderer, "images/Images/level_1_images/AttackH.png",  OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);
    attack_box.click.init(window.renderer, "images/Images/level_1_images/AttackHL.png", OPTION_BLOCK*SCALE, text_box.new_rect.topX, 3*text_box.new_rect.h/8);

    move_box.flat.new_rect.shiftXY();
    move_box.light.new_rect.shiftXY();
    move_box.click.new_rect.shiftXY();

    items_box.flat.new_rect.shiftXY();
    items_box.light.new_rect.shiftXY();
    items_box.click.new_rect.shiftXY();

    stats_box.flat.new_rect.shiftXY();
    stats_box.light.new_rect.shiftXY();
    stats_box.click.new_rect.shiftXY();

    settings_box.flat.new_rect.shiftXY();
    settings_box.light.new_rect.shiftXY();
    settings_box.click.new_rect.shiftXY();

    wait_box.flat.new_rect.shiftXY();
    wait_box.light.new_rect.shiftXY();
    wait_box.click.new_rect.shiftXY();

    attack_box.flat.new_rect.shiftXY();
    attack_box.light.new_rect.shiftXY();
    attack_box.click.new_rect.shiftXY();

    text_box.set_alpha(200);
    move_box.flat.set_alpha(200);
    items_box.flat.set_alpha(200);
    stats_box.flat.set_alpha(200);
    settings_box.flat.set_alpha(200);
    wait_box.flat.set_alpha(200);
    attack_box.flat.set_alpha(200);

    cursor_highlight.set_alpha(50);
    move_highlight.set_alpha(100);
    attack_highlight.set_alpha(100);
}

static void destroy_images(void)
{
    tile.destroy();
    dirt_tile.destroy();
    grass_tile.destroy();
    house_tile.destroy();
    stone_tile.destroy();
    tree_tile.destroy();
    water_tile.destroy();

    hero_sprite.~Character();
    villain_sprite.~Character();

    cursor_highlight.destroy();
    move_highlight.destroy();
    attack_highlight.destroy();

    text_box.destroy();

    move_box.flat.destroy(); 
    move_box.light.destroy(); 
    move_box.click.destroy();

    items_box.flat.destroy(); 
    items_box.light.destroy(); 
    items_box.click.destroy();

    stats_box.flat.destroy(); 
    stats_box.light.destroy(); 
    stats_box.click.destroy();

    settings_box.flat.destroy(); 
    settings_box.light.destroy(); 
    settings_box.click.destroy(); 

    wait_box.flat.destroy();
    wait_box.light.destroy();
    wait_box.click.destroy();

    attack_box.flat.destroy();
    attack_box.light.destroy();
    attack_box.click.destroy();
}

static void sprites_init(void)
{
    hero_sprite.initStatsAndPos("sprite", // name
                            69,      // hp
                            69,      // attack
                            69,      // defence
                            69,      // special attack
                            69,      // special defence
                            69,      // luck
                            4,       // moves
                            HERO,    // allegiance
                            4,       // i
                            7);      // j
    lvl1_map.piece_locations[hero_sprite.i][hero_sprite.j] = &hero_sprite;

    villain_sprite.initStatsAndPos("badGuySprite", // name
                            69,      // hp
                            69,      // attack
                            69,      // defence
                            69,      // special attack
                            69,      // special defence
                            69,      // luck
                            4,       // moves
                            VILLAIN, // allegiance
                            1,       // i
                            7);      // j
    lvl1_map.piece_locations[villain_sprite.i][villain_sprite.j] = &villain_sprite;
}
