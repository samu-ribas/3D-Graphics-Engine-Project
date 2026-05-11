#ifndef POLIGONO_H
#define POLIGONO_H

#include "forma.h"
#include "Matriz.h"

class Poligono : public Forma{

public:
    Poligono(QString n, std::list<Coordenada> vertices): Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    void desenhar(QPainter &painter, Viewport viewport) override{
        QPen caneta(Qt::white, 1);
        painter.setPen(caneta);

        if(p.size()<2) return;

        auto it = p.begin();
        auto next = std::next(it);

        while(next != p.end()){
            painter.drawLine(QLineF(it->xScn, it->yScn, next->xScn, next->yScn));
            it++;
            next++;
        }
        Coordenada primeiro = p.front();
        Coordenada ultimo = p.back();
        painter.drawLine(QLineF(ultimo.xScn, ultimo.yScn, primeiro.xScn, primeiro.yScn));
    }

    void aplicarTransformacao(const Matriz& m, const Matriz& m2) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }

        atualizarCoordenadaScn( m2 );
    }

    void atualizarCoordenadaScn(const Matriz& m) override{

        for(Coordenada& vertice : this->p){
            Coordenada resultado;
            resultado = m * vertice;

            vertice.xScn = resultado.x;
            vertice.yScn = resultado.y;
        }
    }
};

#endif // POLIGONO_H
