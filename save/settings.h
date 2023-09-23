#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct settings_s {
    int widow_width;
    int window_height;
} settings_t;

extern settings_t settings;

void load_settings_file(void);

#endif //SETTINGS_H
