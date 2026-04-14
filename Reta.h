#ifndef RETA_H
#define RETA_H

#include "forma.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA), x(x1),y(y1),xL(x2),yL(y2)
    {
        p.push_back({x1, y1});
        p.push_back({x2, y2});
    }

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        painter.drawLine(x, y, xL, yL);
        painter.drawLine(QLineF(x, y, xL, yL));
    }

private:
    double x;
    double y;
    double xL;
    double yL;
};

#endif // RETA_H
