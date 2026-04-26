/*
 * Moving Traffic Scene using GLUT template
 */

 #include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float tx = -500.0f;   // car position
float bx = -510.0f;   // truck position
float shift = 0.0f;   // cloud position

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void roundShape(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void Bushes()
{
    glColor3ub(0, 128, 0);
    circle(20, 30, 20, 180);
    circle(20, 30, 40, 210);
    circle(20, 30, 60, 180);

    glColor3ub(154, 205, 50);
    circle(20, 30, 430, 180);
    circle(20, 30, 450, 210);
    circle(20, 30, 470, 180);

    glColor3ub(0, 128, 0);
    circle(20, 30, 490, 180);
    circle(20, 30, 510, 210);
}

void road()
{
    glColor3ub(0, 128, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 75);
    glVertex2d(0, 75);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 55);
    glVertex2d(0, 55);
    glEnd();

    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 50);
    glVertex2d(0, 50);
    glEnd();

    for (int i = 15; i <= 465; i += 50)
    {
        glColor3ub(255, 255, 255);
        glBegin(GL_POLYGON);
        glVertex2d(i, 20);
        glVertex2d(i + 35, 20);
        glVertex2d(i + 35, 30);
        glVertex2d(i, 30);
        glEnd();
    }
}

void sun()
{
    glColor3ub(255, 255, 0);
    circle(20, 30, 450, 450);
}

void tree()
{
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(75, 180);
    glVertex2d(85, 180);
    glVertex2d(85, 350);
    glVertex2d(75, 350);
    glEnd();

    glColor3ub(0, 128, 0);
    circle(30, 40, 85, 370);
    circle(20, 30, 90, 340);
    circle(20, 30, 65, 395);

    glColor3ub(0, 100, 0);
    circle(40, 50, 45, 360);
    circle(30, 30, 60, 330);
    circle(20, 30, 30, 300);
    circle(20, 30, 60, 300);

    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(40, 180);
    glVertex2d(50, 180);
    glVertex2d(50, 296);
    glVertex2d(60, 320);
    glVertex2d(55, 326);
    glVertex2d(50, 300);
    glVertex2d(50, 350);
    glVertex2d(45, 350);
    glVertex2d(45, 310);
    glEnd();
}

void little_tree()
{
    int trunks[][2] = {
        {0, 60}, {65, 60}, {125, 60}, {190, 60},
        {300, 60}, {365, 60}, {425, 60}, {490, 60}
    };

    for (int i = 0; i < 8; i++)
    {
        int x = trunks[i][0];
        int y = trunks[i][1];

        glColor3ub(139, 69, 19);
        glBegin(GL_POLYGON);
        glVertex2d(x, y);
        glVertex2d(x + 10, y);
        glVertex2d(x + 10, y + 40);
        glVertex2d(x, y + 40);
        glEnd();

        glColor3ub(0, 100, 0);
        circle(15, 20, x, y + 50);
        circle(15, 20, x + 10, y + 50);
        circle(15, 20, x + 5, y + 70);
    }
}

void clouds()
{
    glPushMatrix();
    glTranslatef(shift, 0, 0);

    glColor3ub(255, 255, 255);
    roundShape(20, 30, 90, 460);
    roundShape(15, 20, 110, 460);
    roundShape(15, 20, 70, 460);

    roundShape(20, 30, 185, 430);
    roundShape(15, 20, 205, 430);
    roundShape(15, 20, 165, 430);

    glColor3ub(220, 220, 220);
    roundShape(20, 30, 390, 420);
    roundShape(15, 20, 405, 420);
    roundShape(15, 20, 375, 420);

    roundShape(20, 30, 460, 460);
    roundShape(15, 20, 445, 460);
    roundShape(15, 20, 475, 460);

    glPopMatrix();
}

