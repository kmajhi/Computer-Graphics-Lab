#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void display();
void reshape(int,int);
void timer(int);
void KeyboardKeys(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

float rotateX = 0.0f;
float rotateY = 0.0f;
float scaleValue = 1.0f;
bool lightOn = false;

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);

    GLfloat light_position[] = {3.0, 1.0, 5.0, 1.0};
    GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[]  = {0.8, 0.8, 0.8, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Table using Cube");

    glutKeyboardFunc(KeyboardKeys);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
}

void cube()
{
    glBegin(GL_QUADS);

    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);

    glColor3f(0.2f, 0.7f, 0.3f);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);

    glColor3f(0.2f, 0.4f, 0.8f);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);

    glColor3f(0.9f, 0.7f, 0.2f);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);

    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);

    glEnd();
}

void drawTable()
{
    glPushMatrix();
    glScalef(3.0f, 0.25f, 2.0f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5f, -2.0f, 1.5f);
    glScalef(0.25f, 1.8f, 0.25f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5f, -2.0f, 1.5f);
    glScalef(0.25f, 1.8f, 0.25f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5f, -2.0f, -1.5f);
    glScalef(0.25f, 1.8f, 0.25f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5f, -2.0f, -1.5f);
    glScalef(0.25f, 1.8f, 0.25f);
    cube();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);

    glScalef(scaleValue, scaleValue, scaleValue);

    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);

    drawTable();

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
    case GLUT_KEY_UP:
        scaleValue += 0.1f;
        break;

    case GLUT_KEY_DOWN:
        scaleValue -= 0.1f;
        if(scaleValue < 0.2f)
            scaleValue = 0.2f;
        break;
    }
}

void KeyboardKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'w':
        rotateY += 5.0f;
        break;

    case 'a':
        rotateX += 5.0f;
        break;

    case 'l':
        lightOn = !lightOn;

        if(lightOn)
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        }
        else
        {
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }
        break;
    }
}
