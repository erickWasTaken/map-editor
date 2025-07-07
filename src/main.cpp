#define APIENTRY
#define GL_GLEXT_PROTOTYPES
#include "glcorearb.h"

#include "platform.h"
#ifdef __linux__
#include "linux_platform.cpp"
#endif

#include "Memory.h"
#include "gl_loader.cpp"

#include <iostream>

int main(){
    MemoryCluster transientCluster = calloc(MB(50));  

    create_window(1280, 720);
    // init_input();
    init_gl(transientCluster);
}
