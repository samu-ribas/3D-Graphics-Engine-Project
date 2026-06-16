#ifndef RETA_H
#define RETA_H

#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1, 0.0});
        p.push_back({x2, y2, 0.0});
    }


    void desenhar(QPainter &painter, const Matriz& mCam, const Window& win) override{
        auto it = p.begin();
        Coordenada p1_mundo = *it;
        Coordenada p2_mundo = *(++it);

        Coordenada p1_scn = mCam * p1_mundo;
        Coordenada p2_scn = mCam * p2_mundo;

        LimitesWindow limitesSCN = Window::getLimitesSCN();

        std::bitset<4> outcode1 = this->getOutcode(p1_scn.x_wc, p1_scn.y_wc, limitesSCN);
        std::bitset<4> outcode2 = this->getOutcode(p2_scn.x_wc, p2_scn.y_wc, limitesSCN);
        bool accept = false;

        while(true){
            if((outcode1 | outcode2).none()){
                accept = true;
                break;
            }
            if((outcode1 & outcode2).any()){
                break;
            }

            std::bitset<4> out_fora = outcode1.any() ? outcode1 : outcode2;
            double x_int = 0.0, y_int = 0.0;

            if(out_fora.test(3)){ // TOP
                x_int = p1_scn.x_wc + (p2_scn.x_wc - p1_scn.x_wc) * (limitesSCN.y_max - p1_scn.y_wc) / (p2_scn.y_wc - p1_scn.y_wc);
                y_int = limitesSCN.y_max;
            }else if(out_fora.test(2)){ // BASE
                x_int = p1_scn.x_wc + (p2_scn.x_wc - p1_scn.x_wc) * (limitesSCN.y_min - p1_scn.y_wc) / (p2_scn.y_wc - p1_scn.y_wc);
                y_int = limitesSCN.y_min;
            }else if(out_fora.test(1)){ // RIGHT
                y_int = p1_scn.y_wc + (p2_scn.y_wc - p1_scn.y_wc) * (limitesSCN.x_max - p1_scn.x_wc) / (p2_scn.x_wc - p1_scn.x_wc);
                x_int = limitesSCN.x_max;
            }else if(out_fora.test(0)){ // LEFT
                y_int = p1_scn.y_wc + (p2_scn.y_wc - p1_scn.y_wc) * (limitesSCN.x_min - p1_scn.x_wc) / (p2_scn.x_wc - p1_scn.x_wc);
                x_int = limitesSCN.x_min;
            }

            if(out_fora == outcode1){
                p1_scn.x_wc = x_int;
                p1_scn.y_wc = y_int;
                outcode1 = this->getOutcode(p1_scn.x_wc, p1_scn.y_wc, limitesSCN);
            }else{
                p2_scn.x_wc = x_int;
                p2_scn.y_wc = y_int;
                outcode2 = this->getOutcode(p2_scn.x_wc, p2_scn.y_wc, limitesSCN);
            }
        }

        if (accept) {
            double zoom = win.getZoomViewport();
            double larg_vp_zoom = win.getLargura() * zoom;
            double alt_vp_zoom  = win.getAltura() * zoom;

            double offX = (win.getLargura() - larg_vp_zoom) / 2.0;
            double offY = (win.getAltura() - alt_vp_zoom) / 2.0;


            double x1_vp = (p1_scn.x_wc + 1.0) * (larg_vp_zoom / 2.0) + offX;
            double y1_vp = (1.0 - p1_scn.y_wc) * (alt_vp_zoom / 2.0) + offY;

            double x2_vp = (p2_scn.x_wc + 1.0) * (larg_vp_zoom / 2.0) + offX;
            double y2_vp = (1.0 - p2_scn.y_wc) * (alt_vp_zoom / 2.0) + offY;

            QPen caneta(Qt::white, 4);
            painter.setPen(caneta);
            painter.drawLine(QPointF(x1_vp, y1_vp), QPointF(x2_vp, y2_vp));
        }
    }

};

#endif // RETA_H
