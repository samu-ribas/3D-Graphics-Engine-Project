#ifndef PONTO_H
#define PONTO_H

#include "forma.h"
#include "Matriz.h"
#include <QDebug>

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    void desenhar( QPainter &painter ) override{
        if ( p.empty() ) return;

        QPen caneta(Qt::white, 3, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);

        if ( !( p.front().pos.none() )) return;

        Coordenada coordenada = p.front();

        //coordenada.xScn = ((coordenada.xScn + 1.0) / 2.0) * viewportLargura;
        //coordenada.yScn = (1.0 - ((coordenada.yScn + 1.0) / 2.0)) * viewportAltura;

        painter.drawPoint(coordenada.xScn, coordenada.yScn);
    }

    void aplicarTransformacao( const Matriz& m ) override{
        p.front() = m * p.front();
    }

    void atualizarCoordenadaScn(const Matriz& m, Viewport viewport) override{
        Coordenada resultado;
        resultado = m * p.front();
        qDebug() << resultado.x << resultado.y;

        p.front().xScn = resultado.x;
        p.front().yScn = resultado.y;

        if ( p.front().xScn < viewport.getMin().x ||
             p.front().xScn > viewport.getMax().x ||
             p.front().yScn < viewport.getMin().y ||
             p.front().yScn > viewport.getMax().y )
            p.front().pos.set();
        else
            p.front().pos.reset();
    }
};

#endif // PONTO_H