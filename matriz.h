#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz
{
private:


public:
    double m[3][3];

    Matriz();

    static Matriz gerarMatrizTranslacao( double dx, double dy );
    static Matriz gerarMatrizEscala( double sx, double sy );
    static Matriz gerarMatrizRotacao( double angulo );

    static Matriz multiplicar( Matriz m1, Matriz m2 );
    static void multiplicarVM( double v[3], Matriz m );

    void imprimir();
};

#endif // MATRIZ_H
