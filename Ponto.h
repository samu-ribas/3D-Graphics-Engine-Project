#ifndef PONTO_H
#define PONTO_H

#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    bool verificarClipping(const Window& win) override {
        if (this->p.empty()) return false;

        double larg = win.getLargura();
        double alt = win.getAltura();
        double cx = win.getCentro_x();
        double cy = win.getCentro_y();
        double ang = win.getAngulo();

        // Matriz mundo -> câmera
        Matriz translacao;
        translacao.m[0][2] = -cx;
        translacao.m[1][2] = -cy;
        double rad = -ang * (M_PI / 180.0);
        Matriz rotacao;
        rotacao.m[0][0] = cos(rad);
        rotacao.m[0][1] = -sin(rad);
        rotacao.m[1][0] = sin(rad);
        rotacao.m[1][1] = cos(rad);
        Matriz mundo_para_camera = rotacao * translacao;

        Coordenada c_cam = mundo_para_camera * this->p.front();

        double x_min_cam = -larg / 2.0;
        double x_max_cam = larg / 2.0;
        double y_min_cam = -alt / 2.0;
        double y_max_cam = alt / 2.0;

        return (c_cam.x_wc >= x_min_cam && c_cam.x_wc <= x_max_cam &&
                c_cam.y_wc >= y_min_cam && c_cam.y_wc <= y_max_cam);
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp,  const Window& win) override{
        if (this->p.empty()) return;
        Coordenada c = this->p.front();
        Coordenada c_scn = mCam * c;

        double zoom = win.getZoomViewport(); // você precisa passar a Window ou acessar via this? Veja abaixo.
        double larg_vp_zoom = larg_vp * zoom;
        double alt_vp_zoom  = alt_vp * zoom;
        double x_vp = (c_scn.x_wc + 1.0) * (larg_vp_zoom / 2.0) + (larg_vp - larg_vp_zoom) / 2.0;
        double y_vp = (1.0 - c_scn.y_wc) * (alt_vp_zoom / 2.0) + (alt_vp - alt_vp_zoom) / 2.0;

        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);
        painter.drawPoint(x_vp, y_vp);
    }

};
#endif // PONTO_H