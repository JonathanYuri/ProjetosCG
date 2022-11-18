#include "Bola.h"
#include <iostream>

bool Bola::move(unsigned char key)
{
    bool move = false;
    if (key == 'j' || key == 'J') {
        position_atual.x -= velocidade;
        move = true;
    }
    if (key == 'l' || key == 'L') {
        position_atual.x += velocidade;
        move = true;
    }

    if (key == 'k' || key == 'K') {
        position_atual.y -= velocidade;
        move = true;
    }
    if (key == 'i' || key == 'I') {
        position_atual.y += velocidade;
        move = true;
    }

    return move;
}

void Bola::reset_position()
{
    position_atual.x = position_inicial.x;
    position_atual.y = position_inicial.y;
}