#pragma once

#include <vector>

using namespace std;

void reverse_points(vector<pair<int, int>>* pontos, vector<pair<int, int>>* ponto);

vector<pair<int, int>> Bresenham_lines(int xI, int yI, int xF, int yF);

vector<pair<int, int>> TraceLine(int xI, int yI, int xF, int yF);

vector<pair<int, int>> Bresenham_circles(int raio, int qnt_quadrantes);