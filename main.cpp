﻿#include <iostream>
#include <vector>
#include <string>

#include "Camera.h"
#include "Bola.h"
#include "Bresenham.h"

using namespace std;

Camera* camera = new Camera();
Bola* bola = new Bola();

struct tamanho {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

int grid_division_x_field = 13;
int grid_division_y_field = 7;
unsigned int delay = 1000 / 60;

/* Menu */

bool menu = false;

vector<string> comandos = { "{W, A, S, D}: rotacionar a camera",
                           "{Q, E}: rotacionar o eixo z da camera",
                           "SETAS: {UP, LEFT, DOWN, RIGHT}: movimentar a camera",
                           "{1, 2}: alterar o modo da camera",
                           "{I, J, K, L}: movimentar a bola",
                           "{M}: desativa / ativar o menu"
};

/* Window */

GLint windowWidth = 900;
GLint windowHeight = 900;

GLint windowPositionX = 0;
GLint windowPositionY = 0;

GLfloat proximidade_da_camera = 2.5f;

GLfloat color_grid[][3] = { 118.0f / 255.0f, 180.0f / 255.0f, 53.0f / 255.0f,
                            91.0f / 255.0f, 165.0f / 255.0f, 44.0f / 255.0f };

/* Medidas */

tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };

tamanho tamanho_barra = { 0.01f, 0.01f, 0.05f };

tamanho tamanho_barraT = { tamanho_barra.x , 0.0732f * (tamanho_campo.y / 0.9f), tamanho_barra.x };

GLfloat posicoes_barras[] = { -(tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           -(tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f };

GLfloat posicoes_barrasT[] = { -(tamanho_campo.x / 2), 0.0f, 0.0f,
                                (tamanho_campo.x / 2), 0.0f, 0.0f };

vector<GLfloat> faces_campo = {
    // tras
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //esquerda
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //direita
    tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //cima
    tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //baixo
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2
};

/* Arquibancada */

int niveis = 7;
float espaco_arquibancada = 0.05;

GLfloat larguraArquibancada = tamanho_campo.x / 4;
GLfloat larguraDegrau = larguraArquibancada;
//GLfloat larguraDegrau = 0.4; // <- ajustar para esse

vector<GLfloat> vertices_arquibancada = {
    //frente
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //tras
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

    // cima
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,

    //baixo
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

    // esquerda
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

    // direita
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
};

vector<GLfloat> vertices_arquibancada2 = {
    //frente
    tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,

    //tras
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

    // cima
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,

    //baixo
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

    // esquerda
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

    // direita
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2,
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2,
    -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
};

GLfloat lines[][4] = {
    //(xI, yI, xF, yF)

    // linha do meio
    .0f, tamanho_campo.y / 2.0f, .0f, -tamanho_campo.y / 2.0f,

    // linha esquerda
    -tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f, -tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f,

    // linha direita
    tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f, tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f,

    // linha de cima
    -tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f, tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f,

    // linha de baixo
    -tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f, tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f,

    // area direita
    0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), 0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f),
    0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), tamanho_campo.x / 2, 0.2016f * (tamanho_campo.y / 0.9f),
    0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f), tamanho_campo.x / 2, -0.2016f * (tamanho_campo.y / 0.9f),

    (tamanho_campo.x / 2) - 0.055f, 0.1384f, (tamanho_campo.x / 2) - 0.055f, -0.1384f,
    (tamanho_campo.x / 2) - 0.055f, 0.1384f, tamanho_campo.x / 2, 0.1384f,
    (tamanho_campo.x / 2) - 0.055f, -0.1384f, tamanho_campo.x / 2, -0.1384f,

    // area esquerda
    -lines[5][0], lines[5][1], -lines[5][2], lines[5][3],
    -0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), -(tamanho_campo.x / 2), 0.2016f * (tamanho_campo.y / 0.9f),
    -0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f), -(tamanho_campo.x / 2), -0.2016f * (tamanho_campo.y / 0.9f),

    -(tamanho_campo.x / 2) + 0.055f, 0.1384f, -(tamanho_campo.x / 2) + 0.055f, -0.1384f,
    -(tamanho_campo.x / 2) + 0.055f, 0.1384f, -(tamanho_campo.x / 2), 0.1384f,
    -(tamanho_campo.x / 2) + 0.055f, -0.1384f, -(tamanho_campo.x / 2), -0.1384f
};

