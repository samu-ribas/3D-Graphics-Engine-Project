#ifndef POLIGONO_H
#define POLIGONO_H

#include "forma.h"
#include "Matriz.h"

class Poligono : public Forma{

public:
    Poligono(QString n, std::list<Coordenada> vertices): Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    void desenhar(QPainter &painter, int largura_vp, int altura_vp) override{
        if(this->p.size()<3) return;

        QVector<QPointF> pontos_vp;

        for(const Coordenada& c : this->p){
            double x_vp = ((c.x_scn - (-1.0)) / 2.0) * largura_vp;
            double y_vp = (1.0 - ((c.y_scn - (-1.0)) / 2.0)) * altura_vp;

            pontos_vp.append(QPointF(x_vp, y_vp));
        }

        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);

        for(int i = 0 ; i < pontos_vp.size() - 1 ; i++)
            painter.drawLine(QLineF(pontos_vp[i], pontos_vp[i + 1]));

        painter.drawLine(QLineF(pontos_vp.last(), pontos_vp.first()));
    }

    void aplicarTransformacao(const Matriz& m) override{
        for(Coordenada& vertice : this->p)
            vertice = m * vertice;
    }
};
#endif // POLIGONO_H
