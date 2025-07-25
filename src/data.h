#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

long get_file_size(const char* filePath){
    if(!filePath){
        puts("No file path provided!");
        return 0;
    }

    long fileSize = 0;
    FILE *file = fopen(filePath, "rb");
    if(!file){
        puts("Failed to open file!");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return fileSize;
}

char* write_to_buffer(const char* filePath, int* fileSize, char* buffer){
    if(!filePath || !fileSize || !buffer)
        return NULL;

    *fileSize = 0;
    FILE *file = fopen(filePath, "rb");
    if(!file){
        printf("Failed to open file: %s", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    memset(buffer, 0, *fileSize + 1);
    fread(buffer, sizeof(char), *fileSize, file);

    fclose(file);
    return buffer;
}

char* read_file(const char* filePath, int* fileSize, MemoryCluster* cluster){
    char* file = NULL;
    long sourceSize = get_file_size(filePath);
    if(sourceSize){
        char* buffer = allocate_area(cluster, sourceSize + 1);
        file = write_to_buffer(filePath, fileSize, buffer);
    }

    return file;
}

