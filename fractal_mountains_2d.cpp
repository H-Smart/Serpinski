extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
}
#include <GLUT/glut.h>

#define PERTURBATION_MAG 0.5

GLfloat v[3][2] = {{0.0,0.0},{25.0,50.0},{50.0,0.0}};
int n = 5;
GLfloat vertices_3d[4][3] = {{0.0,0.0,0.0},{25.0,50.0,10.0},{50.0,25.0,25.0},{25.0,10.0,25.0}};


void myinit();
void triangle(GLfloat *a, GLfloat *b, GLfloat *c);
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int k);
void perturb_point_2d(GLfloat* point);
void display_fractal_mountains();

int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("simple OpenGL example");
    glutDisplayFunc(display_fractal_mountains);
    myinit();
    glutMainLoop();
}

void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.8, 0.4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 50.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}
void display_fractal_mountains()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    divide_triangle(v[0], v[1], v[2], n);
    glFlush();
}
void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    glBegin(GL_LINE_LOOP);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int k)
{
    GLfloat ab[2], ac[2], bc[2];
    int j;
    if(k>0)
    {
        for(j=0; j<2; j++) ab[j] = (a[j]+b[j])/2 + pow(2,k)*PERTURBATION_MAG*((rand()%20 - 10)/20.0);
        for(j=0; j<2; j++) ac[j] = (a[j]+c[j])/2 + pow(2,k)*PERTURBATION_MAG*((rand()%20 - 10)/20.0);
        for(j=0; j<2; j++) bc[j] = (b[j]+c[j])/2 + pow(2,k)*PERTURBATION_MAG*((rand()%20 - 10)/20.0);

        // subdivide all but inner triangle
        divide_triangle(a, ab, ac, k-1);
        divide_triangle(c, ac, bc, k-1);
        divide_triangle(b, bc, ab, k-1);

    } else triangle(a,b,c);
	
} 

void perturb_point_2d(GLfloat* point)
{
    point[0] = point[0] - 0.01;
    point[1] = point[0] + 0.01;
}
