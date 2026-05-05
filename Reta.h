#ifndef RETA_H
#define RETA_H

#include "forma.h"
#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA)
    {
        p.push_back({x1, y1});
        p.push_back({x2, y2});

        listaCodScn.push_back({0.0, 0.0});
        listaCodScn.push_back({0.0, 0.0});
    }

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        auto it = p.begin();
        if(p.size()>=2){
            Coordenada p1 = *it;
            it++;
            Coordenada p2 = *it;
            painter.drawLine(QLineF(p1.x, p1.y, p2.x, p2.y));
        }
    }

    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }

    void atualizarCoordenadaScn(const Matriz& m) override{
        auto scn = listaCodScn.begin();
        for(Coordenada& vertice : this->p){
            *scn = m * vertice;
            scn++;
        }
    }
};

#endif // RETA_H
