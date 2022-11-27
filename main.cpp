#include <iostream>
#include <vector>
#include <string>

#include "Camera.h"
#include "Campo.h"
#include "Bola.h"
#include "Bresenham.h"
#include "stb_image.h"

using namespace std;

Camera* camera = new Camera();
Bola* bola = new Bola();
Campo* campo = new Campo();

int grid_division_x_field = 13;
int grid_division_y_field = 7;

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

/* Medidas */

GLfloat lines[][4] = {
    //(xI, yI, xF, yF)

    // linha do meio
    .0f, campo->tamanho_campo.y / 2.0f, .0f, -campo->tamanho_campo.y / 2.0f,

    // linha esquerda
    -campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f, -campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f,

    // linha direita
    campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f, campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f,

    // linha de cima
    -campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f, campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f,

    // linha de baixo
    -campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f, campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f,

    // area direita
    0.435f * (campo->tamanho_campo.x / 1.2f), 0.2016f * (campo->tamanho_campo.y / 0.9f), 0.435f * (campo->tamanho_campo.x / 1.2f), -0.2016f * (campo->tamanho_campo.y / 0.9f),
    0.435f * (campo->tamanho_campo.x / 1.2f), 0.2016f * (campo->tamanho_campo.y / 0.9f), campo->tamanho_campo.x / 2, 0.2016f * (campo->tamanho_campo.y / 0.9f),
    0.435f * (campo->tamanho_campo.x / 1.2f), -0.2016f * (campo->tamanho_campo.y / 0.9f), campo->tamanho_campo.x / 2, -0.2016f * (campo->tamanho_campo.y / 0.9f),

    (campo->tamanho_campo.x / 2) - 0.055f, 0.1384f, (campo->tamanho_campo.x / 2) - 0.055f, -0.1384f,
    (campo->tamanho_campo.x / 2) - 0.055f, 0.1384f, campo->tamanho_campo.x / 2, 0.1384f,
    (campo->tamanho_campo.x / 2) - 0.055f, -0.1384f, campo->tamanho_campo.x / 2, -0.1384f,

    // area esquerda
    -lines[5][0], lines[5][1], -lines[5][2], lines[5][3],
    -0.435f * (campo->tamanho_campo.x / 1.2f), 0.2016f * (campo->tamanho_campo.y / 0.9f), -(campo->tamanho_campo.x / 2), 0.2016f * (campo->tamanho_campo.y / 0.9f),
    -0.435f * (campo->tamanho_campo.x / 1.2f), -0.2016f * (campo->tamanho_campo.y / 0.9f), -(campo->tamanho_campo.x / 2), -0.2016f * (campo->tamanho_campo.y / 0.9f),

    -(campo->tamanho_campo.x / 2) + 0.055f, 0.1384f, -(campo->tamanho_campo.x / 2) + 0.055f, -0.1384f,
    -(campo->tamanho_campo.x / 2) + 0.055f, 0.1384f, -(campo->tamanho_campo.x / 2), 0.1384f,
    -(campo->tamanho_campo.x / 2) + 0.055f, -0.1384f, -(campo->tamanho_campo.x / 2), -0.1384f
};

/* Placar */

int pontuacaoA = 0;
int pontuacaoB = 0;

/* DIA */
bool isDay = true;
int horas = 0;

float verde = 0.0f;
float azul = 0.2f;
float razao = 0.8f / 12.0f; // em 12 horas tenho que acabar com 0.8 + 0.2 = 1.0f

GLuint texField[4];
GLuint texFieldAtual[2];
GLuint texArquibancada[2];
GLuint texArquibancadaAtual[1];

void carregaTextura(string filePath, GLuint tex_id)
{
    unsigned char* imgData;
    int largura, altura, canais;
    stbi_set_flip_vertically_on_load(true);
    imgData = stbi_load(filePath.c_str(), &largura, &altura, &canais, 4);

    if (imgData)
    {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        stbi_image_free(imgData);
    }
    else
    {
        cout << "Erro: N foi possivel carregar a textura" << filePath.c_str() << endl;
    }

}

void setup_lightning()
{
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHT1);
}

