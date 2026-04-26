#ifndef PONTO_H
#define PONTO_H

#include "forma.h"

class Ponto : public Forma
{
private:

public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO)
    {
        p.push_back({x,y});
    }

    void desenhar(QPainter &painter) override
    {
        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        if(!p.empty()){
            Coordenada coorde = p.front();
            painter.drawPoint(coorde.x, coorde.y);
        }
    }
};

#endif // PONTO_H