#include "../../main.h"
#include "../../debug.h"
#include "main_level_1.h"
#include "private_level_1.h"

#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>
#include <Character.h>

#define BLOCK_LENGTH (80)
#define OPTION_BLOCK (0.075)
#define REVERT (true)

SDL_Point leftClick;
SDL_Point focus;

levelMode_t levelMode;

textureImage tile;

option_box_t attack_box;
option_box_t items_box;
option_box_t move_box;
option_box_t stats_box;
option_box_t wait_box;
option_box_t settings_box;

textureImage cursorHighlight;
textureImage moveHighlight;
textureImage attackHighlight;

textureImage textBox;

Character hero_sprite;
Character villain_sprite;
Character* characterSelect;
map_t lvl1Map;

void main_level_1(void);

static void renderOptions(option_box_t box);
static void renderMoveHighlight(void);
static void renderAttHighlight(void);
static void renderPostMoveAttack(int i, int j);
static void renderCursorHighlightGrid(void);

static void pieceSelectEvent(void);
static bool outsideTextboxEvent(void);
static bool optionSelectEvent(SDL_Rect rect, int modeSelect);
static bool moveEvent(bool revert = false);

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
    while (mode == LEVEL_1) {
        runLevel_1();
    }

    destroyImages();
}

static void runLevel_1(void) {
    SDL_Event event;
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
                            optionSelectEvent(settings_box.flat.newRect, SETTINGS);
                        }
                        break;
                    
                    case PIECE_SELECT:
                        if (characterSelect->allegiance == HERO) {
                            if (moveEvent());
                            else if (!outsideTextboxEvent()) {
                                optionSelectEvent(move_box.flat.newRect, MOVE);
                                optionSelectEvent(settings_box.flat.newRect, SETTINGS);
                            }
                        }
                        else {
                            if (!outsideTextboxEvent()) {
                                optionSelectEvent(stats_box.flat.newRect, STATS);
                                optionSelectEvent(settings_box.flat.newRect, SETTINGS);
                            }
                        }
                        break;
                    
                    case MOVE:
                        moveEvent();
                        break;

                    case POSTMOVE:
                        optionSelectEvent(wait_box.flat.newRect, DEFAULT);
                        optionSelectEvent(attack_box.flat.newRect, ATTACK);
                        break;

                    case ATTACK:
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
                    switch (levelMode)
                    {
                    case DEFAULT:
                        break;
                    
                    case OPTIONS:
                        levelMode = DEFAULT;
                        break;
                    
                    case PIECE_SELECT:
                        levelMode = DEFAULT;
                        break;
                    
                    case MOVE:
                        levelMode = PIECE_SELECT;
                        break;

                    case POSTMOVE:
                        moveEvent(REVERT);
                        break;

                    case ATTACK:
                        levelMode = POSTMOVE;
                        break;

                    case STATS:
                        levelMode = DEFAULT;
                        break;

                    case SETTINGS:
                        levelMode = DEFAULT;
                        break;

                    default:
                        levelMode = DEFAULT;
                        break;
                    }
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

    // draw the sprites
    hero_sprite.image.render(window.renderer);
    villain_sprite.image.render(window.renderer);

    switch (levelMode)
    {
    case DEFAULT:
        renderCursorHighlightGrid();
        break;
    
    case OPTIONS:
        textBox.render(window.renderer);
        renderOptions(settings_box);
        break;
    
    case PIECE_SELECT:
        renderMoveHighlight();
        renderAttHighlight();
        renderCursorHighlightGrid();

        textBox.render(window.renderer);
        if (characterSelect->allegiance == HERO) {
            renderOptions(move_box);
            renderOptions(items_box);
            renderOptions(stats_box);
            renderOptions(settings_box);
        }
        else {
            renderOptions(items_box);
            renderOptions(stats_box);
            renderOptions(settings_box);
        }
        break;

    case MOVE:
        renderMoveHighlight();
        renderAttHighlight();
        renderCursorHighlightGrid();
        break;

    case POSTMOVE:
        renderCursorHighlightGrid();
        
        textBox.render(window.renderer);
        renderOptions(wait_box);
        renderOptions(attack_box);
        break;

    case ATTACK:
        renderPostMoveAttack(characterSelect->i, characterSelect->j);
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

static void renderPostMoveAttack(int i, int j) {
    if (lvl1Map.pieceLocations[i - 1][j] != NULL) {
        if (lvl1Map.pieceLocations[i - 1][j]->allegiance != HERO) { // [ ][x][ ]
            attackHighlight.newRect.x =       j*BLOCK_LENGTH;       // [ ][o][ ]
            attackHighlight.newRect.y = (i - 1)*BLOCK_LENGTH;       // [ ][ ][ ]
            attackHighlight.render(window.renderer);
        }
    }

    if (lvl1Map.pieceLocations[i][j - 1] != NULL) {
        if (lvl1Map.pieceLocations[i][j - 1]->allegiance != HERO) { // [ ][ ][ ]
            attackHighlight.newRect.x = (j - 1)*BLOCK_LENGTH;       // [x][o][ ]
            attackHighlight.newRect.y =       i*BLOCK_LENGTH;       // [ ][ ][ ]
            attackHighlight.render(window.renderer);
        }
    }

    if (lvl1Map.pieceLocations[i][j + 1] != NULL) {
        if (lvl1Map.pieceLocations[i][j + 1]->allegiance != HERO) { // [ ][ ][ ]
            attackHighlight.newRect.x = (j + 1)*BLOCK_LENGTH;       // [ ][o][x]
            attackHighlight.newRect.y =       i*BLOCK_LENGTH;       // [ ][ ][ ]
            attackHighlight.render(window.renderer);
        }
    }

    if (lvl1Map.pieceLocations[i + 1][j] != NULL) {
        if (lvl1Map.pieceLocations[i + 1][j]->allegiance != HERO) { // [ ][ ][ ]
            attackHighlight.newRect.x =       j*BLOCK_LENGTH;       // [ ][o][ ]
            attackHighlight.newRect.y = (i + 1)*BLOCK_LENGTH;       // [ ][x][ ]
            attackHighlight.render(window.renderer);
        }
    }
}

static void renderOptions(option_box_t box) {
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
        printField(lvl1Map.moveAttSpaces[0], ROW, COL);
        levelMode = PIECE_SELECT;
    }
    else {
        levelMode = OPTIONS;
    }
}

