#include <iostream>
#include <string>
#include "Camera.h"
#include "Bola.h"

using namespace std;

Camera* camera = new Camera();
Bola* bola = new Bola();

struct tamanho {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

GLfloat proximidade_da_camera = 2.5f;

tamanho tamanho_barra = { 0.01f, 0.01f, 0.05f };

tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };
// tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };

GLfloat posicoes_barras[] = { -(tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           -(tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f };

tamanho tamanho_barraT = { tamanho_barra.x , 0.0732f * (tamanho_campo.y / 0.9f), tamanho_barra.x };

GLfloat posicoes_barrasT[] = { -(tamanho_campo.x / 2), 0.0f, 0.0f,
                           (tamanho_campo.x / 2), 0.0f, 0.0f };

int pontuacaoA = 0;
int pontuacaoB = 0;

string placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);

void init(void) {
    /* selecionar cor de fundo (preto) */
    glClearColor(69.0f / 255.0f, 39.0f / 255.0f, .0f / 255.0f, 1.0f); // set background color to black
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

    glTranslatef(.0f, .0f, (tamanho_barra.z / 2.0f) + (tamanho_campo.z / 2.0f));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);
    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_barT(int indice)
{
    glPushMatrix();

    if (indice < 3) glTranslatef(posicoes_barrasT[indice] + (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], proximidade_da_camera + posicoes_barrasT[indice + 2]);
    else            glTranslatef(posicoes_barrasT[indice] - (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], proximidade_da_camera + posicoes_barrasT[indice + 2]);

    glTranslatef(.0f, .0f, (tamanho_barra.z / 2.0f) + (tamanho_campo.z / 2.0f) + (tamanho_barra.z / 2.0f));
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
    glTranslatef(bola->position_atual.x, bola->position_atual.y, proximidade_da_camera + bola->raio + (tamanho_campo.z / 2));

    glPushMatrix();

    glRotatef(bola->position_atual.x * bola->velocidadeRotacao, 0, 1, 0);
    glRotatef(bola->position_atual.y * bola->velocidadeRotacao, 1, 0, 0);
    glutWireSphere(bola->raio, bola->slices, bola->stacks);

    glPopMatrix();

    glPopMatrix();
}

void draw_text()
{
    placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);
    glRasterPos3f(-0.08f, 1.0f, 0.5f);

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

void verify_goal()
{
    bool rangeYTrave = (bola->position_atual.y <= posicoes_barras[1]) && (bola->position_atual.y >= posicoes_barras[4]);

    if (bola->position_atual.y >= 0.45 || bola->position_atual.y <= -0.45) // limites superior e inferior
    {
        bola->reset_position();
    }
    else if (bola->position_atual.x <= posicoes_barras[0])
    {
        if (rangeYTrave)    pontuacaoB++;

        bola->reset_position();
    }
    else if (bola->position_atual.x >= posicoes_barras[6])
    {
        if (rangeYTrave)    pontuacaoA++;

        bola->reset_position();
    }
}

void keyboard_handler(unsigned char key, int x, int y)
{
    camera->rotate(key);

    camera->modify_mode(key);

    if (bola->move(key))
    {
        verify_goal();
    }

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
