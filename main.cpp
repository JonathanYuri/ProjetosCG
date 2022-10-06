#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <string>
#include <string.h>

using namespace std;

float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

float qntRotate = 0.1;

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


float cam = 1;
float camX = 0;
float camY = 0;
float camZ = 5;

float targetInitialXcam = 0;
float targetInitialYcam = 0;
float targetInitialZcam = 0.5;

float targetXcam = targetInitialXcam;
float targetYcam = targetInitialYcam;
float targetZcam = targetInitialZcam;

float velocidadeBola = 0.01;

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

void draw_bar_1()
{
    glPushMatrix();
    glTranslatef(posicoes_barras[0] + (tamanho_barra.x / 2), posicoes_barras[1], proximidade_da_camera + posicoes_barras[2]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);
    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_bar_2()
{
    glPushMatrix();
    glTranslatef(posicoes_barras[3] + (tamanho_barra.x / 2), posicoes_barras[4], proximidade_da_camera + posicoes_barras[5]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_bar_3()
{
    glPushMatrix();
    glTranslatef(posicoes_barras[6] - (tamanho_barra.x / 2), posicoes_barras[7], proximidade_da_camera + posicoes_barras[8]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_bar_4()
{
    glPushMatrix();
    glTranslatef(posicoes_barras[9] - (tamanho_barra.x / 2), posicoes_barras[10], proximidade_da_camera + posicoes_barras[11]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_barT1()
{
    glPushMatrix();
    glTranslatef(posicoes_barrasT[0] + (tamanho_barra.x / 2), posicoes_barrasT[1], proximidade_da_camera + posicoes_barrasT[2]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0) + (tamanho_barra.z / 2));
    glScalef(tamanho_barraT.x, tamanho_barraT.y, tamanho_barraT.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_barT2()
{
    glPushMatrix();
    glTranslatef(posicoes_barrasT[3] - (tamanho_barra.x / 2), posicoes_barrasT[4], proximidade_da_camera + posicoes_barrasT[5]);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glTranslatef(.0, .0, (tamanho_barra.z / 2.0) + (tamanho_campo.z / 2.0) + (tamanho_barra.z / 2));
    glScalef(tamanho_barraT.x, tamanho_barraT.y, tamanho_barraT.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void draw_bars()
{
    draw_bar_1();
    draw_bar_2();
    draw_bar_3();
    draw_bar_4();

    draw_barT1();
    draw_barT2();
}

void draw_grid()
{

}

void draw_field()
{
    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera);

    if (rotateX != 0)
    {
        glRotatef(rotateX, 1, 0, 0);
    }
    if (rotateY != 0)
    {
        glRotatef(rotateY, 0, 1, 0);
    }
    if (rotateZ != 0)
    {
        glRotatef(rotateZ, 0, 0, 1);
    }

    glScalef(tamanho_campo.x, tamanho_campo.y, tamanho_campo.z);
    glutWireCube(1.0);
    glPopMatrix();
}

void draw_ball()
{
    glPushMatrix();
    glTranslatef(positionBallX, positionBallY, proximidade_da_camera + raioBola + (tamanho_campo.z / 2));
    glutWireSphere(raioBola, 30, 30);
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

void displayFcn(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (cam == 1)
    {
        gluLookAt(camX, camY, camZ,
                  targetXcam, targetYcam, targetZcam,
                  //0, 0, 0.5,
                  0, 1, 0);
    }
    else if (cam == 2)
    {
        gluLookAt(0, 0, 5,
            0, 0, 0.5,
            0, 1, 0);
    }
    else if (cam == 3)
    {
        gluLookAt(targetXcam + .0, targetYcam - 3.0, targetZcam + 3.5,
            targetXcam, targetYcam + 7.0, targetZcam,
            0, 1, 0);
    }

    /*glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
    glEnd();*/

    //cout << camX << " " << camY << " " << camZ << endl;

    glColor3f(.0, 1.0, .0);
    draw_field();
    glColor3f(1.0, 1.0, 1.0);
    draw_bars();
    draw_ball();
    draw_grid();

    draw_text();

    glutSwapBuffers();
}

void keyboard_handler(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        //rotateY += -qntRotate;
        //cout << "LEFT" << endl;
        camX -= qntRotate;
    }
    if (key == 'd' || key == 'D')
    {
        //rotateY += qntRotate;
        //cout << "RIGHT" << endl;
        camX += qntRotate;
    }
    if (key == 'w' || key == 'W')
    {
        //rotateX += -qntRotate;
        //cout << "UP" << endl;
        camY -= qntRotate;
    }
    if (key == 's' || key == 'S')
    {
        //rotateX += qntRotate;
        //cout << "DOWN" << endl;
        camY += qntRotate;
    }
    if (key == 'q' || key == 'Q')
    {
        //rotateZ += qntRotate;
        camZ -= qntRotate;
    }
    if (key == 'e' || key == 'E')
    {
        //rotateZ += -qntRotate;
        camZ += qntRotate;
    }

    if (key == 'j' || key == 'J')
    {
        positionBallX -= velocidadeBola;
    }
    if (key == 'k' || key == 'K')
    {
        positionBallY -= velocidadeBola;
    }
    if (key == 'l' || key == 'L')
    {
        positionBallX += velocidadeBola;
    }
    if (key == 'i' || key == 'I')
    {
        positionBallY += velocidadeBola;
    }

    if (positionBallY >= 0.45 || positionBallY <= -0.45) // limites superior e inferior
    {
        // jogar para o meio
        positionBallX = positionInitialBallX;
        positionBallY = positionInitialBallY;
    }

    if (positionBallX <= posicoes_barras[0])
    {
        if (positionBallY <= posicoes_barras[1] && positionBallY >= posicoes_barras[4])
        {
            //(ponto pro B)
            pontuacaoB++;
            cout << "Pontuacao A: " << pontuacaoA << " Pontuacao B: " << pontuacaoB << endl;
        }
        // jogar para o meio
        positionBallX = positionInitialBallX;
        positionBallY = positionInitialBallY;
    }
    else if (positionBallX >= posicoes_barras[6])
    {
        if (positionBallY <= posicoes_barras[1] && positionBallY >= posicoes_barras[4])
        {
            //(ponto pro A)
            pontuacaoA++;
            cout << "Pontuacao A: " << pontuacaoA << " Pontuacao B: " << pontuacaoB << endl;
        }
        // jogar para o meio
        positionBallX = positionInitialBallX;
        positionBallY = positionInitialBallY;
    }

    if (key == '1')
    {
        cam = 1;

        // zerar a camera
        targetXcam = targetInitialXcam;
        targetYcam = targetInitialYcam;
        targetZcam = targetInitialZcam;
    }
    if (key == '2')
    {
        cam = 2;

        // zerar a camera
        targetXcam = targetInitialXcam;
        targetYcam = targetInitialYcam;
        targetZcam = targetInitialZcam;
    }
    if (key == '3')
    {
        cam = 3;

        // zerar a camera
        targetXcam = targetInitialXcam;
        targetYcam = targetInitialYcam;
        targetZcam = targetInitialZcam;
    }

    glutPostRedisplay();
    //cam = 0;
}

void camera_move(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        camY -= qntRotate;
        targetYcam -= qntRotate;
    }
    if (key == GLUT_KEY_DOWN)
    {
        camY += qntRotate;
        targetYcam += qntRotate;
    }
    if (key == GLUT_KEY_LEFT)
    {
        camX -= qntRotate;
        targetXcam -= qntRotate;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        camX += qntRotate;
        targetXcam += qntRotate;
    }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Campo");
    init();

    glutDisplayFunc(displayFcn);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard_handler);
    glutSpecialFunc(camera_move);
    glutMainLoop();

    return 0;
}