#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

float x_position = 0.0f;
float y_position = 0.0f;

bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(x_position, y_position, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -2.0f);
        glVertex2f( 1.0f, -2.0f);
        glVertex2f( 1.0f,  0.0f);
        glVertex2f(-1.0f,  0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f,  0.0f);
        glVertex2f( 3.0f,  0.0f);
        glVertex2f( 0.0f,  4.0f);
    glEnd();

    glutSwapBuffers();
}

void updatePosition()
{
    float step = 0.1f; // smaller step for smoother diagonal movement

    if(upPressed) y_position += step;
    if(downPressed) y_position -= step;
    if(leftPressed) x_position -= step;
    if(rightPressed) x_position += step;

    glutPostRedisplay();
}

void specialKeysDown(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:    upPressed = true; break;
        case GLUT_KEY_DOWN:  downPressed = true; break;
        case GLUT_KEY_LEFT:  leftPressed = true; break;
        case GLUT_KEY_RIGHT: rightPressed = true; break;
    }
}

void specialKeysUp(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:    upPressed = false; break;
        case GLUT_KEY_DOWN:  downPressed = false; break;
        case GLUT_KEY_LEFT:  leftPressed = false; break;
        case GLUT_KEY_RIGHT: rightPressed = false; break;
    }
}

void timer(int value)
{
    updatePosition();
    glutTimerFunc(16, timer, 0); // roughly 60 FPS
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Diagonal Movement");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(specialKeysDown);
    glutSpecialUpFunc(specialKeysUp); // track key release
    glutTimerFunc(0, timer, 0); // start movement updates

    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glutMainLoop();
}
