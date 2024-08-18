#include "main.h"
#include "debug.h"
#include "main_level_1.h"
#include "private_level_1.h"
#include "classes/character.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

#define BLOCK_LENGTH  (80)
#define OPTION_BLOCK  (0.075*SCALE)
#define CAMERA_CHANGE (10)
#define REVERT (true)

SDL_Point click_index;
SDL_Point focus;
SDL_Point camera;

levelMode_t level_mode;

TextureImage tile;
TextureImage dirt_tile;
TextureImage grass_tile;
TextureImage house_tile;
TextureImage stone_tile;
TextureImage tree_tile;
TextureImage water_tile;

option_box_t option_block_1;
option_box_t option_block_2;
option_box_t option_block_3;
option_box_t option_block_4;
option_box_t option_block_5;
option_box_t option_block_6;

TextureImage cursor_highlight;
TextureImage move_highlight;
TextureImage attack_highlight;

TextureImage text_box_holder;

Character hero_sprite;
Character villain_sprite;
Character* character_select;
item* item_select;
map lvl1_map;

static void render_options(option_box_t* box);
static void render_move_highlight(void);
static void render_attck_highlight(void);
static bool render_attack_box(int i, int j);
static void render_post_move_attack(int i, int j);
static void render_cursor_highlight_grid(void);

static void piece_select_event(void);
static bool outside_textbox_event(void);
static bool option_select_event(option_box_t* rect, levelMode_t modeSelect);
static bool move_event(bool revert = false);
static void attack_event(void);

static void get_click_index(int* x, int* y);
static void ajust_sprites(int xAjust, int yAjust);
static void arrage_text(int num_boxes, ...);

