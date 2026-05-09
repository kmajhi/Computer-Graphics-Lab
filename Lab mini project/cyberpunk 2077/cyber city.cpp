#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int RAIN_COUNT = 650;

float camX = 0.0f, camY = 6.0f, camZ = 18.0f;
float sceneRot = 0.0f;
float carMove = 0.0f;
float droneMove = 0.0f;

bool rainOn = true;
bool fogOn = true;
bool neonOn = true;
bool isDay = false;

struct Rain {
    float x, y, z;
    float speed;
};

Rain rain[RAIN_COUNT];

void setMaterial(float r, float g, float b, float shine) {
    GLfloat ambient[]  = { r * 0.45f, g * 0.45f, b * 0.45f, 1.0f };
    GLfloat diffuse[]  = { r, g, b, 1.0f };
    GLfloat specular[] = { 0.85f, 0.85f, 0.85f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void cube(float x, float y, float z, float sx, float sy, float sz) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glutSolidCube(1);
    glPopMatrix();
}

void initRain() {
    srand((unsigned)time(0));

    for (int i = 0; i < RAIN_COUNT; i++) {
        rain[i].x = (rand() % 360 - 180) / 10.0f;
        rain[i].y = (rand() % 180) / 10.0f + 2.0f;
        rain[i].z = (rand() % 360 - 180) / 10.0f;
        rain[i].speed = 0.18f + (rand() % 20) / 100.0f;
    }
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);

    if (isDay) {
        GLfloat globalAmbient[] = { 0.65f, 0.65f, 0.62f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        GLfloat sunPos[]      = { -6.0f, 14.0f, 8.0f, 1.0f };
        GLfloat sunAmbient[]  = { 0.55f, 0.52f, 0.45f, 1.0f };
        GLfloat sunDiffuse[]  = { 1.00f, 0.92f, 0.72f, 1.0f };
        GLfloat sunSpecular[] = { 1.00f, 0.95f, 0.80f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);

        GLfloat weakLight[] = { 0.04f, 0.04f, 0.04f, 1.0f };
        glLightfv(GL_LIGHT1, GL_DIFFUSE, weakLight);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, weakLight);
    }
    else {
        GLfloat globalAmbient[] = { 0.32f, 0.32f, 0.36f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        GLfloat moonPos[]      = { 0.0f, 14.0f, 8.0f, 1.0f };
        GLfloat moonAmbient[]  = { 0.14f, 0.16f, 0.24f, 1.0f };
        GLfloat moonDiffuse[]  = { 0.42f, 0.52f, 0.82f, 1.0f };
        GLfloat moonSpecular[] = { 0.80f, 0.90f, 1.00f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, moonPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, moonAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, moonDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, moonSpecular);

        GLfloat cyanPos[]     = { -5.0f, 4.0f, 0.0f, 1.0f };
        GLfloat cyanAmbient[] = { 0.00f, 0.14f, 0.16f, 1.0f };
        GLfloat cyanDiffuse[] = { 0.00f, 1.00f, 1.00f, 1.0f };

        glLightfv(GL_LIGHT1, GL_POSITION, cyanPos);
        glLightfv(GL_LIGHT1, GL_AMBIENT, cyanAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, cyanDiffuse);

        GLfloat pinkPos[]     = { 5.0f, 4.0f, 0.0f, 1.0f };
        GLfloat pinkAmbient[] = { 0.16f, 0.00f, 0.14f, 1.0f };
        GLfloat pinkDiffuse[] = { 1.00f, 0.00f, 0.80f, 1.0f };

        glLightfv(GL_LIGHT2, GL_POSITION, pinkPos);
        glLightfv(GL_LIGHT2, GL_AMBIENT, pinkAmbient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, pinkDiffuse);
    }
}

void drawSky() {
    glDisable(GL_LIGHTING);

    if (isDay) {
        glClearColor(0.52f, 0.75f, 0.95f, 1.0f);

        glColor3f(1.0f, 0.86f, 0.35f);
        glPushMatrix();
        glTranslatef(-7.0f, 10.0f, -15.0f);
        glutSolidSphere(0.85f, 32, 32);
        glPopMatrix();
    }
    else {
        glClearColor(0.05f, 0.06f, 0.11f, 1.0f);

        glColor3f(0.80f, 0.88f, 1.0f);
        glPushMatrix();
        glTranslatef(7.0f, 10.0f, -15.0f);
        glutSolidSphere(0.75f, 32, 32);
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
}

void drawBuildingClock(float x, float y, float z) {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    int hour = localTime->tm_hour % 12;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    float secondAngle = -second * 6.0f;
    float minuteAngle = -(minute * 6.0f + second * 0.1f);
    float hourAngle = -(hour * 30.0f + minute * 0.5f);

    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(0.95f, 0.88f, 0.65f);
    glutSolidTorus(0.03, 0.45, 24, 60);

    glColor3f(0.08f, 0.08f, 0.09f);
    glutSolidSphere(0.42, 40, 40);

    glColor3f(1.0f, 0.90f, 0.55f);

    for (int i = 0; i < 12; i++) {
        float angle = i * 30.0f * 3.1416f / 180.0f;
        float px = sin(angle) * 0.34f;
        float py = cos(angle) * 0.34f;

        glPushMatrix();
        glTranslatef(px, py, 0.04f);
        glScalef(0.035f, 0.08f, 0.02f);
        glutSolidCube(1);
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(hourAngle, 0, 0, 1);
    glColor3f(1.0f, 0.85f, 0.25f);
    glTranslatef(0, 0.12f, 0.06f);
    glScalef(0.04f, 0.25f, 0.02f);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(minuteAngle, 0, 0, 1);
    glColor3f(0.95f, 0.95f, 0.95f);
    glTranslatef(0, 0.17f, 0.07f);
    glScalef(0.03f, 0.34f, 0.02f);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(secondAngle, 0, 0, 1);
    glColor3f(1.0f, 0.10f, 0.10f);
    glTranslatef(0, 0.19f, 0.08f);
    glScalef(0.015f, 0.38f, 0.015f);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(1.0f, 0.85f, 0.25f);
    glutSolidSphere(0.055, 20, 20);

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawGround() {
    if (isDay)
        setMaterial(0.22f, 0.24f, 0.25f, 90);
    else
        setMaterial(0.08f, 0.08f, 0.10f, 180);

    cube(0, -0.12f, 0, 40.0f, 0.2f, 40.0f);

    if (!isDay) {
        glDisable(GL_LIGHTING);

        glColor4f(0.0f, 1.0f, 1.0f, 0.12f);
        cube(-10.0f, -0.01f, 0, 0.3f, 0.01f, 40.0f);

        glColor4f(1.0f, 0.0f, 0.8f, 0.12f);
        cube(10.0f, -0.01f, 0, 0.3f, 0.01f, 40.0f);

        glEnable(GL_LIGHTING);
    }
}

void drawRoad() {
    if (isDay)
        setMaterial(0.04f, 0.04f, 0.045f, 100);
    else
        setMaterial(0.06f, 0.06f, 0.08f, 220);

    cube(0, 0.02f, 0, 5.2f, 0.04f, 34.0f);

    glDisable(GL_LIGHTING);

    if (neonOn && !isDay) {
        glColor4f(0.0f, 1.0f, 1.0f, 0.9f);
        cube(-2.75f, 0.08f, 0, 0.08f, 0.04f, 34.0f);

        glColor4f(1.0f, 0.0f, 0.9f, 0.9f);
        cube(2.75f, 0.08f, 0, 0.08f, 0.04f, 34.0f);
    }

    glColor3f(0.95f, 0.95f, 1.0f);
    for (float z = -15; z <= 15; z += 3.0f) {
        cube(0, 0.09f, z, 0.18f, 0.035f, 1.2f);
    }

    glEnable(GL_LIGHTING);
}

void drawSidewalks() {
    if (isDay)
        setMaterial(0.38f, 0.38f, 0.40f, 70);
    else
        setMaterial(0.13f, 0.13f, 0.16f, 90);

    cube(-4.3f, 0.07f, 0, 2.2f, 0.12f, 34.0f);
    cube(4.3f, 0.07f, 0, 2.2f, 0.12f, 34.0f);
}

void drawBuilding(float x, float z, float w, float h, float d, int style) {
    if (isDay) {
        if (style == 0)
            setMaterial(0.42f, 0.48f, 0.55f, 80);
        else if (style == 1)
            setMaterial(0.48f, 0.38f, 0.52f, 80);
        else
            setMaterial(0.38f, 0.50f, 0.50f, 80);
    }
    else {
        if (style == 0)
            setMaterial(0.12f, 0.16f, 0.24f, 170);
        else if (style == 1)
            setMaterial(0.18f, 0.10f, 0.22f, 170);
        else
            setMaterial(0.10f, 0.18f, 0.18f, 170);
    }

    cube(x, h / 2.0f, z, w, h, d);

    glDisable(GL_LIGHTING);

    if (neonOn || isDay) {
        if (isDay)
            glColor3f(0.75f, 0.85f, 0.95f);
        else {
            float nr = style == 0 ? 0.0f : 1.0f;
            float ng = style == 2 ? 1.0f : 0.0f;
            float nb = style == 1 ? 1.0f : 0.9f;
            glColor3f(nr, ng, nb);
        }

        for (float y = 1.0f; y < h - 0.5f; y += 1.1f) {
            for (float xx = -w / 2.0f + 0.35f; xx < w / 2.0f - 0.2f; xx += 0.6f) {
                cube(x + xx, y, z + d / 2.0f + 0.025f, 0.22f, 0.28f, 0.03f);
            }
        }

        if (!isDay) {
            glColor3f(0.0f, 1.0f, 1.0f);
            cube(x, h + 0.15f, z, w * 0.95f, 0.08f, d * 0.95f);
        }
    }

    glEnable(GL_LIGHTING);
}

void drawBuildings() {
    drawBuilding(-7.3f, -12, 2.0f, 7.0f, 2.0f, 0);
    drawBuilding( 7.3f, -12, 2.0f, 8.5f, 2.0f, 1);

    drawBuilding(-7.2f, -7, 2.3f, 9.0f, 2.0f, 2);
    drawBuilding( 7.2f, -7, 2.3f, 6.8f, 2.0f, 0);

    drawBuilding(-7.1f, -2, 2.0f, 5.8f, 2.0f, 1);
    drawBuilding( 7.1f, -2, 2.0f, 10.0f, 2.0f, 2);

    drawBuilding(-7.4f, 4, 2.4f, 8.2f, 2.0f, 0);
    drawBuilding( 7.4f, 4, 2.4f, 7.4f, 2.0f, 1);

    drawBuilding(-7.0f, 10, 2.0f, 6.5f, 2.0f, 2);
    drawBuilding( 7.0f, 10, 2.0f, 9.0f, 2.0f, 0);

    drawBuildingClock(7.1f, 8.2f, -0.96f);
}

void drawBillboard(float x, float y, float z, float r, float g, float b) {
    glDisable(GL_LIGHTING);

    if (isDay)
        glColor3f(0.65f, 0.65f, 0.68f);
    else if (neonOn)
        glColor3f(r, g, b);
    else
        glColor3f(0.30f, 0.30f, 0.35f);

    cube(x, y, z, 1.5f, 0.75f, 0.06f);

    glColor3f(0.08f, 0.08f, 0.10f);
    cube(x, y - 0.55f, z, 0.12f, 0.8f, 0.08f);

    glEnable(GL_LIGHTING);
}

void drawBillboards() {
    drawBillboard(-5.9f, 3.7f, -5.8f, 1.0f, 0.0f, 0.8f);
    drawBillboard( 5.9f, 4.0f, -1.2f, 0.0f, 1.0f, 1.0f);
    drawBillboard(-5.9f, 4.4f,  6.0f, 0.8f, 0.2f, 1.0f);
}

void drawCar(float x, float z, float r, float g, float b) {
    setMaterial(r, g, b, 120);
    cube(x, 0.35f, z, 1.1f, 0.35f, 1.7f);

    setMaterial(0.08f, 0.10f, 0.14f, 180);
    cube(x, 0.68f, z - 0.05f, 0.75f, 0.35f, 0.8f);

    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 0.10f, 0.10f);
    cube(x, 0.42f, z + 0.88f, 0.75f, 0.08f, 0.05f);

    if (isDay)
        glColor3f(0.95f, 0.95f, 0.75f);
    else
        glColor3f(0.0f, 1.0f, 1.0f);

    cube(x, 0.42f, z - 0.88f, 0.75f, 0.08f, 0.05f);

    glEnable(GL_LIGHTING);
}

void drawCars() {
    drawCar(-1.2f, -16.0f + carMove, 0.90f, 0.08f, 0.14f);
    drawCar( 1.2f,  16.0f - carMove, 0.08f, 0.26f, 0.90f);
    drawCar(-1.2f, -5.0f + carMove, 0.90f, 0.85f, 0.08f);
}

void drawStreetLight(float x, float z) {
    setMaterial(0.16f, 0.16f, 0.18f, 90);
    cube(x, 1.0f, z, 0.08f, 2.0f, 0.08f);

    glDisable(GL_LIGHTING);

    if (isDay)
        glColor3f(0.42f, 0.42f, 0.42f);
    else if (neonOn)
        glColor3f(0.0f, 1.0f, 1.0f);
    else
        glColor3f(0.55f, 0.55f, 0.55f);

    cube(x, 2.05f, z, 0.35f, 0.12f, 0.35f);

    glEnable(GL_LIGHTING);
}

void drawStreetLights() {
    for (float z = -14; z <= 14; z += 4.0f) {
        drawStreetLight(-3.1f, z);
        drawStreetLight(3.1f, z);
    }
}

void drawDrone() {
    float x = sin(droneMove) * 4.0f;
    float z = cos(droneMove) * 5.0f;

    setMaterial(0.18f, 0.18f, 0.22f, 140);
    cube(x, 6.5f, z, 0.7f, 0.18f, 0.45f);

    glDisable(GL_LIGHTING);

    if (isDay)
        glColor3f(0.20f, 0.20f, 0.22f);
    else
        glColor3f(1.0f, 0.0f, 0.8f);

    cube(x - 0.45f, 6.55f, z, 0.12f, 0.08f, 0.12f);

    if (isDay)
        glColor3f(0.35f, 0.35f, 0.38f);
    else
        glColor3f(0.0f, 1.0f, 1.0f);

    cube(x + 0.45f, 6.55f, z, 0.12f, 0.08f, 0.12f);

    glEnable(GL_LIGHTING);
}

void drawRain() {
    if (!rainOn) return;

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);

    if (isDay)
        glColor4f(0.60f, 0.70f, 0.80f, 0.35f);
    else
        glColor4f(0.78f, 0.90f, 1.0f, 0.50f);

    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for (int i = 0; i < RAIN_COUNT; i++) {
        glVertex3f(rain[i].x, rain[i].y, rain[i].z);
        glVertex3f(rain[i].x - 0.08f, rain[i].y - 0.45f, rain[i].z);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void update(int value) {
    if (rainOn) {
        for (int i = 0; i < RAIN_COUNT; i++) {
            rain[i].y -= rain[i].speed;
            rain[i].x -= 0.025f;

            if (rain[i].y < 0.2f) {
                rain[i].y = 16.0f;
                rain[i].x = (rand() % 360 - 180) / 10.0f;
                rain[i].z = (rand() % 360 - 180) / 10.0f;
            }
        }
    }

    carMove += 0.13f;
    if (carMove > 32.0f) carMove = 0.0f;

    droneMove += 0.025f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ, 0, 2.5f, 0, 0, 1, 0);

    setupLighting();
    drawSky();

    glPushMatrix();
    glRotatef(sceneRot, 0, 1, 0);

    drawGround();
    drawRoad();
    drawSidewalks();
    drawBuildings();
    drawBillboards();
    drawStreetLights();
    drawCars();
    drawDrone();
    drawRain();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (float)w / h, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            sceneRot -= 4;
            break;

        case 'd':
        case 'D':
            sceneRot += 4;
            break;

        case 'w':
        case 'W':
            camZ -= 0.6f;
            break;

        case 's':
        case 'S':
            camZ += 0.6f;
            break;

        case 'q':
        case 'Q':
            camY += 0.4f;
            break;

        case 'e':
        case 'E':
            camY -= 0.4f;
            break;

        case 'r':
        case 'R':
            rainOn = !rainOn;
            break;

        case 'n':
        case 'N':
            neonOn = !neonOn;
            break;

        case 't':
        case 'T':
            isDay = !isDay;

            if (isDay) {
                glDisable(GL_FOG);
                fogOn = false;
            } else {
                glEnable(GL_FOG);
                fogOn = true;
            }
            break;

        case 'f':
        case 'F':
            fogOn = !fogOn;
            if (fogOn) glEnable(GL_FOG);
            else glDisable(GL_FOG);
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  camX -= 0.4f;
    if (key == GLUT_KEY_RIGHT) camX += 0.4f;
    if (key == GLUT_KEY_UP)    camZ -= 0.4f;
    if (key == GLUT_KEY_DOWN)  camZ += 0.4f;

    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glEnable(GL_FOG);

    GLfloat fogColor[] = { 0.05f, 0.06f, 0.11f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 14.0f);
    glFogf(GL_FOG_END, 38.0f);

    initRain();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200, 760);

    glutCreateWindow("Cyberpunk Neon Rainy City - Clock Building");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
