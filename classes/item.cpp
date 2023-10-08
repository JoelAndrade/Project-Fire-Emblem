#include "item.h"
#include "character.h"

// item class 
item::item(){}
item::item(const char* name, int uses, item_type_t type, void (*item_func)(void* character_object))
{
    this->name     = name;
    this->uses     = uses;
    this->type     = type;
    this->item_func = item_func;
}

void item::init(const char* name, int uses, item_type_t type, void (*item_func)(void* character_object))
{
    this->name     = name;
    this->uses     = uses;
    this->type     = type;
    this->item_func = item_func;
}

item::~item(){}



// Weapon items
void swords(void* character_object)
{
    Character* character_var = (Character*)character_object;

    character_var->attack += 5;
}

// Hold items
void chain_mail(void* character_object)
{
    Character* character_var = (Character*)character_object;

    character_var->defence += 10;
}

// Consumables items
void potion(void* character_object)
{
    Character* character_var = (Character*)character_object;

    character_var->hp += 50;
}