void car()
{
    glPushMatrix();
    glTranslatef(tx, 0, 0);

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(410, 40);
    glVertex2d(490, 40);
    glVertex2d(485, 70);
    glVertex2d(410, 70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(420, 70);
    glVertex2d(475, 70);
    glVertex2d(465, 100);
    glVertex2d(430, 100);
    glEnd();

    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(425, 70);
    glVertex2d(445, 70);
    glVertex2d(445, 90);
    glVertex2d(430, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(450, 70);
    glVertex2d(470, 70);
    glVertex2d(465, 90);
    glVertex2d(450, 90);
    glEnd();

    glColor3ub(0, 0, 0);
    circle(10, 14, 435, 40);
    circle(10, 14, 465, 40);

    glColor3ub(245, 245, 245);
    circle(6, 10, 435, 40);
    circle(6, 10, 465, 40);

    glPopMatrix();
}

void truck()
{
    glPushMatrix();
    glTranslatef(bx, 0, 0);

    glColor3ub(127, 255, 212);
    glBegin(GL_POLYGON);
    glVertex2d(450, 40);
    glVertex2d(500, 40);
    glVertex2d(500, 110);
    glVertex2d(450, 110);
    glEnd();

    glColor3ub(220, 20, 60);
    glBegin(GL_POLYGON);
    glVertex2d(500, 40);
    glVertex2d(535, 40);
    glVertex2d(535, 70);
    glVertex2d(500, 70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(500, 70);
    glVertex2d(525, 70);
    glVertex2d(515, 90);
    glVertex2d(500, 90);
    glEnd();

    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(500, 70);
    glVertex2d(520, 70);
    glVertex2d(515, 85);
    glVertex2d(500, 85);
    glEnd();

    glColor3ub(0, 0, 0);
    circle(10, 14, 460, 40);
    circle(10, 14, 510, 40);

    glColor3ub(245, 245, 245);
    circle(6, 10, 460, 40);
    circle(6, 10, 510, 40);

    glPopMatrix();
}

void flower()
{
    glColor3ub(255, 0, 0);
    circle(3, 5, 450, 210);
    circle(3, 5, 455, 205);
    circle(3, 5, 455, 215);
    circle(3, 5, 460, 210);
    glColor3ub(255, 215, 0);
    circle(3, 5, 455, 210);

    glColor3ub(255, 0, 0);
    circle(3, 5, 440, 195);
    circle(3, 5, 440, 185);
    circle(3, 5, 435, 190);
    circle(3, 5, 445, 190);
    glColor3ub(255, 215, 0);
    circle(3, 5, 440, 190);

    glColor3ub(255, 0, 0);
    circle(3, 5, 470, 195);
    circle(3, 5, 470, 185);
    circle(3, 5, 465, 190);
    circle(3, 5, 475, 190);
    glColor3ub(255, 215, 0);
    circle(3, 5, 470, 190);

    glColor3ub(255, 0, 0);
    circle(3, 5, 30, 205);
    circle(3, 5, 30, 195);
    circle(3, 5, 25, 200);
    circle(3, 5, 35, 200);
    glColor3ub(255, 215, 0);
    circle(3, 5, 30, 200);

    glColor3ub(255, 215, 0);
    circle(3, 5, 10, 215);
    circle(3, 5, 10, 205);
    circle(3, 5, 5, 210);
    circle(3, 5, 15, 210);
    glColor3ub(255, 0, 0);
    circle(3, 5, 10, 210);
}

void roadLight()
{
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(80, 50);
    glVertex2d(85, 50);
    glVertex2d(85, 180);
    glVertex2d(80, 180);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(65, 150);
    glVertex2d(100, 150);
    glVertex2d(100, 155);
    glVertex2d(65, 155);
    glEnd();

    glColor3ub(255, 255, 255);
    circle(10, 15, 83, 180);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(30, 144, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 500);
    glVertex2d(0, 500);
    glEnd();

    Bushes();

    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 180);
    glVertex2d(0, 180);
    glEnd();

    little_tree();
    road();
    sun();
    clouds();
    tree();
    roadLight();
    truck();
    car();
    flower();

    glutSwapBuffers();
}

static void idle(void)
{
    // faster animation
    tx += 0.6f;      // car speed
    if (tx > 120.0f)
        tx = -500.0f;

    bx += 0.3f;      // truck speed
    if (bx > 120.0f)
        bx = -510.0f;

    shift += 0.1f;   // cloud speed
    if (shift > 500.0f)
        shift = -500.0f;

    glutPostRedisplay();
}

static void key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        shift -= 8.0f;
        break;
    case GLUT_KEY_RIGHT:
        shift += 8.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    if (key == 27 || key == 'q' || key == 'Q')
        exit(0);
}

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Moving cars project");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);
    glutSpecialFunc(key);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
