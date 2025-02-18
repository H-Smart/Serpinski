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
int n = 5;

GLfloat g_turtle_x = TURTLE_X_DEFAULT;
GLfloat g_turtle_y = TURTLE_Y_DEFAULT;
GLfloat g_turtle_theta = TURTLE_THETA_DEFAULT;
bool g_pen_down = true;

void myinit();
void triangle(GLfloat *a, GLfloat *b, GLfloat *c);
void display_turtle_gasket();
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
    glutDisplayFunc(display_turtle_gasket);
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

    } else draw_triangle(a,b,c);
	
}

void display_turtle_gasket()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    divide_triangle(v[0], v[1], v[2], n);
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


