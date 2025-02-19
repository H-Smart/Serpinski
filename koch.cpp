extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
}
#include <GLUT/glut.h>

#define PI 3.14159265

GLfloat triangle[3][2] = {{10.0,10.0},{25.0,40.0},{40.0,10.0}};
int k = 6;

void myinit();
void display_koch_snowflake();
void divide_line_koch(GLfloat a[2], GLfloat b[2] , int k);

int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Koch Snowflake");
    glutDisplayFunc(display_koch_snowflake);
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

void rotate_point_2d(GLfloat* point, const GLfloat rotation)
{
    GLfloat temp[2];
    for(int j = 0; j<2; j++) temp[j] = point[j];
    point[0] = cos(rotation)*temp[0] - sin(rotation)*temp[1];
    point[1] = sin(rotation)*temp[0] + cos(rotation)*temp[1];
}

void generate_eq_triangle_points(const GLfloat centre[2],const GLfloat circumradius,const GLfloat rotation, GLfloat points[3][2])
{
    // Generate vertices
    points[0][0] = 0.0;
    points[0][1] = circumradius;
    points[1][0] = -1*sin(-1.0*(2*PI)/3.0)*circumradius;
    points[1][1] = cos(-1.0*(2*PI)/3.0)*circumradius;
    points[2][0] = -1*sin((2*PI)/3.0)*circumradius;
    points[2][1] = cos((2*PI)/3.0)*circumradius;
    // rotate by prescribed rotation
    for (int j = 0; j<3; j++) rotate_point_2d(points[j], rotation);
    // translate to centre
    for (int j = 0; j<3; j++){
        for (int i = 0; i <2; i++) points[j][i] = points[j][i] + centre[i];
    }
}

void draw_triangle(GLfloat* a, GLfloat* b, GLfloat* c)
{
    glBegin(GL_LINE_LOOP);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}

void koch( GLfloat points[3][2], int k){
    divide_line_koch(points[0],points[1],k);
    divide_line_koch(points[1],points[2],k);
    divide_line_koch(points[2],points[0],k);
}

void koch_inverse( GLfloat points[3][2], int k){
    divide_line_koch(points[0],points[2],k);
    divide_line_koch(points[2],points[1],k);
    divide_line_koch(points[1],points[0],k);
}

void display_koch_snowflake()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat t_points[3][2];
    GLfloat center[2] = {25.0,25.0};
    generate_eq_triangle_points(center,15.0, 0.0, t_points);
    koch(t_points,k);
    koch_inverse(t_points,  k);
    glFlush();
}


void draw_line(GLfloat* a, GLfloat* b)
{
    glBegin(GL_LINES);
    glVertex2fv(a);
    glVertex2fv(b);
    glEnd();
}

void divide_line_koch(GLfloat a[2], GLfloat b[2], int k)
{
    // Implement recursive line divide
    GLfloat ab[2], ab1[2], ab2[2], segment[2], segment_r[2], new_point[2];
    int j;

    if(k>0)
    {
        for(j=0; j<2; j++) ab[j] = b[j] - a[j];
        for(j=0; j<2; j++) segment[j] = (1.0/3.0)*ab[j];
        for(j=0; j<2; j++) ab1[j] = a[j] + segment[j];
        for(j=0; j<2; j++) ab2[j] = a[j] + 2.0*segment[j];

        // Rotate segment
        segment_r[0] = 0.5*segment[0] - (sqrt(3.0)/2.0)*segment[1];
        segment_r[1] = (sqrt(3.0)/2.0)*segment[0] + 0.5*segment[1];

        for(j=0; j<2; j++) new_point[j] = ab1[j] + segment_r[j]; 
        divide_line_koch(a,ab1,k-1);
        divide_line_koch(ab2,b,k-1);
        divide_line_koch(ab1,new_point,k-1);
        divide_line_koch(new_point,ab2,k-1);
    } else draw_line(a,b);

}
