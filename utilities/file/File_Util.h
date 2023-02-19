#ifndef FILE_UTIL_H
#define FILE_UTIL_H

bool writeSave(void* myStruct, int structSize, const char* bin);
bool readSave(void* myStruct, int structSize, const char* bin);

#endif // FILE_UTIL_H