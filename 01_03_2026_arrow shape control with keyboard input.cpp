#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

float x_position = 0.0f;
float y_position = 0.0f;

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


void specialKeys(int key, int x, int y)
{
    float step = 0.5f;

    switch(key){
        case GLUT_KEY_UP:
            y_position += step;
            break;
        case GLUT_KEY_DOWN:
            y_position -= step;
            break;
        case GLUT_KEY_LEFT:
            x_position -= step;
            break;
        case GLUT_KEY_RIGHT:
            x_position += step;
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Arrow");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(specialKeys); // Added for arrow keys

    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glutMainLoop();
}
