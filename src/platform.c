#include "platform.h"
#include <GL/glx.h>
#include <stdio.h>

void* load_gl_function(const char* funcName){
    void* proc = (void*)glXGetProcAddress((const GLubyte*)funcName);
    if(!proc){
        printf("Failed to load function: %s", funcName);
    }
    return proc;
}
