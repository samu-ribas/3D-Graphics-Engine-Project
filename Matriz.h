#ifndef MATRIZ_H
#define MATRIZ_H

#include "Forma.h"

class Matriz
{
public:
    double m[3][3];
    Matriz();

    static Matriz gerarMatrizT(double dx, double dy);
    static Matriz gerarMatrizE(double sx, double sy);
    static Matriz gerarMatrizR(double angulo);

    Matriz operator*(const Matriz& outra) const;
    Coordenada operator*(const Coordenada& ponto) const;

};
#endif // MATRIZ_H