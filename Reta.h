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

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 1);
        painter.setPen(caneta);
        auto it = p.begin();
        if( p.size()>=2 ){

            Coordenada p1 = *it;
            it++;
            Coordenada p2 = *it;

            if ( ( p1.pos.any() && p2.pos.any() )) // Ambas para fora
                return;

            if ( p1.pos.none() && p1.pos.none() )
                painter.drawLine(QLineF( p1.xScn, p1.yScn, p2.xScn, p2.yScn ));
            //else ()
        }
    }

    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }

    void atualizarCoordenadaScn(const Matriz& m, Viewport viewport) override{
        for(Coordenada& vertice : this->p){
            Coordenada resultado;
            resultado = m * vertice;

            vertice.xScn = resultado.x;
            vertice.yScn = resultado.y;

            vertice.pos.set( 0, vertice.xScn < viewport.getMin().x );
            vertice.pos.set( 1, vertice.xScn > viewport.getMax().x );

            vertice.pos.set( 2, vertice.yScn < viewport.getMin().y );
            vertice.pos.set( 3, vertice.yScn > viewport.getMax().y );
        }
    }
};

#endif // RETA_H
