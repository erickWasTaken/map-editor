#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool read_file(const char* filePath, int* fileSize, char* buffer){
    if(!filePath || !fileSize || !buffer)
        return false;

    *fileSize = 0;
    FILE *file = fopen(filePath, "rb");
    if(!file){
        printf("Failed to open file: %s", filePath);
        return false;
    }

    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    memset(buffer, 0, *fileSize + 1);
    fread(buffer, sizeof(char), *fileSize, file);

    fclose(file);
    return buffer;
}