/* Placar */

int pontuacaoA = 0;
int pontuacaoB = 0;

string placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);

/* DIA */
bool isDay = true;

void setup_lightning()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}

void init(void) {
    glClearColor(.0, .0, .0, 1.0);
    glEnable(GL_DEPTH_TEST);
    setup_lightning();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
}

void connect_dots(vector<pair<int, int>> points, float divisor)
{
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < points.size(); i++)
    {
        if (i + 1 < points.size())
        {
            glVertex3f(points[i].first / divisor, points[i].second / divisor, 0.001f);
            glVertex3f(points[i + 1].first / divisor, points[i + 1].second / divisor, 0.001f);
        }
    }
    glEnd();
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
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 11; i += 3)   draw_bar(i);
    for (int i = 0; i < 6; i += 3)    draw_barT(i);
}

void draw_cornerKick(float rotate, float translateX, float translateY, vector<pair<int, int>> points, float divisor)
{
    glPushMatrix();
    glTranslatef(translateX, translateY, .0f);
    glRotatef(rotate, 0, 0, 1);

    connect_dots(points, divisor);
    glPopMatrix();
}

void draw_halfMoon(float translateX, bool esquerdo, vector<pair<int, int>> points, float divisor)
{
    glPushMatrix();
    glTranslatef(translateX, 0.0f, 0.0f);

    vector<pair<int, int>> point;
    if (esquerdo)
    {
        for (unsigned int i = 0; i < points.size(); i++)
        {
            if ((points[i].first / divisor) >= 0.08f)
            {
                point.push_back(points[i]);
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < points.size(); i++)
        {
            if ((points[i].first / divisor) <= -0.08f)
            {
                point.push_back(points[i]);
            }
        }
    }

    connect_dots(point, divisor);
    point.clear();

    glPopMatrix();
}

void draw_circles()
{
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    vector<pair<int, int>> points;
    float divisor = 1000.0f;

    float raio = 0.0915f * (tamanho_campo.x / 1.2f);

    glPushMatrix();

    glTranslatef(.0, .0, proximidade_da_camera + (tamanho_campo.z / 2.0f));

    // circulo do meio
    points = Bresenham_circles((int)(raio * divisor), 4);
    connect_dots(points, divisor);

    //semicirculo do lado direito
    draw_halfMoon((tamanho_campo.x / 2) - 0.16f * (tamanho_campo.x / 1.2f), false, points, divisor);

    // semicirculo do lado esquerdo
    draw_halfMoon(-(tamanho_campo.x / 2) + 0.16f * (tamanho_campo.x / 1.2f), true, points, divisor);

    // Escanteios
    points.clear();

    raio = 0.01f * (tamanho_campo.x / 1.2f);
    points = Bresenham_circles((int)(raio * divisor), 1);

    //Escanteio inferior esquerdo
    draw_cornerKick(0.0f, -tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio inferior direito
    draw_cornerKick(90.0f, tamanho_campo.x / 2.0f, -tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio superior direito
    draw_cornerKick(180.0f, tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio superior esquerdo
    draw_cornerKick(270.0f, -tamanho_campo.x / 2.0f, tamanho_campo.y / 2.0f, points, divisor);

    glPopMatrix();
}

void draw_lines()
{
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    float divisor = 10.0f;

    vector<vector<pair<int, int>>> points;

    for (int i = 0; i < 17; i++)
    {
        points.push_back(TraceLine((int)(lines[i][0] * divisor),
            (int)(lines[i][1] * divisor),
            (int)(lines[i][2] * divisor),
            (int)(lines[i][3] * divisor)));
    }

    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera + (tamanho_campo.z / 2.0f));

    for (auto point : points)
    {
        connect_dots(point, divisor);
    }

    glPopMatrix();
}

void draw_field()
{
    float division_length = tamanho_campo.x / grid_division_x_field;
    float division_height = tamanho_campo.y / grid_division_y_field;

    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera);

    glColor3f(0, 1.0, 0);
    glTranslatef(-tamanho_campo.x / 2, 0, 0);
    glTranslatef(division_length / 2, 0, 0);
    for (int i = 0; i < grid_division_x_field; i++)
    {
        if (i != 0) glTranslatef(division_length, 0, 0);
        glColor3f(color_grid[(i % 2)][0], color_grid[(i % 2)][1], color_grid[(i % 2)][2]);
        
        glPushMatrix();
        glTranslatef(0, tamanho_campo.y / 2, 0);
        glTranslatef(0, -division_height / 2, 0);
        for (int j = 0; j < grid_division_y_field; j++)
        {
            if (j != 0) glTranslatef(0, -division_height, 0);
            glPushMatrix();
            glScalef(division_length, division_height, tamanho_campo.z);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void draw_ball()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(bola->position_atual.x, bola->position_atual.y, proximidade_da_camera + bola->raio + (tamanho_campo.z / 2));

    glPushMatrix();

    glRotatef(bola->position_atual.x * bola->velocidadeRotacao, 0, 1, 0);
    glRotatef(bola->position_atual.y * bola->velocidadeRotacao, 1, 0, 0);
    glutSolidSphere(bola->raio, bola->slices, bola->stacks);

    glPopMatrix();
    glPopMatrix();
}

void draw_text(string str)
{
    for (char p : str)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p);
    }
}

void draw_scoreBoard()
{
    glColor3f(1.0, 1.0, 1.0);
    placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);
    glRasterPos3f(-0.05f, 0.8f, 0.5f + proximidade_da_camera);

    draw_text(placar);
}

void to_position_camera()
{
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
}

void set_lights()
{
    //float light_diffuse[] = { 1.0f , 1.0f , 1.0f }; // luz branca
    //float light_specular[] = { 1.0f , 0.0f , 0.0f }; // Luz branca

    float light_ambient[] = { 0.01f, 0.01f, 0.01f };
    float light_position[] = { 0.0f, 0.0f, 100.0f, 1.0f };

    glPushMatrix();
    float t = 1.0f * glutGet(GLUT_ELAPSED_TIME) / 24000.0f;

    // a cada 24 segundos ta completando a volta
    glRotatef(360 * t, 0.0f, 1.0f, 0.0f);
    int r = int(t * 10) % 360;

    if (r >= 90 && r <= 270)
    {
        if (isDay) isDay = !isDay;
    }
    else
    {
        if (!isDay) isDay = !isDay;
    }

    //cout << "Eh dia? " << isDay << endl;

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glPopMatrix();
}

void draw_layer(vector<float> vertices, float offset_x, float offset_y)
{
    for (unsigned int i = 0; i < vertices.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        if (i == 0) // para frente
        {
            glVertex3f(vertices[i] + offset_x, vertices[i + 1] - offset_y, vertices[i + 2]);
            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
            glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            glVertex3f(vertices[i + 9] + offset_x, vertices[i + 10] - offset_y, vertices[i + 11]);
        }
        else if (i == 24 || i == 36) // cima ou baixo
        {
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
            glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] - offset_y, vertices[i + 8]);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 48 || i == 60) // esquerda ou direita
        {
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            if (i == 48)
            {
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] - offset_y, vertices[i + 5]);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] - offset_y, vertices[i + 8]);
            }
            else
            {
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 12) // tras
        {
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);

            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        glEnd();
    }
}

