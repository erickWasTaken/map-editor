#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#define res 1
#define SW 160*res
#define SH 120*res
#define pixelScale 4/res
#define GLSW SW*pixelScale
#define GLSH SH*pixelScale

typedef struct{
    int mouseX, mouseY;
    int wallTex, wallU, wallV;
    int surfTex, surfScale;
    int bottom, top;
    int scale;
    int selS, selW;
}grid; grid G;

void init(){
    G.scale = 4;
    G.selS = 0; G.selW = 0;
    G.bottom = 0; G.top = 40;
    G.surfTex = 1; G.surfScale = 4;
    G.wallTex = 0; G.wallU = 1; G.wallV = 1;
}

void drawPixel(int x, int y, int r, int g, int b){
    glColor3ub(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b){
    float x = x2 - x1;
    float y = y2 - y1;
    float max = fabs(x);
    if(fabs(y) > max)
        max = fabs(y);

    x /= max;
    y /= max;

    for(int i = 0; i < max; i++){
        drawPixel(x1 / G.scale, y1 / G.scale, r, g, b);
        x1 += x;
        y1 += y;
    }
}

void display(){
    drawLine(100, 100, 20, 10, 255, 255, 255);                         // NDC coords
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);            // Display with double RGBA buffering
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(GLSW, GLSH);
    glutCreateWindow("Map Editor");
    glPointSize(pixelScale);                                 // Pixel size
    glOrtho(0, GLSW, GLSH, 0, 0, 100);
    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
