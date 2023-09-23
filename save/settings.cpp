#include "settings.h"

#include <File_Util.h>

// Defalult settings
settings_t settings = {
    .widow_width   = 1280,
    .window_height = 720
};

void load_settings_file(void) 
{
    if (!read_save(&settings, sizeof(settings), "./setting.bin")) {
        write_save(&settings, sizeof(settings), "./setting.bin");
    }
}
