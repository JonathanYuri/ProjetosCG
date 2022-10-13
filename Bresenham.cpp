#include <vector>
#include <iostream>

#include "Bresenham.h"

using namespace std;

void reverse_points(vector<pair<int, int>>* pontos, vector<pair<int, int>>* ponto)
{
    for (int i = ponto->size() - 1; i >= 0; i--)
    {
        pontos->push_back(ponto->at(i));
    }
    ponto->clear();
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

    for (unsigned int i = 0; i < points.size(); i++)
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
    float d = (5.0f / 4.0f) - (y * 1.0f);

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
    for (auto p : pontos)   ponto.push_back({ p.second, p.first });
    reverse_points(&pontos, &ponto);

    if (qnt_quadrantes == 1)    return pontos;

    //quarto quadrante, 2 octantes
    for (auto p : pontos)   ponto.push_back({ p.first, -p.second });
    reverse_points(&pontos, &ponto);

    if (qnt_quadrantes == 2)    return pontos;

    // 2 e 3 quadrante
    for (auto p : pontos)   ponto.push_back({ -p.first, p.second });
    reverse_points(&pontos, &ponto);

    return pontos;
}