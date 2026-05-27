#ifndef PONTO_H
#define PONTO_H

#include "forma.h"
//#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    void desenhar(QPainter &painter, int largura_vp, int altura_vp) override{
        if(this->p.empty()) return;

        const Coordenada& c = this->p.front();
        double x_vp = ((c.x_scn - (-1.0)) / 2.0) * largura_vp;
        double y_vp = (1.0 - ((c.y_scn - (-1.0)) / 2.0)) * altura_vp;

        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        painter.drawPoint(QPointF(x_vp, y_vp));
    }

    // void aplicarTransformacao(const Matriz& m) override{
    //     for(Coordenada& vertice : this->p)
    //         vertice = m * vertice;
    // }
};
#endif // PONTO_H