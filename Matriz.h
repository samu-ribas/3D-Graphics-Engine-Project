#ifndef MATRIZ_H
#define MATRIZ_H

// #include "forma.h"

class Matriz
{
public:
    double m[3][3];
    Matriz();

    static Matriz gerarMatrizT(double dx, double dy);
    static Matriz gerarMatrizE(double sx, double sy);

};

#endif // MATRIZ_H