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
    double angulo;

public:
    Viewport( QString nome, double x, double y, double largura, double altura );
    Viewport( QString nome, double x, double y, double largura, double altura, double angulo );

    // Getters
    Coordenada getCentro();
    double getAltura();
    double getLargura();
    Coordenada getMin();
    Coordenada getMax();
    QString getNome();
    double getAngulo();

    // Setters
    void setCentro( Coordenada centro );
    void setAltura( double altura );
    void setLargura( double largura );
    void setAngulo( double angulo );

};

#endif // VIEWPORT_H
