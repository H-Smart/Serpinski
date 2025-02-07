extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
}
#include <GLUT/glut.h>

#define PROGRAM_COUNT 3
enum Program {
    DISPLAY_POINTS = 1, 
    DISPLAY_SERPINSKI_TRIANGLE,
    DISPLAY_TRIANGLE,
};
const char *program_names_cli[] = {"serpp", "serpt", "triangle"};

GLfloat v[3][2] = {{0.0,0.0},{25.0,50.0},{50.0,0.0}};
int n = 5;

int process_input(int argc, char* argv[]);
void myinit();
void triangle(GLfloat *a, GLfloat *b, GLfloat *c);
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int k);
void display_serpinski_points();
void display_serpinski_triangle();
void display_triangle();

int main(int argc, char* argv[])
{
    int program = process_input(argc, argv);
    if(!program) return 0;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("simple OpenGL example");
    switch (program) {
        case DISPLAY_POINTS:
            printf("Displaying Serpinski Triangle w/ Points\n");
            glutDisplayFunc(display_serpinski_points);
            break;
        case DISPLAY_SERPINSKI_TRIANGLE:
            printf("Displaying Serpinski Triangle w/ Triangles\n");
            glutDisplayFunc(display_serpinski_triangle);
            break;
        case DISPLAY_TRIANGLE:
        printf("Displaying Triangle\n");
            glutDisplayFunc(display_triangle);
            break;
        default:
            printf("ERROR");
            return 0;
    }
    myinit();
    glutMainLoop();
}

int process_input(int argc, char* argv[]){
    if(argc != 2)
    {
        printf("Only one argument allowed.\n");
        return 0;
    }

    for (int i=1; i<= PROGRAM_COUNT; i++){
        if(!strcmp(argv[1],program_names_cli[i-1])){
            return i;
        }
    }
    printf("Invalid argument.\n");
    return 0;
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
void display_serpinski_points()
{
    GLfloat vertices[3][2] = {{0.0,0.0},{25.0,50.0},{50.0,0.0}};
    int i, j, k;
    GLfloat p[2] = {7.5, 5.0};

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for( k=0; k<20000; k++)
    {
        j=rand()%3;

        p[0] = (p[0] + vertices[j][0])/2.0;
        p[1] = (p[1] + vertices[j][1])/2.0;

        glVertex2fv(p);
    }
    glEnd();
    glFlush();
}
void display_triangle(){
    GLfloat p1[2] = {25.0, 50.0};
    GLfloat p2[2] = {50.0, 0};
    GLfloat p3[2] = {0.0, 0.0};
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    triangle(p1,p2, p3);

    glEnd();
    glFlush();
}
void display_serpinski_triangle(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        divide_triangle(v[0], v[1], v[2], n);
    glEnd();
    glFlush();
}
void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int k)
{
    GLfloat ab[2], ac[2], bc[2];
    int j;
    if(k>0)
    {
        for(j=0; j<2; j++) ab[j] = (a[j]+b[j])/2;
        for(j=0; j<2; j++) ac[j] = (a[j]+c[j])/2;
        for(j=0; j<2; j++) bc[j] = (b[j]+c[j])/2;

        // subdivide all but inner triangle
        divide_triangle(a, ab, ac, k-1);
        divide_triangle(c, ac, bc, k-1);
        divide_triangle(b, bc, ab, k-1);

    } else triangle(a,b,c);
	
} 
