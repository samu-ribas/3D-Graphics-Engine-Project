#ifndef JANELA_H
#define JANELA_H

#include <list>
#include "coordenada.h"

class Janela
{
private:
    std::list<Coordenada> listaPonto;
public:

    Janela( double x, double y, double largura, double altura );

    Coordenada getMin();
    Coordenada getMax();
};

#endif // JANELA_H
