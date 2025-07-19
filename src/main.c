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

typedef struct{
    int x;
    int y;
}MousePos; MousePos mousePos;

typedef struct{
    int x;
    int y;
}ivec2;

typedef struct{
    ivec2 vertices[128];
    int count;
}mesh; mesh drawData[10];

typedef struct{
    int r;
    int g;
    int b;
}color; color bg;

typedef struct{
    ivec2 pos; 
    float zoom;
    int moveSpeed;
}camera; camera cam;

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

void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b){
    float x = x2 - x1;
    float y = y2 - y1;
    float max = fabs(x);
    if(fabs(y) > max)
        max = fabs(y);

    x /= max;
    y /= max;

    for(int i = 0; i < max; i++){
        drawPixel(x1, y1, r, g, b);
        x1 += x;
        y1 += y;
    }
}

void save(){
    FILE *fp = fopen("src/level.h", "w");
    if(!fp){
        printf("Save(); Failed to open level.h");
        return;
    }
    if(drawData[0].count == 0){
        printf("No data to save");
        return;
    }

    fprintf(fp, "%i\n", drawData[0].count);
    for(int i = 0; i < drawData[0].count; i++){
        ivec2 vert = drawData[0].vertices[i];
        fprintf(fp, "%i %i\n", vert.x, vert.y);
    }

    fclose(fp);
}

void load(){
    FILE *fp = fopen("src/level.h", "r");
    if(!fp){
        printf("Load(): Failed to open level.h");
        return;
    }
        
    fscanf(fp, "%i", &drawData[0].count);
    for(int i = 0; i < drawData[0].count; i++){
        fscanf(fp, "%i %i", &drawData[0].vertices[i].x, &drawData[0].vertices[i].y);
    }

    fclose(fp);
}

void click(int button, int state, int x, int y){
    if(state == GLUT_UP)
        return;
    if(x > 580){
        if(y > 400){
            save();
            return;
        }else if(y > 319){
            load();
            return;
        }else if(y > 239){ // Clears drawData
            drawData[0].count = 0;
            drawData[0].vertices[0].x = '\0';
            return;
        }
    }
    else{
        ivec2 point = {cam.pos.x + x, cam.pos.y + y};
        drawData[0].vertices[drawData[0].count] = point;
        drawData[0].count++;
    }
}

void mouse(int x, int y){
    mousePos.x = x;
    mousePos.y = y;
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        // inverted. pos is the offset to be added to geometry
        case 'a':
            cam.pos.x += cam.moveSpeed;
            break;
        case 'd':
            cam.pos.x -= cam.moveSpeed;
            break;
        case 's':
            cam.pos.y += cam.moveSpeed;
            break;
        case 'w':
            cam.pos.y -= cam.moveSpeed;
            break;
        case 'A':
        case 'S':
            cam.zoom -= 1;
            if(cam.zoom < 1)
                cam.zoom = 10;
            break;

        case 'D':
        case 'W':
            cam.zoom += 1;
            if(cam.zoom > 10)
                cam.zoom = 1;
            break;
    }
}

void clear_background(){
    int h = (GLSH / 8) * cam.zoom;

    for(int i = 0; i < GLSW; i++){
        for(int j = 0; j < GLSH; j++){
            int x = i - cam.pos.x;
            int y = j - cam.pos.y;
            if(((x / h) % 2 == 0 && (y / h) % 2 == 1) || ((x / h) % 2 == 1 && (y / h) % 2 == 0)){
                bg.r = 60; bg.g = 60; bg.b = 60;
            }else{
                bg.r = 0; bg.g = 0; bg.b = 0;
            }
            drawPixel(i, j, bg.r, bg.g, bg.b);
        }
    }

    for(int x = 581; x < GLSW; x++){
        for(int y = 0; y < GLSH; y++){
            drawPixel(x, y, 255, 0, 0);
        }
    }

    if(mousePos.x >= 580){
        if(mousePos.y >= 400){
            for(int x = 580; x < GLSW; x++){
                for(int y = 400; y < GLSH; y++){
                    drawPixel(x, y, 127, 0, 0);
                }
            }
        }else if(mousePos.y > 319){
            for(int x = 580; x < GLSW; x++){
                for(int y = 320; y < 399; y++){
                    drawPixel(x, y, 127, 0, 0);
                }
            }
        }else if(mousePos.y > 239){
            for(int x = 580; x < GLSW; x++){
                for(int y = 240; y < 320; y++){
                    drawPixel(x, y, 127, 0, 0);
                }
            }
        }
    }
}

void display(){
    clear_background();
    drawPixel(mousePos.x, mousePos.y, 255, 0, 0);
    // drawLine(GLSW /(2 + pixelScale), GLSH/(2 + pixelScale), mousePos.x, mousePos.y, 255, 255, 255);                         

    mesh current = drawData[0];
    for(int i = 1; i < current.count; i++){
        drawLine(current.vertices[i -1].x * cam.zoom + cam.pos.x, 
                 current.vertices[i - 1].y * cam.zoom + cam.pos.y, 
                 current.vertices[i].x * cam.zoom + cam.pos.x, 
                 current.vertices[i].y * cam.zoom + cam.pos.y, 
                 255, 255, 255);
    }

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

    glutMouseFunc(click);
    cam.zoom = 1;
    cam.moveSpeed = 1;
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
