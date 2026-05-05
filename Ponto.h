#ifndef PONTO_H
#define PONTO_H

#include "forma.h"
#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
        listaCodScn.push_back({0.0, 0.0});
    }

    void desenhar(QPainter &painter) override{
        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        if(!listaCodScn.empty()){
            Coordenada coordenada = listaCodScn.front();
            painter.drawPoint(coordenada.x, coordenada.y);
        }
    }

    void aplicarTransformacao(const Matriz& m) override{
        p.front() = m * p.front();
    }

    void atualizarCoordenadaScn(const Matriz& m) override{
        listaCodScn.front() = m * p.front();
    }
};

#endif // PONTO_H