static void images_init(void);
static void destroy_images(void);
static void sprites_init(void);
static void init_block(option_box_t *option_block, const char *block_name);
static void destroy_block(option_box_t *option_block);

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
                    cursor.hold = true;
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    cursor.hold = false;
                    click_index.x = event.button.x;
                    click_index.y = event.button.y;
                    get_click_index(&click_index.x, &click_index.y);

                    switch (level_mode)
                    {
                    case DEFAULT:
                        piece_select_event();
                        break;
                    
                    case OPTIONS:
                        if (!outside_textbox_event())
                        {
                            option_select_event(&option_block_1, SETTINGS);
                        }
                        break;
                    
                    case PIECE_SELECT:
                        if (character_select->allegiance == HERO)
                        {
                            if (move_event());
                            else if (!outside_textbox_event())
                            {
                                option_select_event(&option_block_1, MOVE);
                                if (option_select_event(&option_block_2, ITEM))
                                {
                                    option_block_1.text.change_text(character_select->items.slot_1.name);
                                    option_block_2.text.change_text(character_select->items.slot_2.name);
                                    option_block_3.text.change_text(character_select->items.slot_3.name);
                                    arrage_text(3, &option_block_1, &option_block_2, &option_block_3);
                                }
                                option_select_event(&option_block_3, STATS);
                                option_select_event(&option_block_4, SETTINGS);
                            }
                        }
                        else
                        {
                            if (!outside_textbox_event())
                            {
                                if (option_select_event(&option_block_1, ITEM))
                                {
                                    option_block_1.text.change_text(character_select->items.slot_1.name);
                                    option_block_2.text.change_text(character_select->items.slot_2.name);
                                    option_block_3.text.change_text(character_select->items.slot_3.name);
                                    arrage_text(3, &option_block_1, &option_block_2, &option_block_3);
                                }
                                option_select_event(&option_block_2, STATS);
                                option_select_event(&option_block_3, SETTINGS);
                            }
                        }
                        break;
                    
                    case MOVE:
                        move_event();
                        break;

                    case ITEM:
                        bool item_selected;
                        
                        if (item_selected = option_select_event(&option_block_1, ITEM_OPTIONS))
                        {
                            item_select = &character_select->items.slot_1;
                        }
                        else if (item_selected = option_select_event(&option_block_2, ITEM_OPTIONS))
                        {
                            item_select = &character_select->items.slot_2;
                        }
                        else if (item_selected = option_select_event(&option_block_3, ITEM_OPTIONS))
                        {
                            item_select = &character_select->items.slot_3;
                        }
                        else if (item_selected = option_select_event(&option_block_4, ITEM_OPTIONS))
                        {
                            item_select = &character_select->items.slot_4;
                        }
                        else if (item_selected = option_select_event(&option_block_5, ITEM_OPTIONS))
                        {
                            item_select = &character_select->items.slot_5;
                        }

                        if (item_selected)
                        {
                            switch (item_select->type)
                            {
                                case WEAPON:
                                    option_block_1.text.change_text("Equip Weapon");
                                    option_block_2.text.change_text("Desc");
                                    arrage_text(2, &option_block_1, &option_block_2);
                                    break;

                                case HOLD:
                                    option_block_1.text.change_text("Desc");
                                    arrage_text(1, &option_block_1);
                                    break;

                                case CONSUMABLE:
                                    option_block_1.text.change_text("Use Item");
                                    option_block_2.text.change_text("Desc");
                                    arrage_text(2, &option_block_1, &option_block_2);
                                    break;
                            }
                        }

                        break;
                    
                    case ITEM_OPTIONS:
                        break;

                    case POSTMOVE:
                        option_select_event(&option_block_1, DEFAULT);
                        if (render_attack_box(character_select->i, character_select->j))
                        {
                            option_select_event(&option_block_2, ATTACK);
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
                        option_block_1.text.change_text("move");
                        option_block_2.text.change_text("items");
                        option_block_3.text.change_text("stats");
                        option_block_4.text.change_text("settings");
                        arrage_text(4, &option_block_1, &option_block_2, &option_block_3, &option_block_4);
                        break;

                    case ITEM_OPTIONS:
                        level_mode = ITEM;
                        option_block_1.text.change_text("wait");
                        option_block_2.text.change_text("attack");
                        option_block_3.text.change_text("move");
                        option_block_4.text.change_text("items");
                        option_block_5.text.change_text("stats");
                        arrage_text(5, &option_block_1, &option_block_2, &option_block_3, &option_block_4, &option_block_5);
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
    cursor.update_cursor_pos(window.window);

    window.clear_render();

    // draw the grid
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            switch (lvl1_map.tiles[i][j])
            {
            case 'n':
                tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                tile.render();
                break;
            
            case 'd':
                dirt_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                dirt_tile.render();
                break;

            case 'g':
                grass_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                grass_tile.render();
                break;

            case 'h':
                house_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                house_tile.render();
                break;

            case 's':
                stone_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                stone_tile.render();
                break;

            case 't':
                tree_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                tree_tile.render();
                break;

            case 'w':
                water_tile.change_pos(j*BLOCK_LENGTH - camera.x, i*BLOCK_LENGTH - camera.y);
                water_tile.render();
                break;

            default:
                break;
            }
        }
    }

    // draw the sprites
    hero_sprite.image.render();
    villain_sprite.image.render();

    switch (level_mode)
    {
    case DEFAULT:
        render_cursor_highlight_grid();
        break;
    
    case OPTIONS:
        text_box_holder.render();
        render_options(&option_block_1);
        break;
    
    case PIECE_SELECT:
        render_move_highlight();
        render_attck_highlight();
        render_cursor_highlight_grid();

        text_box_holder.render();
        if (character_select->allegiance == HERO)
        {
            render_options(&option_block_1); // move
            render_options(&option_block_2); // items
            render_options(&option_block_3); // stats
            render_options(&option_block_4); // settings
        }
        else
        {
            render_options(&option_block_1); // items
            render_options(&option_block_2); // stats
            render_options(&option_block_3); // settings
        }
        break;

    case MOVE:
        render_move_highlight();
        render_attck_highlight();
        render_cursor_highlight_grid();
        break;

    case ITEM:
        text_box_holder.render();
        render_options(&option_block_1); // Item 1
        render_options(&option_block_2); // Item 2
        render_options(&option_block_3); // Item 3
        break;

    case ITEM_OPTIONS:
        text_box_holder.render();
        switch (item_select->type)
        {
        case WEAPON:
            render_options(&option_block_1); // Equip Weapon
            render_options(&option_block_2); // Desc
            break;
        case HOLD:
            render_options(&option_block_1); // Desc
            break;
        case CONSUMABLE:
            render_options(&option_block_1); // Use Item
            render_options(&option_block_2); // Desc
            break;
        }

        break;

    case POSTMOVE:
        render_cursor_highlight_grid();
        
        text_box_holder.render();
        render_options(&option_block_1); // wait
        if (render_attack_box(character_select->i, character_select->j))
        {
            render_options(&option_block_2); // attack
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

    cursor.render();

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
                move_highlight.render();
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
                attack_highlight.render();
            }
        }
    }
}

