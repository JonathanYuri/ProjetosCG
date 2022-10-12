#include <iostream>
#include <vector>
#include <string>

#include "Camera.h"
#include "Bola.h"

using namespace std;

Camera* camera = new Camera();
Bola* bola = new Bola();

/* Polimento:
*  Bresenham (tentar colocar num arquivo)
*  Bresenham_circles() for's
*  draw_lines()
   Menu */

struct tamanho {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

GLint width = 900;
GLint height = 900;

GLfloat proximidade_da_camera = 2.5f;
float pixel_size = 0.01f;

tamanho tamanho_barra = { 0.01f, 0.01f, 0.05f };

tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };
//tamanho tamanho_campo = { 1.2f, 0.9f, 0.1f };

int grid_division = 13;
int qnt_pixel_por_zero_ponto_1 = 1;

bool menu = false;

GLfloat color_grid[][3] = { 118.0f / 255.0f, 180.0f / 255.0f, 53.0f / 255.0f,
                            91.0f / 255.0f, 165.0f / 255.0f, 44.0f / 255.0f };

GLfloat posicoes_barras[] = { -(tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           -(tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                           (tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f };

tamanho tamanho_barraT = { tamanho_barra.x , 0.0732f * (tamanho_campo.y / 0.9f), tamanho_barra.x };

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

int pontuacaoA = 0;
int pontuacaoB = 0;

string placar = to_string(pontuacaoA) + " x " + to_string(pontuacaoB);

void init(void) {
    glClearColor(69.0f / 255.0f, 39.0f / 255.0f, .0f / 255.0f, 1.0f); // set background color to black
    //glClearColor(.0, .0, .0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}

vector<pair<int, int>> Bresenham_lines(int xI, int yI, int xF, int yF)
{
    vector<pair<int, int>> points;

    int dx = xF - xI;
    int dy = yF - yI;

    int dAtual = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);

    int xA = xI;
    int yA = yI;

    points.push_back({ xI, yI });
    while ((xA != xF) || (yA != yF))
    {
        if (dAtual < 0)     dAtual += dE;
        else
        {
            dAtual += dNE;
            yA += 1;
        }
        xA += 1;
        points.push_back({ xA, yA });
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
        points = Bresenham_lines(0, 0, abs(nX), abs(nY));
    }
    else
    {
        points = Bresenham_lines(0, 0, abs(nY), abs(nX));
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

    return points;
}

vector <pair<int, int>> Bresenham_circles(int raio, int qnt_quadrantes)
{
    vector <pair<int, int>> pontos;
    int x = 0, y = raio;
    float d = (5 / 4) - y;

    //primeiro octante, primeiro quadrante
    pontos.push_back({ x, y });
    while (y > x)
    {
        if (d >= 0)
        {
            d += (2 * x) - (2 * y) + 5;
            x++;
            y--;
        }
        else
        {
            d += (2 * x) + 3;
            x++;
        }
        pontos.push_back({ x, y });
    }
    vector <pair<int, int>> ponto;

    //segundo octante, primeiro quadrante
    for (auto p : pontos)
    {
        ponto.push_back({ p.second, p.first });
    }
    for (int i = ponto.size() - 1; i >= 0; i--)
    {
        pontos.push_back({ ponto[i].first, ponto[i].second });
    }
    ponto.clear();

    if (qnt_quadrantes == 1)    return pontos;

    //quarto quadrante, 2 octantes
    for (auto p : pontos)
    {
        ponto.push_back({ p.first, -p.second });
    }
    for (int i = ponto.size() - 1; i >= 0; i--)
    {
        pontos.push_back({ ponto[i].first, ponto[i].second });
    }
    ponto.clear();

    if (qnt_quadrantes == 2)    return pontos;

    for (auto p : pontos)
    {
        ponto.push_back({ -p.first, p.second });
    }
    for (int i = ponto.size() - 1; i >= 0; i--)
    {
        pontos.push_back({ ponto[i].first, ponto[i].second });
    }
    ponto.clear();

    return pontos;
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

int ajustar(float x)
{
    return x * 10;
}

void draw_cornerKick(float rotate, float translateX, float translateY, vector<pair<float, float>> points)
{
    glPushMatrix();
        glTranslatef(translateX, translateY, .0f);
        glRotatef(rotate, 0, 0, 1);

        glBegin(GL_LINES);
            for (int i = 0; i < points.size(); i++)
            {
                if (i + 1 < points.size())
                {
                    glVertex3f(points[i].first, points[i].second, 0.001f);
                    glVertex3f(points[i + 1].first, points[i + 1].second, 0.001f);
                }
            }
        glEnd();
    glPopMatrix();
}

void draw_halfMoon(float translateX, bool esquerdo, vector<pair<float, float>> points)
{
    glPushMatrix();
        glTranslatef(translateX, 0.0f, 0.0f);

        glBegin(GL_LINES);
            for (int i = 0; i < points.size(); i++)
            {
                if (i + 1 < points.size())
                {
                    if (esquerdo)
                    {
                        if (points[i].first >= 0.08)
                        {
                            glVertex3f(points[i].first, points[i].second, 0.001f);
                            glVertex3f(points[i + 1].first, points[i + 1].second, 0.001f);
                        }
                    }
                    else
                    {
                        if (points[i].first <= -0.08)
                        {
                            glVertex3f(points[i].first, points[i].second, 0.001f);
                            glVertex3f(points[i + 1].first, points[i + 1].second, 0.001f);
                        }
                    }
                }
            }
        glEnd();
    glPopMatrix();
}

void draw_circles()
{
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    vector<pair<int, int>> pointInt;
    float divisor = 1000.0f;

    float raio = 0.0915 * (tamanho_campo.x / 1.2f);
    pointInt = Bresenham_circles(raio * divisor, 4);

    vector<pair<float, float>> point;
    for (auto p : pointInt)
    {
        point.push_back({ p.first / divisor, p.second / divisor });
    }

    glPushMatrix();

        glTranslatef(.0, .0, proximidade_da_camera + (tamanho_campo.z / 2.0f));

        // circulo do meio
        glBegin(GL_LINES);
            for (int i = 0; i < point.size(); i++)
            {
                if (i + 1 < point.size())
                {
                    glVertex3f(point[i].first, point[i].second, 0.001f);
                    glVertex3f(point[i + 1].first, point[i + 1].second, 0.001f);
                }
            }
        glEnd();

        //semicirculo do lado direito
        draw_halfMoon((tamanho_campo.x / 2) - 0.16f * (tamanho_campo.x / 1.2f), false, point);

        // semicirculo do lado esquerdo
        draw_halfMoon(-(tamanho_campo.x / 2) + 0.16f * (tamanho_campo.x / 1.2f), true, point);

        // Escanteios

        point.clear();
        pointInt.clear();

        raio = 0.01 * (tamanho_campo.x / 1.2f);
        pointInt = Bresenham_circles(raio * divisor, 1);

        for (auto p : pointInt)
        {
            point.push_back({ p.first / divisor, p.second / divisor });
        }

        //Escanteio inferior esquerdo
        draw_cornerKick(0.0f, -tamanho_campo.x / 2, -tamanho_campo.y / 2, point);

        //Escanteio inferior direito
        draw_cornerKick(90.0f, tamanho_campo.x / 2, -tamanho_campo.y / 2, point);

        //Escanteio superior direito
        draw_cornerKick(180.0f, tamanho_campo.x / 2, tamanho_campo.y / 2, point);

        //Escanteio superior esquerdo
        draw_cornerKick(270.0f, -tamanho_campo.x / 2, tamanho_campo.y / 2, point);

    glPopMatrix();
}

void draw_lines()
{
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0f);

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

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar((tamanho_campo.x / 2) - 0.055f);
    yI = ajustar(-0.1384f);
    xF = ajustar(tamanho_campo.x / 2);
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    // area esquerda
    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-0.435f * (tamanho_campo.x / 1.2f));
    yI = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(-0.2016f * (tamanho_campo.y / 0.9f));

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(0.1384f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    xI = ajustar(-(tamanho_campo.x / 2) + 0.055f);
    yI = ajustar(-0.1384f);
    xF = ajustar(-(tamanho_campo.x / 2));
    yF = ajustar(-0.1384f);

    points.push_back(TraceLine(xI * qnt_pixel_por_zero_ponto_1,
        yI * qnt_pixel_por_zero_ponto_1,
        xF * qnt_pixel_por_zero_ponto_1,
        yF * qnt_pixel_por_zero_ponto_1));

    glPushMatrix();
        glTranslatef(.0, .0, proximidade_da_camera + (tamanho_campo.z / 2.0f));
        
        glBegin(GL_LINES);
            for (auto point : points)
            {
                for (int i = 0; i < point.size(); i++)
                {
                    if (i + 1 < point.size())
                    {
                        glVertex3f(point[i].first / divisor, point[i].second / divisor, 0.001f);
                        glVertex3f(point[i + 1].first / divisor, point[i + 1].second / divisor, 0.001f);
                    }
                }
            }
        glEnd();

    glPopMatrix();
}

void draw_field()
{
    float division_length = tamanho_campo.x / grid_division;

    glPushMatrix();
        glTranslatef(.0, .0, proximidade_da_camera);

        for (int i = 0; i < grid_division; i++)
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

        for (int i = 0; i < faces_campo.size(); i+=12)
        {
            glBegin(GL_POLYGON);
                glVertex3f(faces_campo[i], faces_campo[i+1], faces_campo[i+2]);
                glVertex3f(faces_campo[i+3], faces_campo[i+4], faces_campo[i+5]);

                glVertex3f(faces_campo[i+6], faces_campo[i+7], faces_campo[i+8]);
                glVertex3f(faces_campo[i+9], faces_campo[i+10], faces_campo[i+11]);
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
    glRasterPos3f(-0.08f, 0.8f, 0.5f + proximidade_da_camera);

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

void displayFcn()
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
    else    displayFcn();
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

    if (key == 'm' || key == 'M')
    {
        menu = !menu;
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
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Campo");
    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard_handler);
    glutSpecialFunc(specialKeys_handler);
    glutMainLoop();

    return 0;
}