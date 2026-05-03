#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float rotX = 0, rotY = 0;

void init() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void drawPyramid() {

    glBegin(GL_TRIANGLES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);

    glColor3f(0, 1, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(2, -2, -2);

    glColor3f(0, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(2, -2, -2);
    glVertex3f(-2, -2, -2);

    glColor3f(1, 1, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, -2);
    glVertex3f(-2, -2, 2);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    glVertex3f(2, -2, -2);
    glVertex3f(-2, -2, -2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -8);

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    drawPyramid();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / h, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'a': rotY -= 5; break;
        case 'd': rotY += 5; break;
        case 'w': rotX -= 5; break;
        case 's': rotX += 5; break;
        case 27: exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Lab test final");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
