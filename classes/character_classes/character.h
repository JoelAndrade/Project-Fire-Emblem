#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL_Classes.h>

class character {
    public:
        const char* name;
        int hp;
        int attack;
        int defence;
        int speAtt;
        int speDef;
        int luck;
        int moves;

        textureImage image;
        character() {}
        character(const char* name, int hp, int attack, int defence, int speAtt, int speDef, int luck, int moves,
                  SDL_Renderer* renderer, const char* path, double scaleImage = 1.0, int xPos = 0, int yPos = 0) 
        {
            this->name = name;
            this->hp = hp;
            this->attack = attack;
            this->defence = defence;
            this->speAtt = speAtt;
            this->speDef = speDef;
            this->luck = luck;
            this->moves = moves;

            image.init(renderer, path, scaleImage, xPos, yPos);
        }

        void init(const char* name, int hp, int attack, int defence, int speAtt, int speDef, int luck, int moves,
             SDL_Renderer* renderer, const char* path, double scaleImage = 1.0, int xPos = 0, int yPos = 0) 
        {
            this->name = name;
            this->hp = hp;
            this->attack = attack;
            this->defence = defence;
            this->speAtt = speAtt;
            this->speDef = speDef;
            this->luck = luck;
            this->moves = moves;

            image.init(renderer, path, scaleImage, xPos, yPos);
        }

};

#endif // CHARACTER_H