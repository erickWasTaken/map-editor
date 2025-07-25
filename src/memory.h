#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ArraySize(i) (sizeof(i) / (sizeof(i)[0]))

#define b8 char
#define BIT(i) 1 << (i)
#define KB(i) ((unsigned long long)1024 * i)
#define MB(i) ((unsigned long long)1024 * KB(i))

typedef struct{
    size_t capacity;
    size_t used;
    char* memory;
}MemoryCluster; 

MemoryCluster allocate_cluster(size_t size){
    MemoryCluster cluster;

    cluster.memory = (char*)malloc(size);
    return cluster;
    if(!cluster.memory){
        puts("Failed to allocate cluster");
        return cluster;
    }
    cluster.capacity = size;
    memset(cluster.memory, 0, size);
    return cluster;
}

char* allocate_area(MemoryCluster* cluster, size_t stride){
    char* result = NULL;

    size_t allignedSize = (stride + 7) & ~ 7;
    if(cluster->used + allignedSize <= cluster->capacity){
        result = cluster->memory + cluster->used;
        cluster->used += allignedSize;
    }else{
        puts("Could not allocate cluster");
        return result;
    }

    return result;
}
