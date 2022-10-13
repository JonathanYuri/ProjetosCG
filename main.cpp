#include <iostream>
#include <vector>
#include <string>

#include "Camera.h"
#include "Bola.h"
#include "Bresenham.h"

using namespace std;

Camera* camera = new Camera();
Bola* bola = new Bola();

/* Menu */

struct tamanho {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

bool menu = false;
int grid_division_field = 13;
unsigned int delay = 1000 / 60;

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
//tamanho tamanho_campo = { 1.2f, 0.9f, 0.1f };

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

GLfloat lines[][4] = {
    //(xI, yI, xF, yF)

    // linha do meio
    .0f, tamanho_campo.y / 2.0f, .0f, -tamanho_campo.y / 2.0f,

    // linha esquerda
    -tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.x / 2, -tamanho_campo.y / 2,

    // linha direita
    tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.x / 2, -tamanho_campo.y / 2,

    // linha de cima
    -tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.x / 2, tamanho_campo.y / 2,

    // linha de baixo
    -tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.x / 2, -tamanho_campo.y / 2,

    // area direita
    0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), 0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f),
    0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), tamanho_campo.x / 2, 0.2016f * (tamanho_campo.y / 0.9f),
    0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f), tamanho_campo.x / 2, -0.2016f * (tamanho_campo.y / 0.9f),

    (tamanho_campo.x / 2) - 0.055f, 0.1384f, (tamanho_campo.x / 2) - 0.055f, -0.1384f,
    (tamanho_campo.x / 2) - 0.055f, 0.1384f, tamanho_campo.x / 2, 0.1384f,
    (tamanho_campo.x / 2) - 0.055f, -0.1384f, tamanho_campo.x / 2, -0.1384f,

    // area esquerda
    -0.435f * (tamanho_campo.x / 1.2f), 0.2016f * (tamanho_campo.y / 0.9f), -0.435f * (tamanho_campo.x / 1.2f), -0.2016f * (tamanho_campo.y / 0.9f),
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

void init(void) {
    glClearColor(69.0f / 255.0f, 39.0f / 255.0f, .0f / 255.0f, 1.0f);
    //glClearColor(.0, .0, .0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
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
    float division_length = tamanho_campo.x / grid_division_field;

    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera);

    for (int i = 0; i < grid_division_field; i++)
    {
        glColor3f(color_grid[(i % 2)][0], color_grid[(i % 2)][1], color_grid[(i % 2)][2]);

        //frente
        glBegin(GL_POLYGON);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);

        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glEnd();
    }

    for (unsigned int i = 0; i < faces_campo.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        glVertex3f(faces_campo[i], faces_campo[i + 1], faces_campo[i + 2]);
        glVertex3f(faces_campo[i + 3], faces_campo[i + 4], faces_campo[i + 5]);

        glVertex3f(faces_campo[i + 6], faces_campo[i + 7], faces_campo[i + 8]);
        glVertex3f(faces_campo[i + 9], faces_campo[i + 10], faces_campo[i + 11]);
        glEnd();
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
    glutWireSphere(bola->raio, bola->slices, bola->stacks);

    glPopMatrix();
    glPopMatrix();
}

void draw_scoreBoard()
{
    glColor3f(1.0, 1.0, 1.0);
    placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);
    glRasterPos3f(-0.05f, 0.8f, 0.5f + proximidade_da_camera);

    for (char p : placar)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p);
    }
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

void displayField()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    to_position_camera();

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
