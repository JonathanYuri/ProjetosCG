#include "Bola.h"

bool Bola::move(unsigned char key)
{
    bool move = false;
    if (key == 'j' || key == 'J')   position_atual.x -= velocidade;    move = true;
    if (key == 'l' || key == 'L')   position_atual.x += velocidade;    move = true;

    if (key == 'k' || key == 'K')   position_atual.y -= velocidade;    move = true;
    if (key == 'i' || key == 'I')   position_atual.y += velocidade;    move = true;

    return move;
}

void Bola::verify_goal(GLfloat posicoes_barras[], int *pontuacaoA, int *pontuacaoB)
{
    bool rangeYTrave = (position_atual.y <= posicoes_barras[1]) && (position_atual.y >= posicoes_barras[4]);

    if (position_atual.y >= 0.45 || position_atual.y <= -0.45) // limites superior e inferior
    {
        reset_position();
    }
    else if (position_atual.x <= posicoes_barras[0])
    {
        if (rangeYTrave)    *pontuacaoB = *pontuacaoB + 1;

        reset_position();
    }
    else if (position_atual.x >= posicoes_barras[6])
    {
        if (rangeYTrave)    *pontuacaoA = *pontuacaoB + 1;

        reset_position();
    }
}

void Bola::reset_position()
{
    position_atual.x = position_inicial.x;
    position_atual.y = position_inicial.y;
}