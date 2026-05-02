#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>

float rotationY = 0.0f;
float zoom = -10.0f;

void drawCube(float x, float y, float z, float sx, float sy, float sz)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

void setMaterial(float r, float g, float b, float shininess = 25.0f)
{
    GLfloat ambient[]  = { r * 0.25f, g * 0.25f, b * 0.25f, 1.0f };
    GLfloat diffuse[]  = { r * 0.75f, g * 0.75f, b * 0.75f, 1.0f };
    GLfloat specular[] = { 0.12f, 0.12f, 0.12f, 1.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void drawWindow(float x, float y, float z)
{
    setMaterial(0.45f, 0.78f, 0.90f, 70.0f);
    drawCube(x, y, z, 0.28f, 0.36f, 0.05f);
}

void drawWhiteBuilding()
{
    glPushMatrix();
    glTranslatef(1.45f, 0.0f, 0.0f);

    setMaterial(0.78f, 0.72f, 0.70f, 18.0f);
    drawCube(0.0f, 1.75f, 0.0f, 2.0f, 3.5f, 1.35f);

    setMaterial(0.88f, 0.84f, 0.82f, 18.0f);
    drawCube(-0.04f, 1.75f, -0.70f, 1.95f, 3.5f, 0.08f);

    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            float x = -0.63f + col * 0.42f;
            float y = 0.35f + row * 0.50f;

            setMaterial(0.30f, 0.22f, 0.22f, 10.0f);
            drawCube(x, y, -0.755f, 0.34f, 0.42f, 0.04f);

            drawWindow(x, y, -0.79f);
        }
    }

    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            float z = -0.35f + col * 0.45f;
            float y = 0.35f + row * 0.50f;

            glPushMatrix();
            glTranslatef(1.03f, y, z);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

            setMaterial(0.30f, 0.22f, 0.22f, 10.0f);
            drawCube(0.0f, 0.0f, -0.03f, 0.34f, 0.42f, 0.04f);

            setMaterial(0.42f, 0.73f, 0.86f, 70.0f);
            drawCube(0.0f, 0.0f, -0.06f, 0.28f, 0.36f, 0.05f);

            glPopMatrix();
        }
    }

    glPopMatrix();
}

void drawBlueBuilding()
{
    glPushMatrix();
    glTranslatef(-1.35f, 0.0f, 0.15f);

    setMaterial(0.16f, 0.38f, 0.58f, 20.0f);
    drawCube(0.0f, 2.25f, 0.0f, 1.8f, 4.5f, 1.35f);

    setMaterial(0.20f, 0.50f, 0.72f, 25.0f);
    drawCube(-0.45f, 2.25f, -0.70f, 0.45f, 4.5f, 0.08f);
    drawCube(0.35f, 2.25f, -0.70f, 0.45f, 4.5f, 0.08f);

    setMaterial(0.55f, 0.82f, 0.92f, 45.0f);
    drawCube(-0.88f, 2.25f, -0.78f, 0.16f, 4.7f, 0.18f);
    drawCube(0.62f, 2.25f, -0.78f, 0.16f, 4.7f, 0.18f);

    setMaterial(0.38f, 0.72f, 0.88f, 30.0f);
    for (int i = 0; i < 8; i++)
    {
        float y = 0.45f + i * 0.52f;
        drawCube(-0.13f, y, -0.84f, 1.35f, 0.08f, 0.22f);
    }

    setMaterial(0.11f, 0.30f, 0.48f, 15.0f);
    for (int i = 0; i < 7; i++)
    {
        float y = 0.65f + i * 0.55f;
        drawCube(0.0f, y, 0.70f, 1.75f, 0.035f, 0.04f);
    }

    glPopMatrix();
}

void drawGround()
{
    setMaterial(0.20f, 0.20f, 0.18f, 8.0f);
    drawCube(0.0f, -0.08f, -0.2f, 8.8f, 0.08f, 5.6f);
}

void drawRoad()
{
    setMaterial(0.05f, 0.05f, 0.05f, 8.0f);
    drawCube(0.0f, -0.04f, -2.35f, 8.5f, 0.06f, 1.35f);

    setMaterial(0.90f, 0.82f, 0.25f, 5.0f);
    for (int i = -3; i <= 3; i++)
        drawCube(i * 1.2f, 0.005f, -2.35f, 0.55f, 0.025f, 0.06f);

    setMaterial(0.45f, 0.45f, 0.43f, 10.0f);
    drawCube(0.0f, 0.0f, -1.55f, 8.5f, 0.08f, 0.18f);
    drawCube(0.0f, 0.0f, -3.15f, 8.5f, 0.08f, 0.18f);
}

void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat globalAmbient[] = { 0.18f, 0.18f, 0.18f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat light0Position[] = { -4.0f, 7.0f, 6.0f, 1.0f };
    GLfloat light0Diffuse[]  = { 0.75f, 0.75f, 0.75f, 1.0f };
    GLfloat light0Specular[] = { 0.25f, 0.25f, 0.25f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);

    GLfloat light1Position[] = { 5.0f, 4.0f, -4.0f, 1.0f };
    GLfloat light1Diffuse[]  = { 0.25f, 0.35f, 0.45f, 1.0f };

    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 2.4, 8.5,
              0.0, 2.0, 0.0,
              0.0, 1.0, 0.0);

    glTranslatef(0.0f, 0.0f, zoom + 10.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    drawGround();
    drawRoad();
    drawBlueBuilding();
    drawWhiteBuilding();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    float aspectRatio = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'a':
        case 'A':
            rotationY -= 5.0f;
            break;

        case 'd':
        case 'D':
            rotationY += 5.0f;
            break;

        case 'w':
        case 'W':
            zoom += 0.3f;
            break;

        case 's':
        case 'S':
            zoom -= 0.3f;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(0.02f, 0.02f, 0.025f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    setupLighting();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("3D Modern Building Design");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
