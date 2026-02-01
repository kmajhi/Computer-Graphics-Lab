#include <GL/gl.h> // Low level function
#include <GL/glu.h> //Utility function
#include <GL/glut.h> //  Windows - OS handle

void display ();
void reshape(int, int);

void init(){

glClearColor(.3, .2, .1, 1);

}

int main (int argc, char** argv){

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB|GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Lab1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

}

void display (){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    glColor3f(.5,.5,.2);
    glVertex2d(0,5);
    glVertex2d(-5,0);
    glVertex2d(5,0);
    glEnd();

    glutSwapBuffers();

}

void reshape(int w, int h){

glViewport(0,0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-10, 10, -10, 10);
glMatrixMode(GL_MODELVIEW);
}
