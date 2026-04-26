#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float rotateX=0, rotateY=0;
float scaleValue=1.0f;
float traySlide=0.0f;
bool lightOn=true;

void reshape(int w,int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/h,1,100);

    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 🌟 REALISTIC WARM LIGHT
    GLfloat ambient[]  = {0.25f, 0.20f, 0.15f, 1.0f};
    GLfloat diffuse[]  = {0.85f, 0.75f, 0.60f, 1.0f};
    GLfloat specular[] = {0.20f, 0.20f, 0.20f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void cube()
{
    glBegin(GL_QUADS);

    // FRONT
    glNormal3f(0,0,1);
    glColor3f(0.72f,0.48f,0.25f);
    glVertex3f(1,1,1); glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1); glVertex3f(1,-1,1);

    // BACK
    glNormal3f(0,0,-1);
    glColor3f(0.62f,0.40f,0.20f);
    glVertex3f(1,1,-1); glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1); glVertex3f(1,-1,-1);

    // LEFT
    glNormal3f(-1,0,0);
    glColor3f(0.68f,0.44f,0.22f);
    glVertex3f(-1,1,1); glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1); glVertex3f(-1,-1,1);

    // RIGHT
    glNormal3f(1,0,0);
    glColor3f(0.68f,0.44f,0.22f);
    glVertex3f(1,1,1); glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1); glVertex3f(1,-1,1);

    // TOP
    glNormal3f(0,1,0);
    glColor3f(0.80f,0.55f,0.30f);
    glVertex3f(1,1,1); glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1); glVertex3f(1,1,-1);

    // BOTTOM
    glNormal3f(0,-1,0);
    glColor3f(0.50f,0.30f,0.15f);
    glVertex3f(1,-1,1); glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1); glVertex3f(1,-1,-1);

    glEnd();
}

void drawDesk()
{
    // TOP
    glPushMatrix();
    glScalef(4.5,0.2,2.8);
    cube();
    glPopMatrix();

    // LEFT PANEL
    glPushMatrix();
    glTranslatef(-4.2,-2.2,0);
    glScalef(0.2,2.2,2.8);
    cube();
    glPopMatrix();

    // RIGHT PANEL
    glPushMatrix();
    glTranslatef(4.2,-2.2,0);
    glScalef(0.2,2.2,2.8);
    cube();
    glPopMatrix();

    // BACK PANEL
    glPushMatrix();
    glTranslatef(0,-2.2,-2.6);
    glScalef(4.2,2.0,0.15);
    cube();
    glPopMatrix();

    // DRAWER BOX
    glPushMatrix();
    glTranslatef(2.5,-0.5,1.8);
    glScalef(1.6,0.5,1.0);
    cube();
    glPopMatrix();

    // SLOT
    glPushMatrix();
    glTranslatef(0,-0.2,2.2);
    glScalef(2.5,0.1,0.3);
    cube();
    glPopMatrix();

    // KEYBOARD TRAY (SLIDING)
    glPushMatrix();
    glTranslatef(0,-1.0,1.8 + traySlide);
    glScalef(2.5,0.12,0.9);
    cube();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,3,10, 0,0,0, 0,1,0);

    // LIGHT POSITION (IMPORTANT)
    GLfloat light_pos[] = {3.0f, 6.0f, 4.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glScalef(scaleValue,scaleValue,scaleValue);
    glRotatef(rotateX,1,0,0);
    glRotatef(rotateY,0,1,0);

    drawDesk();

    glutSwapBuffers();
}

void keyboard(unsigned char key,int,int)
{
    switch(key)
    {
        case 'w': rotateY+=5; break;
        case 'a': rotateX+=5; break;

        case 'o':
            traySlide+=0.1f;
            if(traySlide>1.0f) traySlide=1.0f;
            break;

        case 'c':
            traySlide-=0.1f;
            if(traySlide<0.0f) traySlide=0.0f;
            break;

        case 'l':
            lightOn=!lightOn;

            if(lightOn)
            {
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
            else
            {
                glDisable(GL_LIGHTING);
            }
            break;
    }
}

void special(int key,int,int)
{
    if(key==GLUT_KEY_UP) scaleValue+=0.1;
    if(key==GLUT_KEY_DOWN) scaleValue-=0.1;
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(16,timer,0);
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Realistic Wooden Desk");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0,timer,0);

    glutMainLoop();
}
