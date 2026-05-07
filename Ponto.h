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

    void desenhar(QPainter &painter) override{
        if (p.empty()) return;

        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);

        Coordenada coordenada = p.front();

        //coordenada.xScn = ((coordenada.xScn + 1.0) / 2.0) * viewportLargura;
        //coordenada.yScn = (1.0 - ((coordenada.yScn + 1.0) / 2.0)) * viewportAltura;

        painter.drawPoint(coordenada.xScn, coordenada.yScn);
    }

    void aplicarTransformacao(const Matriz& m, const Matriz& m2) override{
        p.front() = m * p.front();

        atualizarCoordenadaScn( m2 );
    }

    void atualizarCoordenadaScn(const Matriz& m) override{
        Coordenada resultado;
        resultado = m * p.front();
        qDebug() << resultado.x << resultado.y;
        p.front().xScn = resultado.x;
        p.front().yScn = resultado.y;
    }
};

#endif // PONTO_H