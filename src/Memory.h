#pragma once
#ifdef __linux__
#define DEBUG_BREAK() __buitin_trap();
#define EXPORT_FN
#endif

#define BIT(x) 1 << (x)
#define b8 char
#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))

#include <stdlib.h>
#include <string.h>

template<typename T, int N>
struct Array{
    static constexpr int maxElements = N;
    int count = 0;
    T elements[N];

    T& operator[](int id){
        if(!in_bounds(id))
            return nullptr;
        return elements[id];
    }

    int add(T element){
        if(!in_bounds(count + 1))
            return -1;
        elements[count] = element;
        return count++;
    }

    void remove(int id){
        if(!in_bounds(id))
            return;
        elements[id] = elements[--count];
    }

    void clear(){
        count = 0;
    }

    bool in_bounds(int id){
        return id >= 0 && id < count;
    }
};

struct MemoryCluster{
    size_t capacity;
    size_t used;
    char* memory;
};

MemoryCluster calloc(size_t size){
    MemoryCluster cluster = {};
    cluster.memory = (char*)malloc(size);
    cluster.capacity = size;
    memset(cluster.memory, 0, size);
    return cluster;
}
