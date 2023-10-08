#include "character.h"

Character::Character()
{
    selected = false;
}

Character::Character(const char* name,
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
                     int i,
                     int j,
                     double scale_image,
                     int xPos,
                     int yPos)
{
    this->name = name;
    this->hp = hp;
    this->attack = attack;
    this->defence = defence;
    this->speAtt = speAtt;
    this->speDef = speDef;
    this->luck = luck;
    this->moves = moves;
    this->allegiance = allegiance,
    this->i = i;
    this->j = j;

    selected = false;

    image.init(renderer, path, scale_image, xPos, yPos);
}

void Character::init_stats_and_pos(const char* name,
                                   int hp,
                                   int attack,
                                   int defence,
                                   int speAtt,
                                   int speDef,
                                   int luck,
                                   int moves,
                                   allegiance_t allegiance,
                                   int i,
                                   int j)
{
    this->name = name;
    this->hp = hp;
    this->attack = attack;
    this->defence = defence;
    this->speAtt = speAtt;
    this->speDef = speDef;
    this->luck = luck;
    this->moves = moves; 
    this->allegiance = allegiance;
    this->i = i;
    this->j = j;
}


void Character::init_image(SDL_Renderer* renderer, const char* path, double scale_image, int xPos, int yPos)
{
    image.init(renderer, path, scale_image, xPos, yPos);
}

Character::~Character()
{
    image.destroy();
}
