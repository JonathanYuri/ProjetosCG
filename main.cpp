#include <iostream>
#include <GL/glut.h>
#include <string>
#include "Camera.h"

using namespace std;

Camera* camera = new Camera();


struct tamanho {
    float x;
    float y;
    float z;
};

float proximidade_da_camera = 2.5;

tamanho tamanho_barra = { 0.01, 0.01, 0.05 };
tamanho tamanho_campo = { 1.2, 0.9, 0.1 }; // 2.4, 1.8, 0.1 fica melhor
tamanho tamanho_barraT = { tamanho_barra.x , 0.0732, tamanho_barra.x };

float raioBola = 0.01;

float posicoes_barras[] = { -0.6, 0.0366, 0,
                           -0.6, -0.0366, 0,
                           0.6, 0.0366, 0,
                           0.6, -0.0366, 0 };

float posicoes_barrasT[] = { -0.6, 0, 0,
                           0.6, 0, 0 };

int slices = 30;
int stacks = 30;

float velocidadeBola = 0.01;
float velocidadeRotacaoBola = 1000.0;

float positionInitialBallX = 0;
float positionInitialBallY = 0;
float positionInitialBallZ = 0.5;

float positionBallX = positionInitialBallX;
float positionBallY = positionInitialBallY;
float positionBallZ = positionInitialBallZ;

int pontuacaoA = 0;
int pontuacaoB = 0;

string placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);

void init(void) {
    /* selecionar cor de fundo (preto) */
    glClearColor(69.0 / 255.0, 39.0 / 255.0, .0 / 255.0, 1.0); // set background color to black
    //glClearColor(.0, .0, .0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}

void draw_bar(int indice)
{
    glPushMatrix();

    if (indice < 6) glTranslatef(posicoes_barras[indice] + (tamanho_barra.x / 2), posicoes_barras[indice + 1], proximidade_da_camera + posicoes_barras[indice + 2]);
    else            glTranslatef(posicoes_barras[indice] - (tamanho_barra.x / 2), posicoes_barras[indice + 1], proximidade_da_camera + posicoes_barras[indice + 2]);

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);
    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_barT(int indice)
{
    glPushMatrix();

    if (indice < 3) glTranslatef(posicoes_barrasT[indice] + (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], proximidade_da_camera + posicoes_barrasT[indice + 2]);
    else            glTranslatef(posicoes_barrasT[indice] - (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], proximidade_da_camera + posicoes_barrasT[indice + 2]);

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0) + (tamanho_barra.z / 2));
    glScalef(tamanho_barraT.x, tamanho_barraT.y, tamanho_barraT.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_bars()
{
    for (int i = 0; i < 11; i += 3)   draw_bar(i);
    for (int i = 0; i < 6; i += 3)    draw_barT(i);
}

void draw_grid()
{

}

void draw_field()
{
    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera);

    glScalef(tamanho_campo.x, tamanho_campo.y, tamanho_campo.z);
    glutWireCube(1.0);
    glPopMatrix();
}

void draw_ball()
{
    glPushMatrix();
    glTranslatef(positionBallX, positionBallY, proximidade_da_camera + raioBola + (tamanho_campo.z / 2));

    glPushMatrix();

    glRotatef(positionBallX * velocidadeRotacaoBola, 0, 1, 0);
    glRotatef(positionBallY * velocidadeRotacaoBola, 1, 0, 0);
    glutWireSphere(raioBola, slices, stacks);
    // testar rotacao: raioBola * 100.0

    glPopMatrix();

    glPopMatrix();
}

void draw_text()
{
    placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);
    glRasterPos3f(-0.08, 1, 0.5);

    for (char p : placar)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p);
    }
}

void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (camera->mode == '1')
    {
        gluLookAt(camera->position_atual.x, camera->position_atual.y, camera->position_atual.z,
                  camera->targetAtual.x, camera->targetAtual.y, camera->targetAtual.z,
                  0, 1, 0);
    }
    else if (camera->mode == '2')
    {
        gluLookAt(camera->targetAtual.x + .0, camera->targetAtual.y - 3.0, camera->targetAtual.z + 3.5,
                  camera->targetAtual.x, camera->targetAtual.y + 7.0, camera->targetAtual.z,
                  0, 1, 0);
    }

    /*glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
    glEnd();*/

    glColor3f(.0, 1.0, .0);
    draw_field();
    glColor3f(1.0, 1.0, 1.0);

    draw_bars();
    draw_ball();
    draw_grid();

    draw_text();

    glutSwapBuffers();
}

void reset_ball()
{
    positionBallX = positionInitialBallX;
    positionBallY = positionInitialBallY;
}

void verify_goal()
{
    bool rangeYTrave = (positionBallY <= posicoes_barras[1]) && (positionBallY >= posicoes_barras[4]);

    if (positionBallY >= 0.45 || positionBallY <= -0.45) // limites superior e inferior
    {
        reset_ball();
    }
    else if (positionBallX <= posicoes_barras[0])
    {
        if (rangeYTrave)    pontuacaoB++;

        reset_ball();
    }
    else if (positionBallX >= posicoes_barras[6])
    {
        if (rangeYTrave)    pontuacaoA++;

        reset_ball();
    }
}

void move_ball(unsigned char key)
{
    bool move = false;
    if (key == 'j' || key == 'J')   positionBallX -= velocidadeBola;    move = true;
    if (key == 'l' || key == 'L')   positionBallX += velocidadeBola;    move = true;

    if (key == 'k' || key == 'K')   positionBallY -= velocidadeBola;    move = true;
    if (key == 'i' || key == 'I')   positionBallY += velocidadeBola;    move = true;

    if (move)   verify_goal();
}

void keyboard_handler(unsigned char key, int x, int y)
{
    camera->rotate(key);

    camera->modify_mode(key);

    move_ball(key);

    glutPostRedisplay();
}

void specialKeys_handler(int key, int x, int y)
{
    camera->move(key);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Campo");
    init();

    glutDisplayFunc(displayFcn);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard_handler);
    glutSpecialFunc(specialKeys_handler);
    glutMainLoop();

    return 0;
}