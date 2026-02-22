#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void display();
void reshape(int,int);
void timer(int);

float truckX = 0.0f;
float direction = 0.1f;

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void drawSquare(float r, float g, float b){
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(-1, 1); glVertex2f(-1, -1);
    glVertex2f(1, -1); glVertex2f(1, 1);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1, 1); glVertex2f(-1, -1);
    glVertex2f(1, -1); glVertex2f(1, 1);
    glEnd();
}

void drawCircle(float r, float g, float b) {
    GLUquadric *quad;
    quad = gluNewQuadric();

    glColor3f(r, g, b);
    gluDisk(quad, 0, 1, 32, 1);

    glColor3f(0, 0, 0);
    gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
    gluDisk(quad, 0, 1, 32, 1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(2.5 + truckX, 1.0, 0);
        glScalef(5.0, 3.5, 1.0);
        drawSquare(0.2, 0.5, 0.9);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4.5 + truckX, -0.5, 0);
        glScalef(2.0, 2.0, 1.0);
        drawSquare(0.9, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4.2 + truckX, 0.2, 0);
        glScalef(1.2, 0.8, 1.0);
        drawSquare(0.7, 0.9, 1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4.0 + truckX, -2.5, 0);
        glScalef(1.3, 1.3, 1.0);
        drawCircle(0.3, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.5 + truckX, -2.5, 0);
        glScalef(1.3, 1.3, 1.0);
        drawCircle(0.3, 0.3, 0.3);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    truckX += direction;

    if(truckX > 2.0f) direction = -0.1f;
    if(truckX < -3.0f) direction = 0.1f;

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

int main(int argc, char**argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Lab task");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
