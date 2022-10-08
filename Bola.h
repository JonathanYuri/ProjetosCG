#pragma once
#include "Tipos.h"

class Bola
{
public:
    GLfloat raio = 0.01f;
    // testar rotacao: raioBola * 100.0

    GLfloat velocidade = 0.01f;
    GLfloat velocidadeRotacao = 1000.0f;

    int slices = 30;
    int stacks = 30;

    position position_inicial = { 0.0f, 0.0f, 0.5f };

    position position_atual = position_inicial;

    void reset_position();

    bool move(unsigned char key);
};

