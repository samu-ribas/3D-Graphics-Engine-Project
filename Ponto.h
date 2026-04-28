#ifndef PONTO_H
#define PONTO_H

#include "forma.h"
#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        if(!p.empty()){
            Coordenada coordenada = p.front();
            painter.drawPoint(coordenada.x, coordenada.y);
        }
    }
    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p){
            vertice = m * vertice;
        }
    }
};

#endif // PONTO_H