void draw_layer2(vector<float> vertices, GLfloat offset_x, float offset_y)
{
    for (unsigned int i = 0; i < vertices.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        if (i == 0) // para frente
        {
            //glColor3f(1.0, 1.0, .0);
            glVertex3f(vertices[i] + offset_x, vertices[i + 1] + offset_y, vertices[i + 2]);
            glVertex3f(vertices[i + 3] - offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
            glVertex3f(vertices[i + 6] - offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            glVertex3f(vertices[i + 9] + offset_x, vertices[i + 10] + offset_y, vertices[i + 11]);
        }
        else if (i == 24 || i == 36) // cima ou baixo
        {
            //glColor3f(.0, 1.0, .0);
            glVertex3f(vertices[i] - offset_x, vertices[i + 1] + offset_y, vertices[i + 2]);
            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 48 || i == 60) // esquerda ou direita
        {
            //glColor3f(.0, 1.0, 1.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            if (i == 48)
            {
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }
            else
            {
                //glColor3f(1.0, .0, 1.0);
                glVertex3f(vertices[i + 3] - offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);
                glVertex3f(vertices[i + 6] - offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 12) // tras
        {
            //glColor3f(1.0, 1.0, 1.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        glEnd();
    }
}

void draw_bench()
{
    int niveis = 7;
    float espaco_arquibancada = 0.05;

    float offset_x = .0f, offset_y = .0f;
    glPushMatrix();
    for (int i = 0; i < niveis; i++, offset_x += espaco_arquibancada, offset_y += (larguraDegrau * espaco_arquibancada) / larguraArquibancada)
    {
        if (i % 2 == 0)     glColor3f(.0, .0, .0);
        else    glColor3f(1.0f, 1.0f, 1.0f);

        if (i != 0)     glTranslatef(.0, .0, tamanho_campo.z);

        draw_layer(vertices_arquibancada, -offset_x, offset_y);
    }
    glPopMatrix();
}

void draw_bench2()
{
    float offset_x = .0f, offset_y = .0f;
    glPushMatrix();
    for (int i = 0; i < niveis; i++, offset_y += espaco_arquibancada, offset_x += (larguraDegrau * espaco_arquibancada) / larguraArquibancada)
    {
        if (i % 2 == 0)     glColor3f(.0, .0, .0); //glColor3f(1.0, .0, .0);
        else    glColor3f(1.0f, 1.0f, 1.0f); //glColor3f(.0f, .0f, 1.0f);

        if (i != 0)     glTranslatef(.0, .0, tamanho_campo.z);

        draw_layer2(vertices_arquibancada2, offset_x, -offset_y);
    }
    glPopMatrix();
}

void draw_stadium()
{
    glPushMatrix();
    glTranslatef(0, 0, proximidade_da_camera);

    // esquerda
    draw_bench();

    // direita
    glPushMatrix();
    glScalef(-1, 1, 1); // espelhar
    draw_bench();
    glPopMatrix();

    // baixo
    draw_bench2();

    // cima
    glPushMatrix();
    glScalef(1, -1, 1); // espelhar
    draw_bench2();
    glPopMatrix();

    glPopMatrix();
}

void displayField()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(69.0f / 255.0f, 39.0f / 255.0f, .0f / 255.0f, 1.0f); // marrom

    set_lights();

    glLoadIdentity();

    to_position_camera();

    draw_stadium();
    draw_field();

    draw_bars();
    draw_ball();

    draw_scoreBoard();
    draw_lines();
    draw_circles();

    glutSwapBuffers();
}

void displayMenu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(.0, .0, .0, 1.0);

    gluLookAt(0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 0.5f,
        0, 1, 0);

    glColor3f(1.0, 1.0, 1.0);

    string menu = "MENU";

    // draw menu
    glRasterPos3f(-0.05f, 0.5f, 0.5f + proximidade_da_camera);
    draw_text(menu);

    // draw commands menu
    for (unsigned int i = 0; i < comandos.size(); i++)
    {
        glRasterPos3f(-0.3f, 0.2f - (i * 0.1f), 0.5f + proximidade_da_camera);
        draw_text(comandos[i]);
    }

    glutSwapBuffers();
}

void display(void)
{
    if (menu)   displayMenu();
    else    displayField();
}

void verify_goal()
{
    bool rangeYTrave = (bola->position_atual.y <= posicoes_barras[1]) && (bola->position_atual.y >= posicoes_barras[4]);

    if (bola->position_atual.y >= (tamanho_campo.y / 2) || bola->position_atual.y <= -(tamanho_campo.y / 2)) // limites superior e inferior
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

    if (bola->move(key))    verify_goal();

    if (key == 'm' || key == 'M')   menu = !menu;

    glutPostRedisplay();
}

void specialKeys_handler(int key, int x, int y)
{
    camera->move(key);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(delay, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutCreateWindow("Campo");
    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard_handler);
    glutSpecialFunc(specialKeys_handler);

    glutMainLoop();

    return 0;
}
