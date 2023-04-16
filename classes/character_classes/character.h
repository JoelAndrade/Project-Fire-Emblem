#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL_Classes.h>

class Character {
    public:
        const char* name;
        int hp;
        int attack;
        int defence;
        int speAtt;
        int speDef;
        int luck;
        int moves;

        bool selected;

        textureImage image;
        Character() {
            selected = false;
        }
        Character(const char* name, int hp, int attack, int defence, int speAtt, int speDef, int luck, int moves,
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

            selected = false;

            image.init(renderer, path, scaleImage, xPos, yPos);
        }

        void initStats(const char* name, int hp, int attack, int defence, int speAtt, int speDef, int luck, int moves) {
            this->name = name;
            this->hp = hp;
            this->attack = attack;
            this->defence = defence;
            this->speAtt = speAtt;
            this->speDef = speDef;
            this->luck = luck;
            this->moves = moves;
        }

        void initImage(SDL_Renderer* renderer, const char* path, double scaleImage = 1.0, int xPos = 0, int yPos = 0) {
            image.init(renderer, path, scaleImage, xPos, yPos);
        }

        ~Character() {
            image.destroy();
        }

};

#endif // CHARACTER_H