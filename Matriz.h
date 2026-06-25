#ifndef MATRIZ_H
#define MATRIZ_H

#include "Forma.h"

class Matriz
{
public:
    double m[4][4];
    Matriz();

    static Matriz gerarMatrizT(double dx, double dy, double dz);
    static Matriz gerarMatrizE(double sx, double sy, double sz);

    static Matriz gerarMatrizRx(double angulo);
    static Matriz gerarMatrizRy(double angulo);
    static Matriz gerarMatrizRz(double angulo);

    static Matriz gerarMatrizPerspectiva(double d);

    Matriz operator*(const Matriz& m2) const;
    Coordenada operator*(const Coordenada& ponto) const;

};
#endif // MATRIZ_H