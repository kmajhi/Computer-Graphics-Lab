#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ctime>
#include <cmath>
#include <sstream> // for stringstream

int windowWidth = 500, windowHeight = 500;

// Draw clock circle
void drawCircle() {
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(0.9f * cos(angle), 0.9f * sin(angle));
    }
    glEnd();
}

// Draw a hand of the clock
void drawHand(float angle, float length, float width) {
    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    glLineWidth(width);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, length);
    glEnd();
    glPopMatrix();
}

// Draw clock ticks
void drawTicks() {
    for(int i=0; i<60; i++){
        float angle = i * 6 * 3.14159f / 180.0f; // 6 degrees per tick
        float inner = (i%5==0)?0.75f:0.85f;      // hour ticks longer
        float outer = 0.9f;
        glLineWidth((i%5==0)?3:1);
        glBegin(GL_LINES);
            glVertex2f(inner*sin(angle), inner*cos(angle));
            glVertex2f(outer*sin(angle), outer*cos(angle));
        glEnd();
    }
}

// Draw hour numbers
void drawNumbers() {
    for(int i=1; i<=12; i++){
        float angle = (i*30) * 3.14159f / 180.0f; // 30 degrees per hour
        float x = 0.65f * sin(angle);
        float y = 0.65f * cos(angle);

        // Convert number to string without C++11
        std::stringstream ss;
        ss << i;
        std::string num = ss.str();

        glRasterPos2f(x-0.03f, y-0.03f); // adjust to center numbers
        for(size_t j=0; j<num.length(); j++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, num[j]);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clock face
    glColor3f(0,0,0);
    drawCircle();
    drawTicks();
    drawNumbers();

    // Get current time
    time_t t; time(&t);
    struct tm *timeinfo = localtime(&t);
    int hours = timeinfo->tm_hour % 12;
    int minutes = timeinfo->tm_min;
    int seconds = timeinfo->tm_sec;

    // Calculate angles
    float secondAngle = -6 * seconds + 90;
    float minuteAngle = -6 * minutes - seconds*0.1 + 90;
    float hourAngle = -30 * hours - minutes*0.5 + 90;

    // Draw hands
    glColor3f(1,0,0); drawHand(secondAngle, 0.8f, 1); // seconds
    glColor3f(0,0,1); drawHand(minuteAngle, 0.6f, 3); // minutes
    glColor3f(0,0,0); drawHand(hourAngle, 0.4f, 5);   // hours

    // Draw center circle
    glPointSize(8);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();

    glutSwapBuffers();
}

// Reshape function
void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-1,1,-1.0f*(float)h/w,1.0f*(float)h/w);
    else
        gluOrtho2D(-1.0f*(float)w/h,1.0f*(float)w/h,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Timer for updating every second
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Enhanced Analog Clock");

    glClearColor(1,1,1,1); // white background

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
