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
    }

    void desenhar(QPainter &painter, Viewport viewport) override{
        QPen caneta(Qt::white, 1);
        painter.setPen(caneta);
        auto it = p.begin();
        if(p.size()>=2){
            Coordenada p1 = *it;
            it++;
            Coordenada p2 = *it;
            painter.drawLine(QLineF(p1.xScn, p1.yScn, p2.xScn, p2.yScn));
        }
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

#endif // RETA_H
