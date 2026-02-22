#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

float hourAngle = 0;
float minuteAngle = 0;
float secondAngle = 0;

void display();
void reshape(int,int);
void timer(int);

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

// Clock Body
void drawCircle(float radius, float r, float g, float b) {
    GLUquadric *quad = gluNewQuadric();

    glColor3f(r, g, b);
    gluDisk(quad, 0, radius, 80, 1);

    glColor3f(0, 0, 0);
    gluQuadricDrawStyle(quad, GLU_SILHOUETTE);
    gluDisk(quad, 0, radius, 80, 1);
}

// Hand
void drawHand(float length, float width){
    glBegin(GL_QUADS);
        glVertex2f(-width, 0);
        glVertex2f(width, 0);
        glVertex2f(width, length);
        glVertex2f(-width, length);
    glEnd();
}

// Hour Ticks
void drawTicks(){
    for(int i=0; i<12; i++){
        glPushMatrix();
            glRotatef(i*30, 0,0,1);
            glColor3f(0,0,0);

            glBegin(GL_QUADS);
                glVertex2f(-0.05, 2.7);
                glVertex2f(0.05, 2.7);
                glVertex2f(0.05, 3.0);
                glVertex2f(-0.05, 3.0);
            glEnd();
        glPopMatrix();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Clock Body
    drawCircle(3, 0.97, 0.97, 0.97);

    // Ticks
    drawTicks();

    // Hour Hand (Dark Green)
    glPushMatrix();
        glRotatef(hourAngle, 0,0,1);
        glColor3f(0.0, 0.4, 0.0);
        drawHand(1.5, 0.08);
    glPopMatrix();

    // Minute Hand (Blue)
    glPushMatrix();
        glRotatef(minuteAngle, 0,0,1);
        glColor3f(0.0, 0.2, 0.8);
        drawHand(2.2, 0.06);
    glPopMatrix();

    // Second Hand (Red)
    glPushMatrix();
        glRotatef(secondAngle, 0,0,1);
        glColor3f(1.0, 0.0, 0.0);
        drawHand(2.6, 0.03);
    glPopMatrix();

    // Center Dot
    GLUquadric *center = gluNewQuadric();
    glColor3f(0,0,0);
    gluDisk(center, 0, 0.12, 40, 1);

    glutSwapBuffers();
}

// Flexible Reshape (Prevents Stretching)
void reshape(int w, int h){
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;

    if(aspect >= 1)
        gluOrtho2D(-4*aspect, 4*aspect, -4, 4);
    else
        gluOrtho2D(-4, 4, -4/aspect, 4/aspect);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    secondAngle -= 6;       // 6 degrees per second
    minuteAngle -= 0.1;     // slow movement
    hourAngle   -= 0.008;   // very slow movement

    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

int main(int argc, char**argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("Analog Clock");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
