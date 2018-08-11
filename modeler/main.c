#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

int cx, cy, cz;
int cn;

struct Quads {
    int x1, y1, z1;
    int x2, y2, z2;
    int x3, y3, z3;
    int x4, y4, z4;
    float r, g, b;
    int state;
    int total;
};

struct Quads q[100];

void add_quad()
{
    int st;
    q[0].state++;
    if (q[0].state > 4) { q[0].state = 1; }
    st = q[0].state;

    if (st == 1) { q[0].total++; cn = q[0].total; }
    if (st == 1) { q[cn].x1 = cx; q[cn].y1 = cy; q[cn].z1 = cz; }
    if (st == 1 || st == 2) { q[cn].x2 = cx; q[cn].y2 = cy; q[cn].z2 = cz; }
    if (st == 1 || st == 2 || st == 3) { q[cn].x3 = cx; q[cn].y3 = cy; q[cn].z3 = cz; }
    if (st == 1 || st == 2 || st == 3 || st == 4) { q[cn].x4 = cx; q[cn].y4 = cy; q[cn].z4 = cz; }
}

void draw_quads()
{
    int i;
    for (i = 1; i < q[0].total+1; i++) {
        glBegin(GL_QUADS);
        glColor3f(q[i].r, q[i].g, q[i].b);
        glVertex3f(q[i].x1, q[i].y1, q[i].z1);
        glVertex3f(q[i].x2, q[i].y2, q[i].z2);
        glVertex3f(q[i].x3, q[i].y3, q[i].z3);
        glVertex3f(q[i].x4, q[i].y4, q[i].z4);
        glEnd();
    }
}

void cube()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(cx, cy, cz);
    glutSolidCube(0.4);
    glPopMatrix();
}

void draw_grid()
{
    int i;
    for (i = 0; i < 40; i++) {
        glPushMatrix();
        if (i < 20) { glTranslatef(0, 0, i); }
        if (i >= 20) { glTranslatef(i-20, 0, 0); glRotatef(-90, 0, 1, 0); }

        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glLineWidth(1);
        glVertex3f(0, -0.1, 0);
        glVertex3f(19, -0.1, 0);
        glEnd();
        glPopMatrix();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-13, 0, -45);
    glRotatef(40, 1, 1, 0);
    draw_grid();
    draw_quads();
    cube();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35, 1.0f, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2, 0.2, 0.2, 1);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'w') { cz -= 1; } else if (key == 's') { cz += 1; }
    if (key == 'a') { cx -= 1; } else if (key == 'd') { cx += 1; }
    if (key == 'q') { cy += 1; } else if (key == 'z') { cy -= 1; }
    if (key == 32) { add_quad(); }

    if (key == 'r') { q[cn].r = 1; q[cn].g = 0; q[cn].b = 0; }
    if (key == 'g') { q[cn].r = 0; q[cn].g = 1; q[cn].b = 0; }
    if (key == 'b') { q[cn].r = 0; q[cn].g = 0; q[cn].b = 1; }
    if (key == 'y') { q[cn].r = 1; q[cn].g = 1; q[cn].b = 0; }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple Modeler v0.1");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;
}
