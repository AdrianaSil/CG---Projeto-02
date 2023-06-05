#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <windows.h>

void lighting(){

    float lightPosition[4] = {0.0f, 10.0f, -5.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //posição da fonte de luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);          //define cor ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);          //define cor difusa da luz
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);         //define cor especular da luz

    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void bule(){
    //definindo reflexões
    float kd[4] = {0.2f, 0.6f, 1.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 70.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //desenha o bule
    glPushMatrix();
        glTranslatef(1.0, 0.8, 1.9);
        glRotatef(60.0,0.0,1.0,0.0);
        glutSolidTeapot(0.25);
    glPopMatrix();

}

void toro(){
    //definindo reflexões
    float kd[4] = {0.2f, 1.0f, 0.2f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 100.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //desenha o toro
    glPushMatrix();
        glTranslatef(1.7, 0.8, 1.7);
        glRotatef(90.0,1.0,0.0,0.0);
        glutSolidTorus(0.06, 0.2, 40, 40);
    glPopMatrix();
}

void bola(){
    //definindo reflexões
    float ka[4] = {2.5f, 1.5f, 0.0f, 1.0f};
    float kd[4] = {1.0f, 0.5f, 0.0f, 1.0f};
    float ks[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float ns = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //desenha a esfera
    glPushMatrix();
        glTranslatef(1.1, 0.8, 1.1);
        glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
}

void cenario(float espessura, int op){
    //definindo reflexões
    float kd[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float ks[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float ns = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //desenha cenário (chão e parede)
    if(op == 1){    //Chão - centraliza e escala no comprimento, largura e espessura correspondente
        glPushMatrix();
            glTranslatef(1.0, espessura, 1.0);
            glScalef(2.0, espessura, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
    }
    else{   //Paredes - centraliza e escala no comprimento, largura e espessura correspondente
         glPushMatrix();
            glTranslatef(1.0, 0.0, 0.5);
            glScalef(2.0, espessura, 0.8);
            glutSolidCube(1.0);
        glPopMatrix();
    }

}

void init(){
    glClearColor(0.5, 0.5, 0.5, 1.0);

    glEnable(GL_DEPTH_TEST);
    /*
    //habilita remoção de faces ocultas
    //obs: renderiza a parte interna do bule que está iluminado, o restante dos objetos ficam normais.

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0,1.6,2.5,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, 1.0, 0.1, 100.0);

    lighting();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    //Chão
    cenario(0.1, 1);
    //Paredes
    glPushMatrix();
        glRotatef(-90.0,1.0,0.0,0.0);
        cenario(0.1, 0);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-90.0,1.0,0.0,0.0);
        glRotatef(270.0,0.0,0.0,1.0);
        cenario(0.1, 0);
    glPopMatrix();

    //Objetos
    bule();
    toro();
    bola();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CENA 01");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}



