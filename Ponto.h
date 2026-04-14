
#ifndef PONTO_H
#define PONTO_H

#include "forma.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO), x(x), y(y){}

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        painter.drawPoint(x, y);
    }

private:
    double x;
    double y;
};

#endif // PONTO_H