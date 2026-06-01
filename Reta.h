#ifndef RETA_H
#define RETA_H

#include "forma.h"
#include "Matriz.h"
#include <QDebug>

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

        if( p.size()>=2 ){

            Coordenada p1 = *it;
            it++;
            Coordenada p2 = *it;

            if (( p1.pos | p2.pos ).none() ) {
                // Ambos os pontos estao pra dentro
                painter.drawLine(QLineF( p1.xScn, p1.yScn, p2.xScn, p2.yScn )); // Desenha a reta completa
            }
            else if (( p1.pos & p2.pos ).any() ) {
            }
            else {
                Linha *l = recorte(&p1, &p2, viewport);

                painter.drawLine(QLineF( l->p1.x, l->p1.y, l->p2.x, l->p2.y ));
            }
        }
    }

    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }

    void atualizarCoordenadaScn(const Matriz& m, Janela window) override{
        for( Coordenada& vertice : this->p ){

            Coordenada resultado;
            resultado = m * vertice;

            vertice.xScn = resultado.x;
            vertice.yScn = resultado.y;

            vertice.pos.set( 0, ( vertice.x <= window.getMin().x ));
            vertice.pos.set( 1, ( vertice.x >= window.getMax().x ));

            vertice.pos.set( 2, ( vertice.y <= window.getMin().y ));
            vertice.pos.set( 3, ( vertice.y >= window.getMax().y ));
        }
    }
};

#endif // RETA_H
