#include "../../main.h"
#include "main_level_1.h"
#include "private_level_1.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>
#include <Character.h>

#define BLOCK_LENGTH (80)

SDL_Point leftClick;
SDL_Point focus;

levelMode_t levelMode;

textureImage tile;

textureImage game_flat_temp;
textureImage game_light_temp;
textureImage game_click_temp;
textureImage settings_flat_temp;
textureImage settings_light_temp;
textureImage settings_click_temp;

textureImage cursorHighlight;
textureImage moveHighlight;
textureImage attackHighlight;

textureImage textBox;

Character sprite;
Character* characterSelect;
map_t lvl1Map;

void main_level_1(void);

static void renderOptions(textureImage box_flat, textureImage box_light, textureImage box_click);
static void renderMoveHighlight(void);
static void renderAttHighlight(void);
static void renderCursorHighlightGrid(void);

static void pieceSelectEvent(void);
static bool outsideTextboxEvent(void);
static void optionSelectEvent(SDL_Rect rect, int modeSelect);
static bool moveEvent(void);

static void clickIndex(int* x, int* y);

static void imagesInit(void);
static void destroyImages(void);
static void spritesInit(void);

static void runLevel_1(void);
static void renderScreen(void);

void main_level_1(void) {
    imagesInit();
    spritesInit();
    levelMode = DEFAULT;
    sprite.i = 4;
    sprite.j = 7;
    while (mode == LEVEL_1) {
        runLevel_1();
    }

    destroyImages();
}

static void runLevel_1(void) {
    SDL_Event event;
    int fps = 60;
    Uint32 startingTick;

    while (mode == LEVEL_1) {
        startingTick = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mode = QUIT;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = true;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    hold = false;
                    leftClick.x = event.button.x;
                    leftClick.y = event.button.y;
                    clickIndex(&leftClick.x, &leftClick.y);

                    switch (levelMode)
                    {
                    case DEFAULT:
                        pieceSelectEvent();
                        break;
                    
                    case OPTIONS:
                        if (!outsideTextboxEvent()) {
                            optionSelectEvent(settings_flat_temp.newRect, SETTINGS);
                        }
                        break;
                    
                    case PIECE_SELECT:
                        if(moveEvent());
                        else if (!outsideTextboxEvent()) {
                            optionSelectEvent(game_flat_temp.newRect, MOVE);
                            optionSelectEvent(settings_flat_temp.newRect, SETTINGS);
                        }
                        break;
                    
                    case MOVE:
                        moveEvent();
                        break;

                    case STATS:
                        break;

                    case SETTINGS:
                        break;

                    default:
                        levelMode = DEFAULT;
                        break;
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    levelMode = DEFAULT;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mode = MAIN_MENU;
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

    // draw the grid
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            tile.changePos(j*BLOCK_LENGTH, i*BLOCK_LENGTH);

            if (lvl1Map.tiles[i][j] == 'n') {
                tile.render(window.renderer);
            }
        }
    }
    sprite.image.render(window.renderer); // draw the sprite

    switch (levelMode)
    {
    case DEFAULT:
        renderCursorHighlightGrid();
        break;
    
    case OPTIONS:
        textBox.render(window.renderer);
        renderOptions(settings_flat_temp, settings_light_temp, settings_click_temp);
        break;
    
    case PIECE_SELECT:
        textBox.render(window.renderer);
        renderMoveHighlight();
        renderAttHighlight();
        renderOptions(game_flat_temp, game_light_temp, game_click_temp);
        renderOptions(settings_flat_temp, settings_light_temp, settings_click_temp);
        renderCursorHighlightGrid();
        break;

    case MOVE:
        renderMoveHighlight();
        renderAttHighlight();
        renderCursorHighlightGrid();
        break;

    case STATS:
        break;


    case SETTINGS:
        break;

    default:
        levelMode = DEFAULT;
        break;
    }

    mouseCursor.render(window.renderer);

    SDL_RenderPresent(window.renderer);
}

static void renderMoveHighlight(void) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (LIMITS('1', lvl1Map.moveAttSpaces[i][j], characterSelect->moves + '0')) {
                moveHighlight.newRect.x = j*BLOCK_LENGTH;
                moveHighlight.newRect.y = i*BLOCK_LENGTH;
                moveHighlight.render(window.renderer);
            }
        }
    }
}

static void renderAttHighlight(void) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (lvl1Map.moveAttSpaces[i][j] == 'a') {
                attackHighlight.newRect.x = j*BLOCK_LENGTH;
                attackHighlight.newRect.y = i*BLOCK_LENGTH;
                attackHighlight.render(window.renderer);
            }
        }
    }
}

static void renderOptions(textureImage box_flat, textureImage box_light, textureImage box_click) {
    if (SDL_PointInRect(&mousePos, &box_flat.newRect) && hold) {
        box_click.render(window.renderer);
    }
    else if (SDL_PointInRect(&mousePos, &box_flat.newRect)) {
        box_light.render(window.renderer);
    }
    else {
        box_flat.render(window.renderer);
    }
}

static void renderCursorHighlightGrid(void) {
    cursorHighlight.newRect.x = (mousePos.x/BLOCK_LENGTH) * BLOCK_LENGTH;
    cursorHighlight.newRect.y = (mousePos.y/BLOCK_LENGTH) * BLOCK_LENGTH;
    cursorHighlight.render(window.renderer);
}


