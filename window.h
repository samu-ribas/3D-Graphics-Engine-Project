#ifndef WINDOW_H
#define WINDOW_H

//#include <list>
#include <QString>
#include "viewport.h"

class Janela : public Viewport
{
private:
    double angulo;

public:
    Janela( QString nome, double x, double y, double largura, double altura );

    // Getters
    double getAngulo();
};

#endif // WINDOW_H
