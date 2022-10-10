#include <iostream>
#include <cfloat>
#include <vector>
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
float pixel_size = 0.01f;

tamanho tamanho_barra = { 0.01f, 0.01f, 0.05f };

tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };
//tamanho tamanho_campo = { 1.2f, 0.9f, 0.1f };
int grid_division = 11;
int qnt_pixel_por_zero_ponto_1 = 1;

GLfloat color_grid[] = { .0f, 0.5f, .0f,
                        .0f, 1.0f, .0f };

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

int ajustar(float x)
{
    return x * 10;
}

vector<pair<int, int>> Bresenham(int xI, int yI, int xF, int yF)
{
    vector<pair<int, int>> points;

    int dx = xF - xI;
    int dy = yF - yI;

    int dAtual = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);
    
    int xA = xI;
    int yA = yI;

    points.push_back({xI, yI});
    while ((xA != xF) || (yA != yF))
    {
        if (dAtual < 0)     dAtual += dE;
        else
        {
            dAtual += dNE;
            yA += 1;
        }
        xA += 1;
        points.push_back({xA, yA});
    }
    return points;
}

vector<pair<int, int>> TraceLine(int xI, int yI, int xF, int yF)
{
    int nX = xF - xI;
    int nY = yF - yI;
    
    vector<pair<int, int>> points;
    if (abs(nX) > abs(nY))
    {
        points = Bresenham(0, 0, abs(nX), abs(nY));
    }
    else
    {
        //cout << "trocar" << endl;
        points = Bresenham(0, 0, abs(nY), abs(nX));
    }
    
    //cout << endl;
    for (auto p : points)
    {
        //cout << "xP: " << p.first << " yP: " << p.second << endl;
    }

    for (int i = 0; i < points.size(); i++)
    {
        if (abs(nY) > abs(nX))
        {
            int aux = points[i].first;
            points[i].first = points[i].second;
            points[i].second = aux;
        }

        if (nX < 0)
        {
            points[i].first = -points[i].first;
        }
        points[i].first += xI;
        if (nY < 0)
        {
            points[i].second = -points[i].second;
        }
        points[i].second += yI;
    }

    //cout << endl;
    for (auto p : points)
    {
        //cout << "xP: " << p.first << " yP: " << p.second << endl;
    }

    return points;
}

void draw_lines()
{
    float divisor = 10.0f;
    divisor *= qnt_pixel_por_zero_ponto_1;

    vector<vector<pair<int, int>>> points;

    int xI = 0, yI = 0, xF = 0, yF = 0;

    // linha do meio
    xI = 0;
    yI = ajustar(tamanho_campo.y / 2.0f);
    xF = 0;
    yF = ajustar(-tamanho_campo.y / 2.0f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
                               yI * qnt_pixel_por_zero_ponto_1,
                               xF * qnt_pixel_por_zero_ponto_1,
                               yF * qnt_pixel_por_zero_ponto_1));

    // linha esquerda
    xI = ajustar(-tamanho_campo.x / 2);
    yI = ajustar(tamanho_campo.y / 2);
    xF = ajustar(-tamanho_campo.x / 2);
    yF = ajustar(-tamanho_campo.y / 2);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    // linha direita
    xI = ajustar(tamanho_campo.x / 2);
    yI = ajustar(tamanho_campo.y / 2);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(-tamanho_campo.y / 2);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    // linha de cima
    xI = ajustar(-tamanho_campo.x / 2);
    yI = ajustar(tamanho_campo.y / 2);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(tamanho_campo.y / 2);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    // linha de baixo
    xI = ajustar(-tamanho_campo.x / 2);
    yI = ajustar(-tamanho_campo.y / 2);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(-tamanho_campo.y / 2);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    // area direita
    xI = ajustar(0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(0.435f * (tamanho_campo.x / 1.2f));
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar((tamanho_campo.x / 2) - 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar((tamanho_campo.x / 2) - 0.055f);
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar((tamanho_campo.x / 2) - 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(0.1384f);

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar((tamanho_campo.x / 2) - 0.055f);
    yI = ajustar(-0.1384f);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    // area esquerda
    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(0.1384f);

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(-0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI* qnt_pixel_por_zero_ponto_1,
        yI* qnt_pixel_por_zero_ponto_1,
        xF* qnt_pixel_por_zero_ponto_1,
        yF* qnt_pixel_por_zero_ponto_1));


    glPushMatrix();
    glColor3f(1.0, .0, .0);
    glLineWidth(2.0f);
    glTranslatef(.0, .0, proximidade_da_camera + (tamanho_campo.z / 2.0f));

    glBegin(GL_POINTS);
    for (auto point : points)
    {
        for (auto p : point)
        {
            //cout << "xP: " << p.first / 10.0f << " yP: " << p.second / 10.0f << endl;
            glVertex3f(p.first / divisor, p.second / divisor, .0f);
        }
    }
    glEnd();

    glColor3f(.0, .0, 1.0f);
    glBegin(GL_LINES);
    for (auto point : points)
    {
        for (int i = 0; i < point.size(); i++)
        {
            if (i + 1 < point.size())
            {
                glVertex3f(point[i].first / divisor, point[i].second / divisor, .0f);
                glVertex3f(point[i + 1].first / divisor, point[i + 1].second / divisor, .0f);
            }
        }
    }
    glEnd();

    glPopMatrix();
    //system("pause");
}

void draw_field()
{
    float division_length = tamanho_campo.x / grid_division;

    glPushMatrix();
    glTranslatef(.0, .0, proximidade_da_camera);

    for (int i = 0; i < grid_division; i++)
    {
        glColor3f(color_grid[(i % 2) * 3], color_grid[((i % 2) * 3) + 1], color_grid[((i % 2) * 3) + 2]);

        //frente
        glBegin(GL_POLYGON);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);

        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glEnd();
    }

    //trás
    glBegin(GL_POLYGON);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);

    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glEnd();

    //esquerda
    glBegin(GL_POLYGON);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);

    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glEnd();

    //direita
    glBegin(GL_POLYGON);
    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);

    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glEnd();

    //cima
    glBegin(GL_POLYGON);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);

    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glEnd();

    //baixo
    glBegin(GL_POLYGON);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);

    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, -tamanho_campo.z / 2);

    glEnd();

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

void draw_scoreBoard()
{
    placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(-0.08f, 0.8f, 0.5f + proximidade_da_camera);

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

    draw_field();
    glColor3f(1.0, 1.0, 1.0);

    draw_bars();
    draw_ball();

    draw_scoreBoard();
    draw_lines();

    glutSwapBuffers();
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