static bool outsideTextboxEvent(void) {
    if (!SDL_PointInRect(&mousePos, &textBox.newRect)) {
        levelMode = DEFAULT;
        return true;
    }
    return false;
}

static void pieceSelectEvent(void) {
    if (lvl1Map.collision[leftClick.y][leftClick.x] == 'p') {
        characterSelect = lvl1Map.pieceLocations[leftClick.y][leftClick.x];
        lvl1Map.fillMoveAttSpaces(characterSelect->i, characterSelect->j, characterSelect->moves);
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                std::cout << lvl1Map.moveAttSpaces[i][j];
            }
            std::cout << "\n";
        }
        levelMode = PIECE_SELECT;
        // focus = leftClick;
    }
    else {
        levelMode = OPTIONS;
    }
}

static void optionSelectEvent(SDL_Rect rect, int modeSelect) {
    if (SDL_PointInRect(&mousePos, &rect)) {
        levelMode = (levelMode_t)modeSelect;
    }
}

static bool moveEvent(void) {
    if (LIMITS('0', lvl1Map.moveAttSpaces[leftClick.y][leftClick.x], '0' + characterSelect->moves)) {
        char tempChar = lvl1Map.collision[leftClick.y][leftClick.x];
        lvl1Map.collision[leftClick.y][leftClick.x] = lvl1Map.collision[characterSelect->i][characterSelect->j];
        lvl1Map.collision[characterSelect->i][characterSelect->j] = tempChar;

        Character* tempCharacter = lvl1Map.pieceLocations[leftClick.y][leftClick.x];
        lvl1Map.pieceLocations[leftClick.y][leftClick.x] = lvl1Map.pieceLocations[characterSelect->i][characterSelect->j];
        lvl1Map.pieceLocations[characterSelect->i][characterSelect->j] = tempCharacter;

        characterSelect->i = leftClick.y;
        characterSelect->j = leftClick.x;
        characterSelect->image.newRect.x = characterSelect->j*BLOCK_LENGTH;
        characterSelect->image.newRect.y = characterSelect->i*BLOCK_LENGTH;

        levelMode = DEFAULT; // This is temporary; we want a option menu for move; ie: attack, wait, etc
        return true;
    }

    return false;
}

static void clickIndex(int* x, int* y) {
    *x = (*x/BLOCK_LENGTH);
    *y = (*y/BLOCK_LENGTH);
}

static void imagesInit(void) {
    updateCursorPos(&mouseCursor.newRect, mousePos.x, mousePos.y);

    tile.init(window.renderer, "images/Images/level_1_images/blockDark.png", BLOCK_LENGTH, BLOCK_LENGTH, 0, 0);
    sprite.image.init(window.renderer, "images/Images/level_1_images/sprite.png", 0.1, 7*BLOCK_LENGTH, 4*BLOCK_LENGTH);

    textBox.init(window.renderer, "images/Images/level_1_images/TextBox.png", 0.28*SCALE, window.w, 0);

    game_flat_temp.init(window.renderer,   "images/Images/main_menu_images/Game.png",   0.1*SCALE, window.w, 0);
    game_light_temp.init(window.renderer,  "images/Images/main_menu_images/GameH.png",  0.1*SCALE, window.w, 0);
    game_click_temp.init(window.renderer,  "images/Images/main_menu_images/GameHL.png", 0.1*SCALE, window.w, 0);

    settings_flat_temp.init(window.renderer,   "images/Images/main_menu_images/Settings.png",   0.1*SCALE, window.w, window.h/8);
    settings_light_temp.init(window.renderer,  "images/Images/main_menu_images/SettingsH.png",  0.1*SCALE, window.w, window.h/8);
    settings_click_temp.init(window.renderer,  "images/Images/main_menu_images/SettingsHL.png", 0.1*SCALE, window.w, window.h/8);

    cursorHighlight.init(window.renderer, yellow, BLOCK_LENGTH, BLOCK_LENGTH);
    moveHighlight.init(window.renderer, cyan, BLOCK_LENGTH, BLOCK_LENGTH);
    attackHighlight.init(window.renderer, red, BLOCK_LENGTH, BLOCK_LENGTH);

    textBox.newRect.shiftX(2);

    game_flat_temp.newRect.shiftX(2);
    game_light_temp.newRect.shiftX(2);
    game_click_temp.newRect.shiftX(2);

    settings_flat_temp.newRect.shiftX(2);
    settings_light_temp.newRect.shiftX(2);
    settings_click_temp.newRect.shiftX(2);

    textBox.setAlpha(200);
    game_flat_temp.setAlpha(200);
    settings_flat_temp.setAlpha(200);

    cursorHighlight.setAlpha(50);
    moveHighlight.setAlpha(100);
    attackHighlight.setAlpha(100);
}

static void destroyImages(void) {
    tile.destroy();
    sprite.~Character();
    cursorHighlight.destroy();

    textBox.destroy();

    game_flat_temp.destroy(); 
    game_light_temp.destroy(); 
    game_click_temp.destroy();

    settings_flat_temp.destroy(); 
    settings_light_temp.destroy(); 
    settings_click_temp.destroy(); 
}

static void spritesInit(void) {
    sprite.initStatsAndPos("sprite", // name
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
    lvl1Map.pieceLocations[sprite.i][sprite.j] = &sprite;
}
