#include <GL/glut.h>

void display(){
    glutSwapBuffers();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // Display with double RGBA buffering
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Map Editor");
    glPointSize(5);                                 // Pixel size
    glViewport(0, 0, 1280, 720);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
