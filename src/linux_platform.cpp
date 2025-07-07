#include "platform.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

static PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT_ptr;
static Display* display;
static Atom wmDeleteWindow;
static Window window;

bool create_window(int width, int height){
    display = XOpenDisplay(NULL);
    window = XCreateSimpleWindow(
        display,
        DefaultRootWindow(display),
        10,     // xPos
        10,     // yPos
        width,
        height,
        0,      // border width
        0,      // border height
        0       // background
    );

    int pixelAttribs[] = {
        GLX_DOUBLEBUFFER,   True,
        GLX_RED_SIZE,       8,
        GLX_GREEN_SIZE,     8,
        GLX_BLUE_SIZE,      8,
        None
    };

    int fbcCount = 0;
    GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display), pixelAttribs, &fbcCount);

    if(!fbc){
        // SM_ASSERT(false, "failed to create window!");
        return false;
    }

    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    glXSwapIntervalEXT_ptr = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");

    int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB,      4,
        GLX_CONTEXT_MINOR_VERSION_ARB,      3,
        GLX_CONTEXT_PROFILE_MASK_ARB,       GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB,              GLX_CONTEXT_DEBUG_BIT_ARB,
        None
    };

    GLXContext rc = glXCreateContextAttribsARB(display, fbc[0], NULL, true, contextAttribs);
    if(!rc){
        return false;
    }

    long event_mask = 
        ExposureMask
        | KeyPressMask      | KeyReleaseMask
        | ButtonPressMask   | ButtonReleaseMask;

    XSelectInput(display, window, event_mask);
    XMapWindow(display, window);
    glXMakeCurrent(display, window, rc);

    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

    return true;
}

void* load_gl_function(char* funcName){
    void* proc = (void*)glXGetProcAddress((const GLubyte*)funcName);
    if(!proc)
        return nullptr;
    return proc;
}
