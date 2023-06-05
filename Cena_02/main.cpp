#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>

void lighting(){

    float lightPosition[4] = {3.0f, 3.0f, 2.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void bule(){
    //definindo reflexões
    float kd[4] = {0.5f, 0.4f, 0.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.0f, 1.0f};
    float ns = 80.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //desenha objeto
    glutSolidTeapot(0.6);
}

void init(){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    lighting();
}

void display(){

    //Rotação é feita a partir do tempo de execução do algoritmo (a cada segundo o objeto gira)
    const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    const double beta = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // XY - definindo viewport, seu tipo de projeção e posição da camera que irá capturar plano XY
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 800/2, 800/2, 800/2);
    gluLookAt(0.0, 0.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glPushMatrix();
        glRotatef(beta, 0.0f, 1.0f, 0.0f);
        bule();
    glPopMatrix();


    // YZ - definindo viewport, seu tipo de projeção e posição da camera que irá capturar plano YZ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(800/2, 800/2, 800/2, 800/2);
    gluLookAt(1.0, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPushMatrix();
        glRotatef(beta, 0.0f, 1.0f, 0.0f);
        bule();
    glPopMatrix();


    // XZ - definindo viewport, seu tipo de projeção e posição da camera que irá capturar plano XZ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, 800/2, 800/2);
    gluLookAt(0.0, 1.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, -1.0);
    glPushMatrix();
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
        bule();
    glPopMatrix();

    //Perspectiva - definindo viewport, seu tipo de projeção e posição da camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(800/2, 0, 800/2, 800/2);
    glLoadIdentity();
    gluLookAt(2.3, 2.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPushMatrix();
        glRotatef(beta, 0.0f, 1.0f, 0.0f);
        bule();
    glPopMatrix();

    glutSwapBuffers();
    //glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CENA 02");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
