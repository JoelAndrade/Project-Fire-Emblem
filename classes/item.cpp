#include "item.h"
#include "character.h"

item::item(){}
item::item(const char* name, int uses, item_type_t type, void (*itemFunc)(void* characterObject))
{
    this->name     = name;
    this->uses     = uses;
    this->type     = type;
    this->itemFunc = itemFunc;
}

void item::init(const char* name, int uses, item_type_t type, void (*itemFunc)(void* characterObject))
{
    this->name     = name;
    this->uses     = uses;
    this->type     = type;
    this->itemFunc = itemFunc;
}

item::~item(){}



// Weapon items
void swords(void* characterObject)
{
    Character* characterVar = (Character*)characterObject;

    characterVar->attack += 5;
}

// Hold items
void chainMail(void* characterObject)
{
    Character* characterVar = (Character*)characterObject;

    characterVar->defence += 10;
}

// Consumables items
void potion(void* characterObject)
{
    Character* characterVar = (Character*)characterObject;
    
    characterVar->hp += 50;
}
