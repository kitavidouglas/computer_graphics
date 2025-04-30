#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <iostream>

// Globals ===
const float PI = 3.1415926f;
bool bgIsGreen      = false; // false=blue, true=green
bool fillIsTextured = false; // false=white, true=wood texture
GLuint woodTexture;          // texture ID

//oad Texture ===
void loadWoodTexture(const char* file) {
    woodTexture = SOIL_load_OGL_texture(
        file,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (!woodTexture) {
        std::cerr << "Failed to load " << file
                  << ": " << SOIL_last_result() << "\n";
        exit(1);
    }
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// === Initialization ===
void init() {
    glEnable(GL_TEXTURE_2D);
    loadWoodTexture("wood.jpg");  // make sure wood.jpg is in the same folder
}

// === Window Resize / Projection ===
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // world coords from -10..+10 in X and Y
    glOrtho(-10, 10, -10, 10, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// === Draw Grid & Axes ===
void drawGrid() {
    // Light‑gray grid lines
    glLineWidth(1);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
      for (int i = -10; i <= 10; ++i) {
        // vertical
        glVertex2f(i, -10); glVertex2f(i, 10);
        // horizontal
        glVertex2f(-10, i); glVertex2f(10, i);
      }
    glEnd();

    // White axes
    glLineWidth(2);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
      // Y axis
      glVertex2f(0, -10); glVertex2f(0, 10);
      // X axis
      glVertex2f(-10, 0); glVertex2f(10, 0);
    glEnd();
}

// === Draw Solid (white) Circle ===
void drawSolidCircle(float cx, float cy, float r) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glBegin(GL_TRIANGLE_FAN);
      glVertex2f(cx, cy);
      for (int a = 0; a <= 360; ++a) {
        float rad = a * PI / 180.0f;
        glVertex2f(cx + r * cos(rad), cy + r * sin(rad));
      }
    glEnd();
}

// === Draw Textured Circle ===
void drawTexturedCircle(float cx, float cy, float r) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glBegin(GL_TRIANGLE_FAN);
      // center
      glTexCoord2f(0.5f, 0.5f);
      glVertex2f(cx, cy);
      // rim
      for (int a = 0; a <= 360; ++a) {
        float rad = a * PI / 180.0f;
        float x = cx + r * cos(rad), y = cy + r * sin(rad);
        float u = (cos(rad) + 1.0f) * 0.5f;
        float v = (sin(rad) + 1.0f) * 0.5f;
        glTexCoord2f(u, v);
        glVertex2f(x, y);
      }
    glEnd();
}

// === On‑screen Text ===
void drawText(const char* s, float x, float y) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    for (const char* c = s; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

// === Display Callback ===
void display() {
    // 1) background color
    if (bgIsGreen) glClearColor(0,1,0,1);
    else           glClearColor(0,0,0.5f,1); // dark blue

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // 2) grid + axes
    drawGrid();

    // 3) circle at (-3,1), radius=4 cm → 4 units
    if (fillIsTextured)
        drawTexturedCircle(-3.0f, 1.0f, 4.0f);
    else
        drawSolidCircle(     -3.0f, 1.0f, 4.0f);

    // 4) UI text
    drawText("G: Toggle BG (Blue/Green)", -9.5f,  9.0f);
    drawText("T: Toggle Fill (White/Wood)", -9.5f,  8.0f);
    drawText("Circle @ (-3,1), r=4cm",      -9.5f,  7.0f);

    glFlush();
}

// === Keyboard Callback ===
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
      case 'g': case 'G':
        bgIsGreen = !bgIsGreen;
        break;
      case 't': case 'T':
        fillIsTextured = !fillIsTextured;
        break;
      case 27: // ESC
        exit(0);
    }
    glutPostRedisplay();
}

// === Main ===
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Circle Demo with Grid & UI");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
