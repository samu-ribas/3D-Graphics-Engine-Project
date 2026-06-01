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

        if(p.size()<2) return;

        auto it = p.begin();
        auto next = std::next(it);

        while(next != p.end()){

            Coordenada p1 = *it;
            Coordenada p2 = *next;

            if (( it->pos | next->pos ).none() ) {
                // Ambos os pontos estao pra dentro
                QPen caneta(Qt::white, 1);
                painter.setPen(caneta);
                painter.drawLine(QLineF( it->xScn, it->yScn, next->xScn, next->yScn )); // Desenha a reta completa
            }
            else if (( it->pos & next->pos ).any() ) {
                //QPen caneta(Qt::yellow, 1);
                //painter.setPen(caneta);
                //painter.drawLine(QLineF( it->xScn, it->yScn, next->xScn, next->yScn ));
            }
            else {
                Linha *l = recorte(&p1, &p2, viewport);
                if (l != nullptr) {
                    QPen caneta(Qt::white, 1);
                    painter.setPen(caneta);
                    painter.drawLine(QLineF( l->p1.x, l->p1.y, l->p2.x, l->p2.y ));
                }
                else {
                    //QPen caneta(Qt::red, 1);
                    //painter.setPen(caneta);
                    //painter.drawLine(QLineF( it->xScn, it->yScn, next->xScn, next->yScn ));
                }
            }

            it++;
            next++;
        }
        Coordenada primeiro = p.front();
        Coordenada ultimo = p.back();
        if (( primeiro.pos | ultimo.pos ).none() ) {
            // Ambos os pontos estao pra dentro
            QPen caneta(Qt::white, 1);
            painter.setPen(caneta);
            painter.drawLine(QLineF( primeiro.xScn, primeiro.yScn, ultimo.xScn, ultimo.yScn )); // Desenha a reta completa
        }
        else if (( primeiro.pos & ultimo.pos ).any() ) {
            //QPen caneta(Qt::yellow, 1);
            //painter.setPen(caneta);
            //painter.drawLine(QLineF( primeiro.xScn, primeiro.yScn, ultimo.xScn, ultimo.yScn ));
        }
        else {

            Linha *l = recorte(&primeiro, &ultimo, viewport);
            if (l != nullptr) {
                QPen caneta(Qt::white, 1);
                painter.setPen(caneta);
                painter.drawLine(QLineF( l->p1.x, l->p1.y, l->p2.x, l->p2.y ));
            }
            else {
                //QPen caneta(Qt::red, 1);
                //painter.setPen(caneta);
                //painter.drawLine(QLineF( primeiro.xScn, primeiro.yScn, ultimo.xScn, ultimo.yScn ));
            }

        }
        //painter.drawLine(QLineF(ultimo.xScn, ultimo.yScn, primeiro.xScn, primeiro.yScn));
    }

    void aplicarTransformacao( const Matriz& m ) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }

    void atualizarCoordenadaScn( const Matriz& m, Janela window ) override{

        for(Coordenada& vertice : this->p){
            Coordenada resultado;
            resultado = m * vertice;

            vertice.xScn = resultado.x;
            vertice.yScn = resultado.y;

            vertice.pos.set( 0, ( vertice.x < window.getMin().x ));
            vertice.pos.set( 1, ( vertice.x > window.getMax().x ));

            vertice.pos.set( 2, ( vertice.y < window.getMin().y ));
            vertice.pos.set( 3, ( vertice.y > window.getMax().y ));
        }
    }
};

#endif // POLIGONO_H
