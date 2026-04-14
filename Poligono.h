#ifndef POLIGONO_H
#define POLIGONO_H
#include "forma.h"

class Poligono : public Forma{

public:
    Poligono(QString n, std::list<Coordenada> vertices): Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);

        if(p.size()<2) return;

        auto it = p.begin();
        auto next = std::next(it);

        while(next != p.end()){
            painter.drawLine(QLineF(it->x, it->y, next->x, next->y));
            it++;
            next++;
        }
        Coordenada primeiro = p.front();
        Coordenada ultimo = p.back();
        painter.drawLine(QLineF(ultimo.x, ultimo.y, primeiro.x, primeiro.y));
    }

};

#endif // POLIGONO_H
