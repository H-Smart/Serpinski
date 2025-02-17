extern "C" {
#include <stdio.h>
#include <stdlib.h>
}
#include <GLUT/glut.h>

void my_init();
void display_line();

int main(int argc, char* argv[]){
    // library testing here...
    //
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Library Testing");
    glutDisplayFunc(display_line);
    my_init();
    glutMainLoop();
}

void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.8, 0.4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 50.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void WritePixel(GLfloat *a){
    glBegin(GL_POINTS);
    glVertex2fv(a);
    glEnd();
}

void display_line()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 1; i< 50; i++){
         GLfloat a[2] = {25.0,(GLfloat) i};
         WritePixel(a);
    }
    glFlush();
}

void ReadPixel(){
    // Read the pixel
}
