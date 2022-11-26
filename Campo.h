#pragma once
#include <vector>
#include "Tipos.h"

using namespace std;

class Campo
{
public:
    tamanho tamanho_campo = { 2.4f, 1.8f, 0.1f };
    vector<GLfloat> posicoes_barras = { -(tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                               -(tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                               (tamanho_campo.x / 2), 0.0366f * (tamanho_campo.y / 0.9f), 0.0f,
                               (tamanho_campo.x / 2), -0.0366f * (tamanho_campo.y / 0.9f), 0.0f };

    void draw_field(GLuint texid, GLuint texMaisClara);

    void draw_stadium(GLuint texID[]);

    void draw_bars();

private:
    int grid_division_field = 13;

    vector<vector<GLfloat>> color_grid = {
        { 118.0f / 255.0f, 180.0f / 255.0f, 53.0f / 255.0f },
        { 91.0f / 255.0f, 165.0f / 255.0f, 44.0f / 255.0f } };

    tamanho tamanho_barra = { 0.01f, 0.01f, 0.05f };

    tamanho tamanho_barraT = { tamanho_barra.x , 0.0732f * (tamanho_campo.y / 0.9f), tamanho_barra.x };

    vector<GLfloat> posicoes_barrasT = {-(tamanho_campo.x / 2), 0.0f, 0.0f,
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

    void draw_bar(int indice);

    void draw_barT(int indice);

    void draw_outlines(GLuint texid);

    /* Arquibancada */

    int niveis = 7;
    float espaco_arquibancada = 0.05f;
    float espacamento_lateral = 0.1f;

    GLfloat larguraArquibancada = tamanho_campo.x / 4;
    GLfloat larguraDegrau = larguraArquibancada;

    vector<GLfloat> vertices_arquibancada = {
        //frente
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,

        //tras
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

        // cima
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,

        //baixo
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

        // esquerda
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, -tamanho_campo.y / 2 - larguraDegrau, -tamanho_campo.z / 2,

        // direita
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraArquibancada, tamanho_campo.y / 2 + larguraDegrau, -tamanho_campo.z / 2,
    };

    vector<GLfloat> vertices_arquibancada2 = {
        //frente
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,

        //tras
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

        // cima
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,

        //baixo
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

        // esquerda
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        tamanho_campo.x / 2 + espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        tamanho_campo.x / 2 + larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,

        // direita
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - espacamento_lateral, -tamanho_campo.y / 2 - espacamento_lateral, -tamanho_campo.z / 2,
        -tamanho_campo.x / 2 - larguraDegrau, -tamanho_campo.y / 2 - larguraArquibancada, -tamanho_campo.z / 2,
    };

    void draw_layer(vector<float> vertices, float offset_x, float offset_y, GLuint texid);

    void draw_layer2(vector<float> vertices, float offset_x, float offset_y, GLuint texid);

    void draw_bench(bool cima, GLuint texID[]);
};

