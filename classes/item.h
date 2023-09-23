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

    item();
    item(const char* name, int uses, item_type_t type, void (*itemFunc)(void* characterObject));

    void init(const char* name, int uses, item_type_t type, void (*itemFunc)(void* characterObject));
    void (*itemFunc)(void* characterObject);

    ~item();
};

void swords(void* characterObject);
void chainMail(void* characterObject);
void potion(void* characterObject);

#endif // ITEM_H

