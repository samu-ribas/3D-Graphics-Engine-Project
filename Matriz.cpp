#include "Matriz.h"
#include <QDebug>
#include <cmath>

Matriz::Matriz()
{
    //matriz identidade
    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = 0.0;
    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = 0.0;
    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;
}

Matriz Matriz::gerarMatrizT(double dx, double dy){ // transalação
    Matriz translacao;
    translacao.m[0][2] = dx;
    translacao.m[1][2] = dy;
    return translacao;
}

Matriz Matriz::gerarMatrizT(Coordenada cod){ // transalação
    Matriz translacao;
    translacao.m[0][2] = cod.x;
    translacao.m[1][2] = cod.y;
    return translacao;
}

Matriz Matriz::gerarMatrizE(double sx, double sy){ // escala
    Matriz escala;
    escala.m[0][0] = sx;
    escala.m[1][1] = sy;

    return escala;
}

Matriz Matriz::gerarMatrizR(double angulo){ // rotação
    Matriz rotacao;
    double radianos = angulo * (M_PI/180);
    rotacao.m[0][0] = cos(radianos);
    rotacao.m[0][1] = -sin(radianos);
    rotacao.m[1][0] = sin(radianos);
    rotacao.m[1][1] = cos(radianos);

    return rotacao;
}


Matriz Matriz::operator*(const Matriz& m2) const{
    Matriz resultado;
    double soma;
    for(int i = 0 ; i<3 ; i++){
        for(int j = 0 ; j<3 ; j++){
            soma = 0.0;
            for(int k = 0 ; k<3 ; k++){
                soma += this->m[i][k] * m2.m[k][j];
            }
            resultado.m[i][j] = soma;
        }
    }
    return resultado;
}

Coordenada Matriz::operator*(const Coordenada& ponto) const{
    Coordenada resultado = {0.0, 0.0};
    resultado.x = (this->m[0][0] * ponto.x) + (this->m[0][1] * ponto.y) + (this->m[0][2]);
    resultado.y = (this->m[1][0] * ponto.x) + (this->m[1][1] * ponto.y) + (this->m[1][2]);
    return resultado;
}

void Matriz::imprimir()
{
    qDebug() << "Imprimindo Matriz";
    for (int i = 0; i < 3; ++i)
    {
        qDebug() << this->m[i][0] << this->m[i][1] << this->m[i][2];
    }
}