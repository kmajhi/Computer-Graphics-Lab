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

    //front
    glColor3f(1.0,0.0,0.0); //red
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);


    //rear/back
    glColor3f(0.0,1.0,0.0);//green
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);

    //left
    glColor3f(0.0,0.0,1.0);//blue
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);

    //right
    glColor3f(1.0,1.0,0.0);//yellow
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);

    //up
    glColor3f(0.0,1.0,1.0);//cyan
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);

    //down
    glColor3f(1.0,0.5,0.0);//orange
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);



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

    glPushMatrix();
    glRotatef(angle,0,1,0);
    glTranslatef(x_position, y_position,0);

    cube();// For the cube

    glPushMatrix();
    glScalef(2,2,1);
    //drawSquare();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5,1,1);
    //drawTriangle();
    glPopMatrix();

    glPopMatrix();


    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-10,10,-10,10);
    gluPerspective(60,1,2.0,50.5);
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
        angle-=step;
        break;

    }
}
