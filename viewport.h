#ifndef VIEWPORT_H
#define VIEWPORT_H

//#include <list>
#include <QString>
#include "coordenada.h"

class Viewport
{
protected:
    QString nome;
    Coordenada centro = {0.0, 0.0};
    double largura;
    double altura;

public:
    Viewport( QString nome, double x, double y, double largura, double altura );

    // Getters
    Coordenada getCentro();
    double getAltura();
    double getLargura();
    Coordenada getMin();
    Coordenada getMax();
    QString getNome();
};

#endif // VIEWPORT_H
