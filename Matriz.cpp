#include "Matriz.h"
#include <cmath>

Matriz::Matriz()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

Matriz Matriz::gerarMatrizT(double dx, double dy, double dz){ // transalação
    Matriz translacao;
    translacao.m[0][2] = dx;
    translacao.m[1][2] = dy;
    translacao.m[2][3] = dz;
    return translacao;
}

Matriz Matriz::gerarMatrizE(double sx, double sy, double sz){ // escala
    Matriz escala;
    escala.m[0][0] = sx;
    escala.m[1][1] = sy;
    escala.m[2][3] = sz;
    return escala;
}

Matriz Matriz::gerarMatrizRx(double angulo){ // rotação x
    Matriz rotacao;
    double rad = angulo * (M_PI/180);
    rotacao.m[1][1] = cos(rad);
    rotacao.m[1][2] = -sin(rad);
    rotacao.m[2][1] = sin(rad);
    rotacao.m[2][2] = cos(rad);

    return rotacao;
}

Matriz Matriz::gerarMatrizRy(double angulo){ // rotação y
    Matriz rotacao;
    double rad = angulo * (M_PI/180);
    rotacao.m[0][0] = cos(rad);
    rotacao.m[0][2] = sin(rad);
    rotacao.m[2][0] = -sin(rad);
    rotacao.m[2][2] = cos(rad);

    return rotacao;
}

Matriz Matriz::gerarMatrizRz(double angulo){ // rotação z
    Matriz rotacao;
    double rad = angulo * (M_PI/180);
    rotacao.m[0][0] = cos(rad);
    rotacao.m[0][1] = -sin(rad);
    rotacao.m[1][0] = sin(rad);
    rotacao.m[1][1] = cos(rad);

    return rotacao;
}

Matriz Matriz::operator*(const Matriz& m2) const{
    Matriz resultado;
    double soma;
    for(int i = 0 ; i<4 ; i++){
        for(int j = 0 ; j<4 ; j++){
            soma = 0.0;
            for(int k = 0 ; k<4 ; k++){
                soma += this->m[i][k] * m2.m[k][j];
            }
            resultado.m[i][j] = soma;
        }
    }
    return resultado;
}

Coordenada Matriz::operator*(const Coordenada& ponto) const{
    Coordenada resultado;
    //matriz 4x4 por vetor coluna (x, y, z, 1)
    resultado.x_wc = (this->m[0][0] * ponto.x_wc) + (this->m[0][1] * ponto.y_wc) + (this->m[0][2] * ponto.z_wc) + (this->m[0][3] * 1.0);
    resultado.y_wc = (this->m[1][0] * ponto.x_wc) + (this->m[1][1] * ponto.y_wc) + (this->m[1][2] * ponto.z_wc) + (this->m[1][3] * 1.0);
    resultado.z_wc = (this->m[2][0] * ponto.x_wc) + (this->m[2][1] * ponto.y_wc) + (this->m[2][2] * ponto.z_wc) + (this->m[2][3] * 1.0);
    return resultado;
}