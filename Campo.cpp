#include "Campo.h"
#include <iostream>

void Campo::draw_bar(int indice)
{
    glPushMatrix();

    if (indice < 6) glTranslatef(posicoes_barras[indice] + (tamanho_barra.x / 2), posicoes_barras[indice + 1], posicoes_barras[indice + 2]);
    else            glTranslatef(posicoes_barras[indice] - (tamanho_barra.x / 2), posicoes_barras[indice + 1], posicoes_barras[indice + 2]);

    glTranslatef(.0f, .0f, (tamanho_barra.z / 2.0f) + (tamanho_campo.z / 2.0f));
    glScalef(tamanho_barra.x, tamanho_barra.y, tamanho_barra.z);
    glutSolidCube(1.0);

    glPopMatrix();
}

void Campo::draw_barT(int indice)
{
    glPushMatrix();

    if (indice < 3) glTranslatef(posicoes_barrasT[indice] + (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], posicoes_barrasT[indice + 2]);
    else            glTranslatef(posicoes_barrasT[indice] - (tamanho_barra.x / 2), posicoes_barrasT[indice + 1], posicoes_barrasT[indice + 2]);

    glTranslatef(.0f, .0f, (tamanho_barra.z / 2.0f) + (tamanho_campo.z / 2.0f) + (tamanho_barra.z / 2.0f));
    glScalef(tamanho_barraT.x, tamanho_barraT.y, tamanho_barraT.z);

    glutSolidCube(1.0);

    glPopMatrix();
}

void Campo::draw_bars()
{
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 11; i += 3)   draw_bar(i);
    for (int i = 0; i < 6; i += 3)    draw_barT(i);
}

