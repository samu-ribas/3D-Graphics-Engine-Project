#ifndef RETA_H
#define RETA_H

#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1, 0.0});
        p.push_back({x2, y2, 0.0});
    }

    void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) override {
        if (this->p.size() < 2) return;

        auto it = p.begin();
        Coordenada p1 = mView * (*it);
        Coordenada p2 = mView * (*(++it));

        double z_near = 1.0;
        if (!clipNearPlane(p1, p2, z_near)) return;

        p1 = mProj * p1;
        p2 = mProj * p2;

        // Aplicar escala + zoom (AGORA)
        double sx = (2.0 / win.getLargura()) * zoom;
        double sy = (2.0 / win.getAltura())  * zoom;
        p1.x_wc *= sx; p1.y_wc *= sy;
        p2.x_wc *= sx; p2.y_wc *= sy;

        // Copiar para x_scn/y_scn (por compatibilidade, mas não use)
        p1.x_scn = p1.x_wc; p1.y_scn = p1.y_wc;
        p2.x_scn = p2.x_wc; p2.y_scn = p2.y_wc;

        LimitesSCN limites = Viewport::getLimitesSCN();
        if (cohenSutherland(p1, p2, limites)) {
            double x1_vp = (p1.x_wc + 1.0) * (win.getLargura() / 2.0);
            double y1_vp = (1.0 - p1.y_wc) * (win.getAltura() / 2.0);
            double x2_vp = (p2.x_wc + 1.0) * (win.getLargura() / 2.0);
            double y2_vp = (1.0 - p2.y_wc) * (win.getAltura() / 2.0);
            painter.drawLine(QPointF(x1_vp, y1_vp), QPointF(x2_vp, y2_vp));
        }
    }

};

#endif // RETA_H
