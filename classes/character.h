#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL_Classes.h>
#include <item.h>

#define NUM_ITEMS

typedef enum allegiance_e {
    HERO,
    VILLAIN,
    NEUTRAL
} allegiance_t;

typedef struct item_list_s {
    item slot_1;
    item slot_2;
    item slot_3;
    item slot_4;
    item slot_5;
} item_list_t;

class Character
{
public:
    const char* name;
    int hp;
    int attack;
    int defence;
    int speAtt;
    int speDef;
    int luck;
    int moves;
    allegiance_t allegiance;
    int i;
    int j;
    bool selected;
    item_list_t items;
    texture_image image;
    
    Character();
    Character(const char* name,
              int hp,
              int attack,
              int defence,
              int speAtt,
              int speDef,
              int luck,
              int moves,
              allegiance_t allegiance,
              SDL_Renderer* renderer,
              const char* path,
              int i = 0,
              int j = 0,
              double scale_image = 1.0,
              int xPos = 0,
              int yPos = 0);

    void initStatsAndPos(const char* name,
                         int hp,
                         int attack,
                         int defence,
                         int speAtt,
                         int speDef,
                         int luck,
                         int moves,
                         allegiance_t allegiance,
                         int i,
                         int j);

    void initImage(SDL_Renderer* renderer, const char* path, double scale_image = 1.0, int xPos = 0, int yPos = 0);

    ~Character();
};

#endif // CHARACTER_H