void Campo::draw_outlines(GLuint texid)
{
    glBindTexture(GL_TEXTURE_2D, texid);
    glColor3f(color_grid[1][0], color_grid[1][1], color_grid[1][2]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-(tamanho_campo.x / 2) - espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-(tamanho_campo.x / 2), tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(1.0, 5.0);
    glVertex3f(-(tamanho_campo.x / 2), -(tamanho_campo.y / 2) - espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(0.0, 5.0);
    glVertex3f(-(tamanho_campo.x / 2) - espacamento_lateral, -(tamanho_campo.y / 2) - espacamento_lateral, tamanho_campo.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(tamanho_campo.x / 2 + espacamento_lateral, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(1.0, 5.0);
    glVertex3f(tamanho_campo.x / 2 + espacamento_lateral, -(tamanho_campo.y / 2) - espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(0.0, 5.0);
    glVertex3f(tamanho_campo.x / 2, -(tamanho_campo.y / 2) - espacamento_lateral, tamanho_campo.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2 + espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(5.0, 1.0);
    glVertex3f(tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
    glTexCoord2f(5.0, 1.0);
    glVertex3f(tamanho_campo.x / 2, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-tamanho_campo.x / 2, -tamanho_campo.y / 2 - espacamento_lateral, tamanho_campo.z / 2);
    glEnd();
}

void Campo::draw_field(GLuint texid, GLuint texMaisClara)
{
    float division_length = tamanho_campo.x / grid_division_field;

    for (int i = 0; i < grid_division_field; i++)
    {
        if (i % 2 == 0)
        {
            glBindTexture(GL_TEXTURE_2D, texid);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, texMaisClara);
        }

        glColor3f(color_grid[(i % 2)][0], color_grid[(i % 2)][1], color_grid[(i % 2)][2]);

        //frente
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, tamanho_campo.y / 2, tamanho_campo.z / 2);

        glTexCoord2f(1.0, 5.0);
        glVertex3f((division_length * (i + 1)) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glTexCoord2f(0.0, 5.0);
        glVertex3f((division_length * i) - tamanho_campo.x / 2, -tamanho_campo.y / 2, tamanho_campo.z / 2);
        glEnd();
    }

    for (unsigned int i = 0; i < faces_campo.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(faces_campo[i], faces_campo[i + 1], faces_campo[i + 2]);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(faces_campo[i + 3], faces_campo[i + 4], faces_campo[i + 5]);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(faces_campo[i + 6], faces_campo[i + 7], faces_campo[i + 8]);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(faces_campo[i + 9], faces_campo[i + 10], faces_campo[i + 11]);
        glEnd();
    }

    draw_outlines(texid);
    draw_bars();
}

/* Arquibancada */

void Campo::draw_layer(vector<float> vertices, float offset_x, float offset_y, GLuint texid)
{
    glBindTexture(GL_TEXTURE_2D, texid);
    for (unsigned int i = 0; i < vertices.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        if (i == 0) // para frente
        {
            glNormal3f(1, 0, 0);
            glColor3f(1.0f, 1.0f, .0f);
            glTexCoord2f(0.0, 0.0);

            glVertex3f(vertices[i] + offset_x, vertices[i + 1] - offset_y, vertices[i + 2]);

            glNormal3f(1, 0, 0);
            glTexCoord2f(1.0, 0.0);

            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

            glNormal3f(1, 0, 0);
            glTexCoord2f(1.0, 1.0);

            glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);

            glNormal3f(1, 0, 0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9] + offset_x, vertices[i + 10] - offset_y, vertices[i + 11]);
        }
        else if (i == 24 || i == 36) // cima ou baixo
        {
            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);

            glColor3f(.0f, .0f, 1.0f);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] - offset_y, vertices[i + 8]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 48 || i == 60) // esquerda ou direita
        {
            if (i == 48)    glNormal3f(0, 1, 0);
            else    glNormal3f(0, -1, 0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            if (i == 48)
            {
                glNormal3f(0, 1, 0);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] - offset_y, vertices[i + 5]);

                glNormal3f(0, 1, 0);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] - offset_y, vertices[i + 8]);
            }
            else
            {
                glNormal3f(0, -1, 0);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

                glNormal3f(0, -1, 0);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }

            if (i == 48)    glNormal3f(0, 1, 0);
            else    glNormal3f(0, -1, 0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 12) // tras
        {
            glNormal3f(-1, 0, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);

            glNormal3f(-1, 0, 0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);

            glNormal3f(-1, 0, 0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

            glNormal3f(-1, 0, 0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        glEnd();
    }
}

void Campo::draw_layer2(vector<float> vertices, float offset_x, float offset_y, GLuint texid)
{
    glBindTexture(GL_TEXTURE_2D, texid);

    for (unsigned int i = 0; i < vertices.size(); i += 12)
    {
        glBegin(GL_POLYGON);
        if (i == 0) // para frente
        {
            glColor3f(1.0f, 1.0f, .0f);

            glNormal3f(0, 1, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(vertices[i] + offset_x, vertices[i + 1] + offset_y, vertices[i + 2]);

            glNormal3f(0, 1, 0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(vertices[i + 3] - offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

            glNormal3f(0, 1, 0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(vertices[i + 6] - offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);

            glNormal3f(0, 1, 0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9] + offset_x, vertices[i + 10] + offset_y, vertices[i + 11]);
        }
        else if (i == 24 || i == 36) // cima ou baixo
        {
            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);

            glColor3f(.0f, .0f, 1.0f);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(vertices[i] - offset_x, vertices[i + 1] + offset_y, vertices[i + 2]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

            if (i == 24)    glNormal3f(0, 0, 1);
            else    glNormal3f(0, 0, -1);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 48 || i == 60) // esquerda ou direita
        {
            if (i == 48)    glNormal3f(1, 1, 0);
            else    glNormal3f(-1, 1, 0);

            //glColor3f(.0, 1.0, 1.0);
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            if (i == 48)
            {
                glNormal3f(1, 1, 0);
                glVertex3f(vertices[i + 3] + offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

                glNormal3f(1, 1, 0);
                glVertex3f(vertices[i + 6] + offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }
            else
            {
                //glColor3f(1.0, .0, 1.0);
                glNormal3f(-1, 1, 0);
                glVertex3f(vertices[i + 3] - offset_x, vertices[i + 4] + offset_y, vertices[i + 5]);

                glNormal3f(-1, 1, 0);
                glVertex3f(vertices[i + 6] - offset_x, vertices[i + 7] + offset_y, vertices[i + 8]);
            }

            if (i == 48)    glNormal3f(1, 1, 0);
            else    glNormal3f(-1, 1, 0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        else if (i == 12) // tras
        {
            glNormal3f(0, -1, 0);
            //glColor3f(1.0, 1.0, 1.0);

            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);

            glNormal3f(0, -1, 0);
            glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);

            glNormal3f(0, -1, 0);
            glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

            glNormal3f(0, -1, 0);
            glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
        }
        glEnd();
    }
}

void Campo::draw_bench(bool cima, GLuint texID[])
{
    int niveis = 7;
    float espaco_arquibancada = 0.05;

    float offset_x = .0f, offset_y = .0f;

    glColor3f(.0, .0, 1.0);
    glPushMatrix();
    for (int i = 0; i < niveis; i++, offset_x += espaco_arquibancada, offset_y += (larguraDegrau * espaco_arquibancada) / larguraArquibancada)
    {
        //if (i % 2 == 0)     glColor3f(1.0, 1.0, 1.0);
        //else    glColor3f(1.0f, 1.0f, 1.0f);

        if (i != 0)     glTranslatef(.0, .0, tamanho_campo.z);

        if (!cima)
        {
            glEnable(GL_TEXTURE_2D);
            draw_layer(vertices_arquibancada, -offset_x, offset_y, texID[1]);
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            glEnable(GL_TEXTURE_2D);
            draw_layer2(vertices_arquibancada2, offset_y, -offset_x, texID[1]);
            glDisable(GL_TEXTURE_2D);
        }
    }
    glPopMatrix();
}

void Campo::draw_stadium(GLuint texID[])
{
    // esquerda
    draw_bench(false, texID);

    // direita
    glPushMatrix();
    glScalef(-1, 1, 1); // espelhar
    draw_bench(false, texID);
    glPopMatrix();

    // baixo
    draw_bench(true, texID);

    // cima
    glPushMatrix();
    glScalef(1, -1, 1); // espelhar
    draw_bench(true, texID);
    glPopMatrix();
}