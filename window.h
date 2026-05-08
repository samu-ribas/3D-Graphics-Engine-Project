#ifndef WINDOW_H
#define WINDOW_H

//#include <list>
#include <QString>
#include "viewport.h"

class Janela : public Viewport
{
public:
    Janela( QString nome, double x, double y, double largura, double altura );

};

#endif // WINDOW_H
