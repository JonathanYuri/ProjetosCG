#pragma once

struct position
{
	float x;
	float y;
	float z;
};

class Camera
{
public:
	char mode = '1';

	float qntRotate = 0.1f;

	position position_inicial = { 0.0f, 0.0f, 5.0f };
	position position_atual = position_inicial;

	position targetInicial = { 0.0f, 0.0f, 0.5f };
	position targetAtual = targetInicial;

	void modify_mode(unsigned char key);

	void reset();

	void move(int key);

	void rotate(unsigned char key);
};

