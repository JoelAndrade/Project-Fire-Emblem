#ifndef ITEM_H
#define ITEM_H

typedef enum item_type_e {
    WEAPON,
    HOLD,
    CONSUMABLE,
} item_type_t;

class item
{
public:
    const char* name;
    item_type_t type;
    int uses;
    void (*item_func)(void* character_object);

    item();
    item(const char* name, int uses, item_type_t type, void (*item_func)(void* character_object));

    void init(const char* name, int uses, item_type_t type, void (*item_func)(void* character_object));

    ~item();
};

void swords(void* character_object);
void chain_mail(void* character_object);
void potion(void* character_object);

#endif // ITEM_H