static bool optionSelectEvent(SDL_Rect rect, int modeSelect) {
    if (SDL_PointInRect(&mousePos, &rect)) {
        levelMode = (levelMode_t)modeSelect;
        return true;
    }

    return false;
}

static bool moveEvent(bool revert) {
    static SDL_Point prevCharacterPos;

    if (LIMITS('0', lvl1Map.moveAttSpaces[leftClick.y][leftClick.x], '0' + characterSelect->moves) || revert) {
        if (!revert) {
            prevCharacterPos.x = characterSelect->j;
            prevCharacterPos.y = characterSelect->i;
        }
        else {
            leftClick.x = prevCharacterPos.x;
            leftClick.y = prevCharacterPos.y;
        }

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

        if (!revert) {
            levelMode = POSTMOVE;
        }
        else {
            levelMode = PIECE_SELECT;
        }

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
    hero_sprite.image.init(window.renderer, "images/Images/level_1_images/sprite.png", 0.1, 7*BLOCK_LENGTH, 4*BLOCK_LENGTH);
    villain_sprite.image.init(window.renderer, "images/Images/level_1_images/badGuySprite.png", 0.13, 7*BLOCK_LENGTH, 1*BLOCK_LENGTH);

    textBox.init(window.renderer, "images/Images/level_1_images/TextBox.png", 0.28*SCALE, window.w, 0);
    textBox.newRect.shiftX(2);

    cursorHighlight.init(window.renderer, yellow, BLOCK_LENGTH, BLOCK_LENGTH);
    moveHighlight.init(window.renderer,   cyan,   BLOCK_LENGTH, BLOCK_LENGTH);
    attackHighlight.init(window.renderer, red,    BLOCK_LENGTH, BLOCK_LENGTH);

    move_box.flat.init(window.renderer,  "images/Images/level_1_images/Move.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);
    move_box.light.init(window.renderer, "images/Images/level_1_images/MoveH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);
    move_box.click.init(window.renderer, "images/Images/level_1_images/MoveHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);

    items_box.flat.init(window.renderer,  "images/Images/level_1_images/Items.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);
    items_box.light.init(window.renderer, "images/Images/level_1_images/ItemsH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);
    items_box.click.init(window.renderer, "images/Images/level_1_images/ItemsHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);

    stats_box.flat.init(window.renderer,  "images/Images/level_1_images/Stats.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, 5*textBox.newRect.h/8);
    stats_box.light.init(window.renderer, "images/Images/level_1_images/StatsH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, 5*textBox.newRect.h/8);
    stats_box.click.init(window.renderer, "images/Images/level_1_images/StatsHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, 5*textBox.newRect.h/8);

    settings_box.flat.init(window.renderer,  "images/Images/level_1_images/Settings.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, 7*textBox.newRect.h/8);
    settings_box.light.init(window.renderer, "images/Images/level_1_images/SettingsH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, 7*textBox.newRect.h/8);
    settings_box.click.init(window.renderer, "images/Images/level_1_images/SettingsHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, 7*textBox.newRect.h/8);

    wait_box.flat.init(window.renderer,  "images/Images/level_1_images/Wait.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);
    wait_box.light.init(window.renderer, "images/Images/level_1_images/WaitH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);
    wait_box.click.init(window.renderer, "images/Images/level_1_images/WaitHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, textBox.newRect.h/8);

    attack_box.flat.init(window.renderer,  "images/Images/level_1_images/Attack.png",   OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);
    attack_box.light.init(window.renderer, "images/Images/level_1_images/AttackH.png",  OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);
    attack_box.click.init(window.renderer, "images/Images/level_1_images/AttackHL.png", OPTION_BLOCK*SCALE, textBox.newRect.topX, 3*textBox.newRect.h/8);

    move_box.flat.newRect.shiftXY();
    move_box.light.newRect.shiftXY();
    move_box.click.newRect.shiftXY();

    items_box.flat.newRect.shiftXY();
    items_box.light.newRect.shiftXY();
    items_box.click.newRect.shiftXY();

    stats_box.flat.newRect.shiftXY();
    stats_box.light.newRect.shiftXY();
    stats_box.click.newRect.shiftXY();

    settings_box.flat.newRect.shiftXY();
    settings_box.light.newRect.shiftXY();
    settings_box.click.newRect.shiftXY();

    wait_box.flat.newRect.shiftXY();
    wait_box.light.newRect.shiftXY();
    wait_box.click.newRect.shiftXY();

    attack_box.flat.newRect.shiftXY();
    attack_box.light.newRect.shiftXY();
    attack_box.click.newRect.shiftXY();

    textBox.setAlpha(200);
    move_box.flat.setAlpha(200);
    items_box.flat.setAlpha(200);
    stats_box.flat.setAlpha(200);
    settings_box.flat.setAlpha(200);
    wait_box.flat.setAlpha(200);
    attack_box.flat.setAlpha(200);

    cursorHighlight.setAlpha(50);
    moveHighlight.setAlpha(100);
    attackHighlight.setAlpha(100);
}

static void destroyImages(void) {
    tile.destroy();
    hero_sprite.~Character();
    villain_sprite.~Character();
    cursorHighlight.destroy();
    moveHighlight.destroy();
    attackHighlight.destroy();

    textBox.destroy();

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

static void spritesInit(void) {
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
    lvl1Map.pieceLocations[hero_sprite.i][hero_sprite.j] = &hero_sprite;

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
    lvl1Map.pieceLocations[villain_sprite.i][villain_sprite.j] = &villain_sprite;
}
