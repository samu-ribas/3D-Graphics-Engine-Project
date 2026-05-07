#ifndef MATRIZ_H
#define MATRIZ_H

#include "coordenada.h"

class Matriz
{
public:
    double m[3][3];
    Matriz();

    static Matriz gerarMatrizT(double dx, double dy);
    static Matriz gerarMatrizT(Coordenada cod);

    static Matriz gerarMatrizE(double sx, double sy);

    static Matriz gerarMatrizR(double angulo);

    //sobrecarga de operador para multiplicar matriz
    Matriz operator*(const Matriz& outra) const;
    Coordenada operator*(const Coordenada& ponto) const;

    void imprimir();
};

#endif // MATRIZ_H