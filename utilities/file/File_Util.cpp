#include <File_Util.h>
#include <iostream>

bool writeSave(void* myStruct, int structSize, const char* bin) {
    FILE* myFile = fopen(bin, "wb");
    if (myFile == NULL) {
        return false;
    }

    fwrite(myStruct, structSize, 1, myFile);
    fclose(myFile);

    return true;
}

bool readSave(void* myStruct, int structSize, const char* bin) {
    FILE* myFile = fopen(bin, "rb");
    if (myFile == NULL) {
        return false;
    }
    
    fread(myStruct, structSize, 1, myFile);
    fclose(myFile);

    return true;
}