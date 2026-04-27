#include "matriz.h"
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

Matriz Matriz::gerarMatrizTranslacao( double dx, double dy )
{
    Matriz translacao = Matriz();
    translacao.m[2][0] = dx;
    translacao.m[2][1] = dy;

    return translacao;
}

Matriz Matriz::gerarMatrizEscala( double sx, double sy )
{
    Matriz escala = Matriz();
    escala.m[0][0] = sx;
    escala.m[1][1] = sy;

    return escala;
}

Matriz Matriz::gerarMatrizRotacao( double angulo )
{
    double rad = angulo * M_PI / 180;
    Matriz rotacao = Matriz();
    rotacao.m[0][0] = std::cos(rad);
    rotacao.m[0][1] = -std::sin(rad);
    rotacao.m[1][0] = std::sin(rad);
    rotacao.m[1][1] = std::cos(rad);


    return rotacao;
}

Matriz Matriz::multiplicar( Matriz m1, Matriz m2 )
{
    Matriz resultado;

    double soma;
    for ( int i = 0; i < 3; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            soma = 0.0;
            for ( int k = 0; k < 3; k++ )
            {
                soma += m1.m[i][k] * m2.m[k][j];
            }
            resultado.m[i][j] = soma;
        }
    }

    return resultado;
}

void Matriz::imprimir()
{
    for ( int i = 0; i < 3; i++ )
    {
        qDebug() << m[0][i] << m[1][i] << m[2][i];
    }
}