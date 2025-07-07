#include "platform.h"
#ifdef __linux__
#include "linux_platform.cpp"
#endif
#include <iostream>

int main(){
    if(!create_window(1280, 720))
        std::cout<<"something went wrong creating a window";
    // init_input();
    // init_gl();
}