static void render_post_move_attack(int i, int j)
{
    if (lvl1_map.piece_locations[i - 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i - 1][j]->allegiance != HERO)
        {                                                                  // [ ][x][ ]
            attack_highlight.new_rect.x =       j*BLOCK_LENGTH - camera.x; // [ ][o][ ]
            attack_highlight.new_rect.y = (i - 1)*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render();
        }
    }

    if (lvl1_map.piece_locations[i][j - 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j - 1]->allegiance != HERO)
        {                                                                  // [ ][ ][ ]
            attack_highlight.new_rect.x = (j - 1)*BLOCK_LENGTH - camera.x; // [x][o][ ]
            attack_highlight.new_rect.y =       i*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render();
        }
    }

    if (lvl1_map.piece_locations[i][j + 1] != NULL)
    {
        if (lvl1_map.piece_locations[i][j + 1]->allegiance != HERO)
        {                                                                  // [ ][ ][ ]
            attack_highlight.new_rect.x = (j + 1)*BLOCK_LENGTH - camera.x; // [ ][o][x]
            attack_highlight.new_rect.y =       i*BLOCK_LENGTH - camera.y; // [ ][ ][ ]
            attack_highlight.render();
        }
    }

    if (lvl1_map.piece_locations[i + 1][j] != NULL)
    {
        if (lvl1_map.piece_locations[i + 1][j]->allegiance != HERO)
        {                                                                  // [ ][ ][ ]
            attack_highlight.new_rect.x =       j*BLOCK_LENGTH - camera.x; // [ ][o][ ]
            attack_highlight.new_rect.y = (i + 1)*BLOCK_LENGTH - camera.y; // [ ][x][ ]
            attack_highlight.render();
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
    if (SDL_PointInRect(&cursor.mouse_pos, &box->flat.new_rect) && cursor.hold)
    {
        box->click.render();
    }
    else if (SDL_PointInRect(&cursor.mouse_pos, &box->flat.new_rect))
    {
        box->light.render();
    }
    else
    {
        box->flat.render();
    }

    box->text.render();
}

static void render_cursor_highlight_grid(void)
{
    cursor_highlight.new_rect.x = ((cursor.mouse_pos.x + camera.x)/BLOCK_LENGTH) * BLOCK_LENGTH - camera.x;
    cursor_highlight.new_rect.y = ((cursor.mouse_pos.y + camera.y)/BLOCK_LENGTH) * BLOCK_LENGTH - camera.y;
    cursor_highlight.render();
}


static bool outside_textbox_event(void)
{
    if (!SDL_PointInRect(&cursor.mouse_pos, &text_box_holder.new_rect))
    {
        level_mode = DEFAULT;
        return true;
    }
    return false;
}

static void piece_select_event(void)
{
    if (lvl1_map.collision[click_index.y][click_index.x] == 'p')
    {
        character_select = lvl1_map.piece_locations[click_index.y][click_index.x];
        lvl1_map.fill_move_attack_spaces(character_select->i, character_select->j, character_select->moves);
        // print_field(lvl1_map.move_attack_spaces[0], ROW, COL); // TODO: remove this line
        level_mode = PIECE_SELECT;

        if (character_select->allegiance == HERO)
        {  
            option_block_1.text.change_text("move");
            option_block_2.text.change_text("items");
            option_block_3.text.change_text("stats");
            option_block_4.text.change_text("settings");
            arrage_text(4, &option_block_1, &option_block_2, &option_block_3, &option_block_4);
        }
        else
        {
            option_block_1.text.change_text("items");
            option_block_2.text.change_text("stats");
            option_block_3.text.change_text("settings");
            arrage_text(3, &option_block_1, &option_block_2, &option_block_3);
        }
    }
    else
    {
        level_mode = OPTIONS;
        option_block_1.text.change_text("settings");
        arrage_text(1, &option_block_1);
    }
}

static bool option_select_event(option_box_t* box, levelMode_t mode_select)
{
    if (SDL_PointInRect(&cursor.mouse_pos, &box->flat.new_rect))
    {
        level_mode = mode_select;
        return true;
    }

    return false;
}

static bool move_event(bool revert)
{
    static SDL_Point prev_character_pos;

    if (LIMITS('0', lvl1_map.move_attack_spaces[click_index.y][click_index.x], '0' + character_select->moves) || revert)
    {
        if (!revert)
        {
            prev_character_pos.x = character_select->j;
            prev_character_pos.y = character_select->i;
        }
        else
        {
            click_index.x = prev_character_pos.x;
            click_index.y = prev_character_pos.y;
        }

        char temp_char = lvl1_map.collision[click_index.y][click_index.x];
        lvl1_map.collision[click_index.y][click_index.x] = lvl1_map.collision[character_select->i][character_select->j];
        lvl1_map.collision[character_select->i][character_select->j] = temp_char;

        Character* tempCharacter = lvl1_map.piece_locations[click_index.y][click_index.x];
        lvl1_map.piece_locations[click_index.y][click_index.x] = lvl1_map.piece_locations[character_select->i][character_select->j];
        lvl1_map.piece_locations[character_select->i][character_select->j] = tempCharacter;

        character_select->i = click_index.y;
        character_select->j = click_index.x;
        character_select->image.new_rect.x = character_select->j*BLOCK_LENGTH - camera.x;
        character_select->image.new_rect.y = character_select->i*BLOCK_LENGTH - camera.y;

        if (!revert)
        {
            level_mode = POSTMOVE;
            if (render_attack_box(character_select->i, character_select->j))
            {
                option_block_1.text.change_text("wait");
                option_block_2.text.change_text("attack");
                arrage_text(2, &option_block_1, &option_block_2);
            }
            else
            {
                option_block_1.text.change_text("wait");
                arrage_text(1, &option_block_1);
            }
        }
        else
        {
            level_mode = PIECE_SELECT;
            option_block_1.text.change_text("move");
            option_block_2.text.change_text("items");
            option_block_3.text.change_text("stats");
            option_block_4.text.change_text("settings");
            arrage_text(4, &option_block_1, &option_block_2, &option_block_3, &option_block_4);    
        }

        return true;
    }

    return false;
}

void attack_event(void)
{
    NULL_CHECK(lvl1_map.piece_locations[click_index.y][click_index.x]);

    if (lvl1_map.piece_locations[click_index.y][click_index.x]->allegiance == VILLAIN)
    {
        // TODO: Need a functions that calculates the damage, crit, and misses
        lvl1_map.piece_locations[click_index.y][click_index.x]->hp -= character_select->attack;
        std::cout << lvl1_map.piece_locations[click_index.y][click_index.x]->hp << std::endl; // TODO: remove this line
        level_mode = DEFAULT;
    }
}

static void arrage_text(int num_boxes, ...)
{
    text_box_holder.new_rect.h = num_boxes*85*SCALE;
    rect_make_dimensions(&text_box_holder.new_rect);

    va_list args;
    va_start(args, num_boxes);
    for (int i = 1; i < (2*num_boxes); i = i + 2)
    {
        option_box_t *box = va_arg(args, option_box_t *);

        box->flat.new_rect.y  = (i*text_box_holder.new_rect.h)/(2*num_boxes);
        box->light.new_rect.y = (i*text_box_holder.new_rect.h)/(2*num_boxes);
        box->click.new_rect.y = (i*text_box_holder.new_rect.h)/(2*num_boxes);
        box->text.rect.y      = (i*text_box_holder.new_rect.h)/(2*num_boxes);

        rect_make_dimensions(&box->flat.new_rect);
        rect_make_dimensions(&box->light.new_rect);
        rect_make_dimensions(&box->click.new_rect);
        rect_make_dimensions(&box->text.rect);

        rect_shiftY(&box->flat.new_rect);
        rect_shiftY(&box->light.new_rect);
        rect_shiftY(&box->click.new_rect);
        rect_shiftY(&box->text.rect);
    }
    va_end(args);
}

static void get_click_index(int *x, int *y)
{
    *x = (*x + camera.x)/BLOCK_LENGTH;
    *y = (*y + camera.y)/BLOCK_LENGTH;
}

static void ajust_sprites(int xAjust, int yAjust)
{
    hero_sprite.image.new_rect.x -= xAjust;
    hero_sprite.image.new_rect.y -= yAjust;
    rect_make_dimensions(&hero_sprite.image.new_rect);

    villain_sprite.image.new_rect.x -= xAjust;
    villain_sprite.image.new_rect.y -= yAjust;
    rect_make_dimensions(&villain_sprite.image.new_rect);
}

static void images_init(void)
{
    cursor.update_cursor_pos(window.window);

    tile.init(window.renderer,       "images/Images/level_1_images/blockDark.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    dirt_tile.init(window.renderer,  "images/Images/level_1_images/dirttile.png",  BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    grass_tile.init(window.renderer, "images/Images/level_1_images/grasstile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    house_tile.init(window.renderer, "images/Images/level_1_images/housetile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    stone_tile.init(window.renderer, "images/Images/level_1_images/stonetile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    tree_tile.init(window.renderer,  "images/Images/level_1_images/treetile.png",  BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    water_tile.init(window.renderer, "images/Images/level_1_images/watertile.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);

    hero_sprite.image.init(window.renderer,    "images/Images/level_1_images/sprite.png",        0.1, 7*BLOCK_LENGTH, 4*BLOCK_LENGTH);
    villain_sprite.image.init(window.renderer, "images/Images/level_1_images/badGuySprite.png", 0.13, 7*BLOCK_LENGTH, 1*BLOCK_LENGTH);

    text_box_holder.init(window.renderer, "images/Images/level_1_images/TextBox.png", 0.28*SCALE, window.w, 0);
    rect_shiftX(&text_box_holder.new_rect, 2); // This is here to fix all the other boxes

    cursor_highlight.init(window.renderer, SDL_yellow, BLOCK_LENGTH, BLOCK_LENGTH);
    move_highlight.init(window.renderer,   SDL_cyan,   BLOCK_LENGTH, BLOCK_LENGTH);
    attack_highlight.init(window.renderer, SDL_red,    BLOCK_LENGTH, BLOCK_LENGTH);

    init_block(&option_block_1, "move");
    init_block(&option_block_2, "items");
    init_block(&option_block_3, "stats");
    init_block(&option_block_4, "settings");
    init_block(&option_block_5, "wait");
    init_block(&option_block_6, "attack");

    text_box_holder.set_alpha(200);
    cursor_highlight.set_alpha(50);
    move_highlight.set_alpha(100);
    attack_highlight.set_alpha(100);
}

static void init_block(option_box_t *option_block, const char *block_name)
{
    option_block->flat.init(window.renderer,  SDL_yellow, 175, 65, text_box_holder.new_rect.topX, text_box_holder.new_rect.h/8);
    option_block->light.init(window.renderer, SDL_blue,   175, 65, text_box_holder.new_rect.topX, text_box_holder.new_rect.h/8);
    option_block->click.init(window.renderer, SDL_cyan,   175, 65, text_box_holder.new_rect.topX, text_box_holder.new_rect.h/8);
    option_block->text.init(window.renderer, "fonts/arial.ttf", block_name, 20, option_block->flat.new_rect.x, option_block->flat.new_rect.y);
    rect_shiftXY(&option_block->flat.new_rect);
    rect_shiftXY(&option_block->light.new_rect);
    rect_shiftXY(&option_block->click.new_rect);
    rect_shiftXY(&option_block->text.rect);
    option_block->flat.set_alpha(200);
}

static void destroy_block(option_box_t *option_block)
{
    option_block->flat.~TextureImage();
    option_block->light.~TextureImage();
    option_block->click.~TextureImage();
    option_block->text.~TextureText();
}

static void destroy_images(void)
{
    tile.~TextureImage();
    dirt_tile.~TextureImage();
    grass_tile.~TextureImage();
    house_tile.~TextureImage();
    stone_tile.~TextureImage();
    tree_tile.~TextureImage();
    water_tile.~TextureImage();

    hero_sprite.~Character();
    villain_sprite.~Character();

    cursor_highlight.~TextureImage();
    move_highlight.~TextureImage();
    attack_highlight.~TextureImage();

    text_box_holder.~TextureImage();

    destroy_block(&option_block_1);
    destroy_block(&option_block_2);
    destroy_block(&option_block_3);
    destroy_block(&option_block_4);
    destroy_block(&option_block_5);
    destroy_block(&option_block_6);
}

static void sprites_init(void)
{
    hero_sprite.init_stats_and_pos("sprite", // name
                                   69,       // hp
                                   69,       // attack
                                   69,       // defence
                                   69,       // special attack
                                   69,       // special defence
                                   69,       // luck
                                   4,        // moves
                                   HERO,     // allegiance
                                   4,        // i
                                   7);       // j
    lvl1_map.piece_locations[hero_sprite.i][hero_sprite.j] = &hero_sprite;
    hero_sprite.items.slot_1.init("Weapon Item", 50, WEAPON, swords);
    hero_sprite.items.slot_2.init("Hold Item", 50, HOLD, chain_mail);
    hero_sprite.items.slot_3.init("Consumable Item", 50, CONSUMABLE, potion);
    hero_sprite.items.num_items = 3;

    villain_sprite.init_stats_and_pos("badGuySprite", // name
                                      69,            // hp
                                      69,            // attack
                                      69,            // defence
                                      69,            // special attack
                                      69,            // special defence
                                      69,            // luck
                                      4,             // moves
                                      VILLAIN,       // allegiance
                                      1,             // i
                                      7);            // j
    lvl1_map.piece_locations[villain_sprite.i][villain_sprite.j] = &villain_sprite;
}
