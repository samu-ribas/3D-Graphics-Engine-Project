#ifndef PONTO_H
#define PONTO_H

#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y,0.0});
    }



    void desenhar(QPainter &painter, const Matriz& mCam, const Window& win) override {
        if (this->p.empty())
            return;

        Coordenada c = this->p.front();
        Coordenada c_scn = mCam * c;

        if(c_scn.x_wc < -1.0 || c_scn.x_wc > 1.0 || c_scn.y_wc < -1.0 || c_scn.y_wc > 1.0) {
            return;
        }


        double x_vp = (c_scn.x_wc + 1.0) * ((win.getLargura()*win.getZoomViewport()) / 2.0) + (win.getLargura() - (win.getLargura()*win.getZoomViewport())) / 2.0;
        double y_vp = (1.0 - c_scn.y_wc) * ((win.getAltura()*win.getZoomViewport()) / 2.0) + (win.getAltura() - (win.getAltura()*win.getZoomViewport())) / 2.0;

        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);
        painter.drawPoint(x_vp, y_vp);
    }

};
#endif // PONTO_H