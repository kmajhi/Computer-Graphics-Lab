#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
void display();
void reshape(int,int);
void timer(int);

float x_position = 0;
float y_position = 0;
float step = 0.3;

void KeyboardKeys(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
float angle = 0.5f;

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
}
int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Window 1");

    glutKeyboardFunc(KeyboardKeys);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
}

//For 3d
void cube(){
    glBegin(GL_QUADS);

    // FRONT (z = 1)
    glColor3f(1.0,0.0,0.0);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);

    // BACK (z = -1)
    glColor3f(0.0,1.0,0.0);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);

    // LEFT
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);

    // RIGHT
    glColor3f(1.0,1.0,0.0);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);

    // TOP
    glColor3f(0.0,1.0,1.0);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);

    // BOTTOM
    glColor3f(1.0,0.5,0.0);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);

    glEnd();
}

//for 2d
/*
void drawSquare()
{
    glBegin(GL_QUADS);
    glColor3f(0.0,0.6,0.7);
    glVertex2f(  -1,1);
    glVertex2f( -1,-1);
    glVertex2f(  1, -1);
    glVertex2f(  1,1);
    glEnd();
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(0,5);
    glVertex2f(-2,1);
    glVertex2f(2,1);
    glEnd();
}

*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // move camera backward
    glTranslatef(0.0, 0.0, -7.0);
    glRotatef(angle, 0,1, 1);

    glPushMatrix();
    glTranslatef(x_position, y_position, 0);

    cube();

    glPopMatrix();

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w/(float)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{

    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
}

void specialKeys(int key, int x, int y)
{

    switch(key)
    {
    case GLUT_KEY_LEFT:
        x_position-=step;
        break;
    case GLUT_KEY_RIGHT:
        x_position+=step;
        break;
    case GLUT_KEY_UP:
        y_position+=step;
        break;
    case GLUT_KEY_DOWN:
        y_position-=step;
        break;
    }
}

void KeyboardKeys(unsigned char key, int x, int y){

    switch(key)
    {
    case 'a':
        angle-=5;
        break;

    }
}
