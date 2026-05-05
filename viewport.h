#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <list>
#include "coordenada.h"

class Viewport
{
private:
    std::list<Coordenada> listaPonto;

public:
    Viewport( double largura, double altura )
    {
        listaPonto.push_back({0.0    , 0.0});
        listaPonto.push_back({largura, 0.0});
        listaPonto.push_back({0.0    , altura});
        listaPonto.push_back({largura, altura});
    }

    Coordenada getMin() {
        return listaPonto.front();
    }

    Coordenada getMax() {
        return listaPonto.back();
    }
};

#endif // VIEWPORT_H
