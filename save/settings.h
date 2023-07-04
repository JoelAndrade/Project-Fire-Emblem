#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct settings_s {
    int widowWidth;
    int windowHeight;
} settings_t;

extern settings_t settings;

void loadSettingsFile(void);

#endif //SETTINGS_H
