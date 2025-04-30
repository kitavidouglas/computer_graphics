from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from PIL import Image
import math
import sys

PI = 3.1415926
bgIsGreen = False
fillIsTextured = False
woodTexture = None

def loadWoodTexture(file):
    global woodTexture
    image = Image.open(file)
    image = image.transpose(Image.FLIP_TOP_BOTTOM)
    img_data = image.convert("RGB").tobytes()
    width, height = image.size

    woodTexture = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, woodTexture)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, img_data)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

def init():
    glEnable(GL_TEXTURE_2D)
    loadWoodTexture("wood.jpg")

def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-10, 10, -10, 10, -1, 1)
    glMatrixMode(GL_MODELVIEW)

def drawGrid():
    glLineWidth(1)
    glColor3f(0.8, 0.8, 0.8)
    glBegin(GL_LINES)
    for i in range(-10, 11):
        glVertex2f(i, -10)
        glVertex2f(i, 10)
        glVertex2f(-10, i)
        glVertex2f(10, i)
    glEnd()

    glLineWidth(2)
    glColor3f(1, 1, 1)
    glBegin(GL_LINES)
    glVertex2f(0, -10)
    glVertex2f(0, 10)
    glVertex2f(-10, 0)
    glVertex2f(10, 0)
    glEnd()

def drawSolidCircle(cx, cy, r):
    glDisable(GL_TEXTURE_2D)
    glColor3f(1, 1, 1)
    glBegin(GL_TRIANGLE_FAN)
    glVertex2f(cx, cy)
    for a in range(361):
        rad = a * PI / 180.0
        glVertex2f(cx + r * math.cos(rad), cy + r * math.sin(rad))
    glEnd()

def drawTexturedCircle(cx, cy, r):
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, woodTexture)
    glBegin(GL_TRIANGLE_FAN)
    glTexCoord2f(0.5, 0.5)
    glVertex2f(cx, cy)
    for a in range(361):
        rad = a * PI / 180.0
        x = cx + r * math.cos(rad)
        y = cy + r * math.sin(rad)
        u = (math.cos(rad) + 1) * 0.5
        v = (math.sin(rad) + 1) * 0.5
        glTexCoord2f(u, v)
        glVertex2f(x, y)
    glEnd()

def drawText(text, x, y):
    glDisable(GL_TEXTURE_2D)
    glColor3f(1, 1, 1)
    glRasterPos2f(x, y)
    for ch in text:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(ch))

def display():
    global bgIsGreen, fillIsTextured
    if bgIsGreen:
        glClearColor(0, 1, 0, 1)
    else:
        glClearColor(0, 0, 0.5, 1)

    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    drawGrid()

    if fillIsTextured:
        drawTexturedCircle(-3.0, 1.0, 4.0)
    else:
        drawSolidCircle(-3.0, 1.0, 4.0)

    drawText("G: Toggle BG (Blue/Green)", -9.5, 9.0)
    drawText("T: Toggle Fill (White/Wood)", -9.5, 8.0)
    drawText("Circle @ (-3,1), r=4cm", -9.5, 7.0)

    glFlush()

def keyboard(key, x, y):
    global bgIsGreen, fillIsTextured
    key = key.decode('utf-8')
    if key in ('g', 'G'):
        bgIsGreen = not bgIsGreen
    elif key in ('t', 'T'):
        fillIsTextured = not fillIsTextured
    elif ord(key) == 27:  # ESC key
        sys.exit()
    glutPostRedisplay()

def main():
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(800, 600)
    glutCreateWindow(b"Circle Demo with Grid & UI")
    init()
    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)
    glutMainLoop()

if __name__ == "__main__":
    main()
