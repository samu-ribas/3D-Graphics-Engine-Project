#ifndef PONTO_H
#define PONTO_H

#include "forma.h"

class Ponto : public Forma
{
public:
    Ponto(int x, int y);

    void desenhar(QPainter &painter) override;

private:
    int m_x;
    int m_y;
};

#endif // PONTO_H
