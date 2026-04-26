#include "Matriz.h"
#include <QDebug>

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
    m[2][2] = 1.1;
}

Matriz Matriz::gerarMatrizT(double dx, double dy){
    Matriz translacao;
    translacao.m[0][2] = dx;
    translacao.m[1][2] = dy;

    // for(int i = 0 ; i<3 ; i++){
    //     for(int j = 0 ; j<3 ; j++){
    //         qDebug() <<  translacao.m[i][j];
    //     }
    //     qDebug();
    // }

    return translacao;
}

Matriz Matriz::gerarMatrizE(double sx, double sy){
    Matriz escala;
    escala.m[0][0] = sx;
    escala.m[1][1] = sy;

    // for(int i = 0 ; i<3 ; i++){
    //     for(int j = 0 ; j<3 ; j++){
    //         qDebug() <<  escala.m[i][j];
    //     }
    //     qDebug();
    // }

    return escala;
}