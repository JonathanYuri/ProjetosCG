#include "Camera.h"

void Camera::reset()
{
	position_atual = position_inicial;
	targetAtual = targetInicial;
}

void Camera::modify_mode(unsigned char key)
{
	if (key == '1' || key == '2')
	{
		mode = key;
		reset();
	}
}

void Camera::move(int key)
{
	if (key == GLUT_KEY_UP)
	{
		position_atual.y -= qntRotate;
		targetAtual.y -= qntRotate;
	}
	if (key == GLUT_KEY_DOWN)
	{
		position_atual.y += qntRotate;
		targetAtual.y += qntRotate;
	}
	if (key == GLUT_KEY_LEFT)
	{
		position_atual.x += qntRotate;
		targetAtual.x += qntRotate;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		position_atual.x -= qntRotate;
		targetAtual.x -= qntRotate;
	}
}

void Camera::rotate(unsigned char key)
{
	if (key == 'a' || key == 'A')   position_atual.x -= qntRotate;
	if (key == 'd' || key == 'D')   position_atual.x += qntRotate;

	if (key == 'w' || key == 'W')   position_atual.y -= qntRotate;
	if (key == 's' || key == 'S')   position_atual.y += qntRotate;

	if (key == 'q' || key == 'Q')   position_atual.z -= qntRotate;
	if (key == 'e' || key == 'E')   position_atual.z += qntRotate;
}