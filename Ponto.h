#ifndef PONTO_H
#define PONTO_H

#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y,0.0});
    }

     void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) override {
        if (this->p.empty()) return;

        Coordenada p_cam = mView * this->p.front();

        if (p_cam.z_wc < 1.0) return;

        Coordenada p_proj = mProj * p_cam;

        double sx = (2.0 / win.getLargura()) * zoom;
        double sy = (2.0 / win.getAltura())  * zoom;
        p_proj.x_wc *= sx;
        p_proj.y_wc *= sy;
        p_proj.x_scn = p_proj.x_wc;
        p_proj.y_scn = p_proj.y_wc;


        if (p_proj.x_scn < -1.0 || p_proj.x_scn > 1.0 || p_proj.y_scn < -1.0 || p_proj.y_scn > 1.0) {
            return;
        }

        double x_vp = (p_proj.x_scn + 1.0) * (win.getLargura() / 2.0);
        double y_vp = (1.0 - p_proj.y_scn) * (win.getAltura() / 2.0);

        QPen caneta(Qt::white, 3);
        painter.setPen(caneta);
        painter.drawPoint(QPointF(x_vp, y_vp));
    }
};
#endif // PONTO_H