void init(void) {
    glClearColor(.0, .0, .0, 1.0);
    glEnable(GL_DEPTH_TEST);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glGenTextures(2, texArquibancada);
    glGenTextures(4, texField);
    carregaTextura("./Texturas/grama_escura_dia.png", texField[0]);
    carregaTextura("./Texturas/grama_clara_dia.png", texField[1]);
    carregaTextura("./Texturas/grama_escura_noite.png", texField[2]);
    carregaTextura("./Texturas/grama_clara_noite.png", texField[3]);

    carregaTextura("./Texturas/arquibancada_dia.png", texArquibancada[0]);
    carregaTextura("./Texturas/arquibancada_noite.png", texArquibancada[1]);

    texFieldAtual[0] = texField[2];
    texFieldAtual[1] = texField[3];

    texArquibancadaAtual[0] = texArquibancada[1];

    setup_lightning();

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

    float raio = 0.0915f * (campo->tamanho_campo.x / 1.2f);

    glPushMatrix();

    glTranslatef(.0, .0, campo->tamanho_campo.z / 2.0f);

    // circulo do meio
    points = Bresenham_circles((int)(raio * divisor), 4);
    connect_dots(points, divisor);

    //semicirculo do lado direito
    draw_halfMoon((campo->tamanho_campo.x / 2) - 0.16f * (campo->tamanho_campo.x / 1.2f), false, points, divisor);

    // semicirculo do lado esquerdo
    draw_halfMoon(-(campo->tamanho_campo.x / 2) + 0.16f * (campo->tamanho_campo.x / 1.2f), true, points, divisor);

    // Escanteios
    points.clear();

    raio = 0.01f * (campo->tamanho_campo.x / 1.2f);
    points = Bresenham_circles((int)(raio * divisor), 1);

    //Escanteio inferior esquerdo
    draw_cornerKick(0.0f, -campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio inferior direito
    draw_cornerKick(90.0f, campo->tamanho_campo.x / 2.0f, -campo->tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio superior direito
    draw_cornerKick(180.0f, campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f, points, divisor);

    //Escanteio superior esquerdo
    draw_cornerKick(270.0f, -campo->tamanho_campo.x / 2.0f, campo->tamanho_campo.y / 2.0f, points, divisor);

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
    glTranslatef(.0, .0, campo->tamanho_campo.z / 2.0f);

    for (auto point : points)
    {
        connect_dots(point, divisor);
    }

    glPopMatrix();
}

void draw_ball()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(bola->position_atual.x, bola->position_atual.y, bola->raio + (campo->tamanho_campo.z / 2));

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
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(-0.05f, 0.8f, 0.5f);

    draw_text(to_string(pontuacaoA) + " x " + to_string(pontuacaoB));
}

void draw_hour()
{
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(-0.8f, 0.8f, 0.5f);

    draw_text(to_string(horas) + ":" + to_string(0) + to_string(0));
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
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    float light_diffuse[] = { 0.5f , 0.5f , 0.5f, 1.0f }; // luz branca
    float light_specular[] = { 1.0f , 1.0f , 1.0f, 1.0f };

    float light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float light_position[] = { 100.0f, 0.0f, 0.0f, 1.0f };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glPushMatrix();
    float t = 1.0f * glutGet(GLUT_ELAPSED_TIME) / 24000.0f;    // a cada 24 segundos ta completando a volta
    glRotatef(360 * t, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //glClearColor(.0, .0, 0.2, 1.0); <- noite
    //glClearColor(.0, 0.5, 1.0, 1.0); <- dia
    glClearColor(.0, verde, azul, 1.0f);

    glPopMatrix();
}

void displayField()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    to_position_camera();

    set_lights();

    glPushMatrix();
    glTranslatef(0, 0, proximidade_da_camera);
    campo->draw_stadium(texArquibancadaAtual[0]);

    glEnable(GL_TEXTURE_2D);
    campo->draw_field(texFieldAtual[0], texFieldAtual[1]);
    glDisable(GL_TEXTURE_2D);
    campo->draw_bars();

    draw_ball();

    draw_scoreBoard();
    draw_hour();
    draw_lines();
    draw_circles();
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
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
    bool rangeYTrave = (bola->position_atual.y <= campo->posicoes_barras[1]) && (bola->position_atual.y >= campo->posicoes_barras[4]);

    if (bola->position_atual.y >= (campo->tamanho_campo.y / 2) || bola->position_atual.y <= -(campo->tamanho_campo.y / 2)) // limites superior e inferior
    {
        bola->reset_position();
    }
    else if (bola->position_atual.x <= campo->posicoes_barras[0])
    {
        if (rangeYTrave)    pontuacaoB++;

        bola->reset_position();
    }
    else if (bola->position_atual.x >= campo->posicoes_barras[6])
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

void move_timer()
{
    horas++;
    if (horas == 25)    horas = 1;
}

void change_background_color()
{
    if (horas <= 12)
    {
        azul += razao;
        verde += razao / 2.0f;
    }
    else
    {
        azul -= razao;
        verde -= razao / 2.0f;
    }
}

void change_texture()
{
    if (horas == 6) // eh dia
    {
        texFieldAtual[0] = texField[0];
        texFieldAtual[1] = texField[1];

        texArquibancadaAtual[0] = texArquibancada[0];
    }

    if (horas == 19) // noite
    {
        texFieldAtual[0] = texField[2];
        texFieldAtual[1] = texField[3];

        texArquibancadaAtual[0] = texArquibancada[1];
    }
}

void timer(int)
{
    move_timer();
    change_background_color();
    change_texture();

    glutTimerFunc(1000, timer, 0);
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

    glDeleteTextures(1, texField);
    glDeleteTextures(1, texFieldAtual);
    glDeleteTextures(1, texArquibancada);
    glDeleteTextures(1, texArquibancadaAtual);
    return 0;
}