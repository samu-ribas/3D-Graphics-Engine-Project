#ifndef RETA_H
#define RETA_H

#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1});
        p.push_back({x2, y2});
    }

    bool verificarClipping(const Window& win) override {
        if(this->p.size() < 2) return false;

        double larg = win.getLargura();
        double alt = win.getAltura();
        double cx = win.getCentro_x();
        double cy = win.getCentro_y();
        double ang = win.getAngulo();

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

        Matriz translacao_inv;
        translacao_inv.m[0][2] = cx;
        translacao_inv.m[1][2] = cy;
        double rad_inv = ang * (M_PI / 180.0);
        Matriz rotacao_inv;
        rotacao_inv.m[0][0] = cos(rad_inv);
        rotacao_inv.m[0][1] = -sin(rad_inv);
        rotacao_inv.m[1][0] = sin(rad_inv);
        rotacao_inv.m[1][1] = cos(rad_inv);
        Matriz camera_para_mundo = translacao_inv * rotacao_inv;

        auto it = this->p.begin();
        Coordenada p1_cam = mundo_para_camera * (*it);
        Coordenada p2_cam = mundo_para_camera * (*(++it));

        double x_min_cam = -larg / 2.0;
        double x_max_cam =  larg / 2.0;
        double y_min_cam = -alt  / 2.0;
        double y_max_cam =  alt  / 2.0;

        // Função local para obter outcode (usando limites da câmera)
        auto getOutcodeCam = [&](const Coordenada& p) -> std::bitset<4> {
            std::bitset<4> code = INSIDE;
            if (p.x_wc < x_min_cam) code |= LEFT;
            else if (p.x_wc > x_max_cam) code |= RIGHT;
            if (p.y_wc < y_min_cam) code |= BASE;
            else if (p.y_wc > y_max_cam) code |= TOP;
            return code;
        };

        std::bitset<4> outcode1 = getOutcodeCam(p1_cam);
        std::bitset<4> outcode2 = getOutcodeCam(p2_cam);
        bool aceito = false;

        while (true) {
            if ((outcode1 | outcode2).none()) {
                aceito = true;
                break;
            }
            if ((outcode1 & outcode2).any()) break;

            std::bitset<4> out_fora = outcode1.any() ? outcode1 : outcode2;
            double x_int = 0.0, y_int = 0.0;
            double m = (p2_cam.y_wc - p1_cam.y_wc) / (p2_cam.x_wc - p1_cam.x_wc);

            if ((out_fora & TOP).any()) {
                x_int = p1_cam.x_wc + (y_max_cam - p1_cam.y_wc) / m;
                y_int = y_max_cam;
            } else if ((out_fora & BASE).any()) {
                x_int = p1_cam.x_wc + (y_min_cam - p1_cam.y_wc) / m;
                y_int = y_min_cam;
            } else if ((out_fora & RIGHT).any()) {
                y_int = m * (x_max_cam - p1_cam.x_wc) + p1_cam.y_wc;
                x_int = x_max_cam;
            } else if ((out_fora & LEFT).any()) {
                y_int = m * (x_min_cam - p1_cam.x_wc) + p1_cam.y_wc;
                x_int = x_min_cam;
            }

            if (out_fora == outcode1) {
                p1_cam.x_wc = x_int;
                p1_cam.y_wc = y_int;
                outcode1 = getOutcodeCam(p1_cam);
            } else {
                p2_cam.x_wc = x_int;
                p2_cam.y_wc = y_int;
                outcode2 = getOutcodeCam(p2_cam);
            }
        }

        if (aceito) {
            this->p1_clip = camera_para_mundo * p1_cam;
            this->p2_clip = camera_para_mundo * p2_cam;
        }
        return aceito;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp, const Window& win) override{
        Coordenada c1_scn = mCam * this->p1_clip;
        Coordenada c2_scn = mCam * this->p2_clip;

        double zoom = win.getZoomViewport();
        double larg_vp_zoom = larg_vp * zoom;
        double alt_vp_zoom  = alt_vp * zoom;
        // Ponto 1
        double x1_vp = (c1_scn.x_wc + 1.0) * (larg_vp_zoom/2.0) + (larg_vp - larg_vp_zoom) / 2.0; //offset centraliza a imagem ampliada dentro da viewport original
        double y1_vp = (1.0 - c1_scn.y_wc) * (alt_vp_zoom / 2.0) + (alt_vp - alt_vp_zoom) / 2.0;

        // Ponto 2
        double x2_vp = (c2_scn.x_wc + 1.0) * (larg_vp_zoom/2.0) + (larg_vp - larg_vp_zoom) / 2.0;
        double y2_vp = (1.0 - c2_scn.y_wc) * (alt_vp_zoom / 2.0) + (alt_vp - alt_vp_zoom) / 2.0;


        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);
        painter.drawLine(QLineF(x1_vp, y1_vp, x2_vp, y2_vp));
    }

private:
    Coordenada p1_clip;
    Coordenada p2_clip;
};

#endif // RETA_H
