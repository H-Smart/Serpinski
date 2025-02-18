extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
}
#include <GLUT/glut.h>

#define PI 3.14159265
#define TURTLE_X_DEFAULT 25.0
#define TURTLE_Y_DEFAULT 25.0
#define TURTLE_THETA_DEFAULT 90.0

GLfloat v[3][2] = {{0.0,0.0},{25.0,50.0},{50.0,0.0}};
GLfloat vertices_3d[4][3] = {{0.0,0.0,0.0},{25.0,50.0,10.0},{50.0,25.0,25.0},{25.0,10.0,25.0}};

GLfloat g_turtle_x = TURTLE_X_DEFAULT;
GLfloat g_turtle_y = TURTLE_Y_DEFAULT;
GLfloat g_turtle_theta = TURTLE_THETA_DEFAULT;
bool g_pen_down = true;

void myinit();
void triangle(GLfloat *a, GLfloat *b, GLfloat *c);
void display_turtle();
void init(GLfloat x, GLfloat y, GLfloat theta);
void forward(GLfloat d);
void right(GLfloat theta);
void left(GLfloat theta);
void pen(bool down_up);


int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Turtle");
    glutDisplayFunc(display_turtle);
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

void draw_body()
{
    pen(true);
    init(15.0, 35.0, 0.0);
    forward(20.0);
    right(90.0);
    forward(20.0);
    right(90.0);
    forward(20.0);
    right(90.0);
    forward(20.0);
    pen(false);
}

void draw_head()
{
    pen(true);
    init(20.0, 35.0, 90.0);
    forward(7.5);
    right(90.0);
    forward(10.0);
    right(90.0);
    forward(7.5);
    pen(false);
}

void draw_rectangle(GLfloat height, GLfloat width, GLfloat* centre, GLfloat rotation)
{
    pen(true);
    init(centre[0] - 0.5*width, centre[1] + 0.5*height,rotation);
    forward(width);
    right(90.0);
    forward(height);
    right(90.0);
    forward(width);
    right(90.0);
    forward(height);
    pen(false);
}

void draw_line(GLfloat* a, GLfloat*b)
{
    pen(true);
    init(a[0], a[1], (180.0/PI)*atan2((b[1]-a[1]),(b[0]-a[0])));
    forward(sqrt(pow((b[1]-a[1]),2) + pow((b[0]-a[0]),2)));
    pen(false);
}

void draw_triangle(GLfloat* a, GLfloat* b, GLfloat* c)
{
    pen(true);
    draw_line(a,b);
    draw_line(b,c);
    draw_line(c,a);
    pen(false);
}

void draw_tail()
{
    GLfloat tail_points[3][2] = {{22.5,15.0},{27.5,15.0},{25.0,10.0}};
    draw_triangle(tail_points[0], tail_points[1], tail_points[2]);
}

void draw_legs()
{
    GLfloat left_foreleg[2] = {12.5,30};
    draw_rectangle(5,5,left_foreleg,0.0);
    GLfloat right_foreleg[2] = {37.5,30};
    draw_rectangle(5,5,right_foreleg,0.0);

    GLfloat left_hindleg[2] = {12.5,20};
    draw_rectangle(5,5,left_hindleg,0.0);
    GLfloat right_hindleg[2] = {37.5,20};
    draw_rectangle(5,5,right_hindleg,0.0);
}

void display_turtle()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    draw_body();
    draw_head();
    draw_tail();
    draw_legs();
    glFlush();
}

void init(GLfloat x, GLfloat y, GLfloat theta)
{
    //update global parameters
    g_turtle_x = x;
    g_turtle_y = y;
    g_turtle_theta = theta;
}

void forward(GLfloat d)
{
    // calculate new co-ordinates
    GLfloat turtle_x_new = g_turtle_x + d*cos(g_turtle_theta*PI/180.0);
    GLfloat turtle_y_new = g_turtle_y + d*sin(g_turtle_theta*PI/180.0);
    // Draw line if pen down
    if (g_pen_down){
        glBegin(GL_LINES);
        GLfloat linestart[2] = {g_turtle_x,g_turtle_y};
        glVertex2fv(linestart);
        GLfloat line_end[2] = {turtle_x_new,turtle_y_new};
        glVertex2fv(line_end);
        glEnd();
    }
    // Update turtle position
    g_turtle_x = turtle_x_new;
    g_turtle_y = turtle_y_new;
}

void right(GLfloat angle)
{
    // Add to the global angle
    g_turtle_theta = g_turtle_theta - angle;
}

void left(GLfloat angle)
{
    // Subtract from the global angle
    g_turtle_theta = g_turtle_theta + angle;
}

void pen(bool pen_down)
{
    g_pen_down = pen_down;
}

void WritePixel(GLfloat *a){
    glBegin(GL_POINTS);
    glVertex2fv(a);
    glEnd();
}
