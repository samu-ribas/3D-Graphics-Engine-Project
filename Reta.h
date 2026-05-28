#ifndef RETA_H
#define RETA_H
#include "Forma.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1});
        p.push_back({x2, y2});
    }

    bool verificarClipping(const Window& win) override{
        return true;
    }

    void desenhar(QPainter &painter, int largura_vp, int altura_vp) override{
        if (this->p.size() < 2) return;

        auto it = this->p.begin();
        const Coordenada& p1 = *it;
        const Coordenada& p2 = *++it;

        //viewport Ponto 1
        double x1_vp = ((p1.x_scn + 1.0) / 2.0) * largura_vp;
        double y1_vp = (1.0 - ((p1.y_scn + 1.0) / 2.0)) * altura_vp;
        //viewport Ponto 2
        double x2_vp = ((p2.x_scn + 1.0) / 2.0) * largura_vp;
        double y2_vp = (1.0 - ((p2.y_scn + 1.0) / 2.0)) * altura_vp;

        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        painter.drawLine(x1_vp, y1_vp, x2_vp, y2_vp);
    }

};

#endif // RETA_H
