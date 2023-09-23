#include "settings.h"

#include <File_Util.h>

// Defalult settings
settings_t settings = {
    .widowWidth   = 1280,
    .windowHeight = 720
};

void loadSettingsFile(void) 
{
    if (!readSave(&settings, sizeof(settings), "./setting.bin")) {
        writeSave(&settings, sizeof(settings), "./setting.bin");
    }
}
