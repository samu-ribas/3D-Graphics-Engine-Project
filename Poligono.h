#ifndef POLIGONO_H
#define POLIGONO_H

#include "forma.h"
#include "Matriz.h"

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
        painter.drawLine(QLineF(ultimo.xScn, ultimo.yScn, primeiro.xScn, primeiro.yScn));
    }

    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }

    void atualizarCoordenadaScn(const Matriz& m) override{
        auto pontoScn = p.begin();
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
            pontoScn++;
        }
    }
};

#endif // POLIGONO_H
