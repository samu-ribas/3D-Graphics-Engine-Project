#ifndef RETA_H
#define RETA_H

#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1});
        p.push_back({x2, y2});
    }

    bool verificarClipping(const Window& win) override{
        if(this->p.empty() || this->p.size() < 2) return false;

        LimitesWindow limites = win.getLimites();

        auto it = this->p.begin();
        Coordenada p1_temp = *it;
        Coordenada p2_temp = *(++it);

        std::bitset<4> outcode1 = getOutcode(p1_temp.x_wc, p1_temp.y_wc, limites);
        std::bitset<4> outcode2 = getOutcode(p2_temp.x_wc, p2_temp.y_wc, limites);

        bool aceito = false;

        while(true){
            // aceitação trivial
            if((outcode1 | outcode2).none()){
                aceito = true;
                break;
            }
            // rejeição trivial
            if((outcode1 & outcode2).any()){
                break;
            }

            // escolhe um ponto fora da window
            std::bitset<4> out_fora = outcode1.any() ? outcode1 : outcode2;
            double x_int = 0;
            double y_int = 0;

            // coeficiente angular  m = (Y2 - Y1)/(X2 - X1)
            double m = (p2_temp.y_wc - p1_temp.y_wc)/(p2_temp.x_wc - p1_temp.x_wc);

            if((out_fora & TOP).any()){
                //top: X = 1/m * (Yt - Y1) + X1
                x_int = p1_temp.x_wc + (1.0/m) * (limites.y_max - p1_temp.y_wc);
                y_int = limites.y_max;
            }
            else if((out_fora & BASE).any()){
                //base: X = 1/m * (Yf - Y1) + X1
                x_int = p1_temp.x_wc + (1.0/m) * (limites.y_min - p1_temp.y_wc);
                y_int = limites.y_min;
            }
            else if((out_fora & RIGHT).any()){
                //direita: Y = m * (Xmax - X1) + Y1
                y_int = m * (limites.x_max - p1_temp.x_wc) + p1_temp.y_wc;
                x_int = limites.x_max;
            }
            else if((out_fora & LEFT).any()){
                //esquerda: Y = m * (Xmin - X1) + Y1
                y_int = m * (limites.x_min - p1_temp.x_wc) + p1_temp.y_wc;
                x_int = limites.x_min;
            }

            if (out_fora == outcode1) {
                p1_temp.x_wc = x_int;
                p1_temp.y_wc = y_int;
                outcode1 = getOutcode(p1_temp.x_wc, p1_temp.y_wc, limites);
            } else {
                p2_temp.x_wc = x_int;
                p2_temp.y_wc = y_int;
                outcode2 = getOutcode(p2_temp.x_wc, p2_temp.y_wc, limites);
            }
        }
        if(aceito){
            this->p1_clip = p1_temp;
            this->p2_clip = p2_temp;
        }
        return aceito;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        Coordenada c1_scn = mCam * this->p1_clip;
        Coordenada c2_scn = mCam * this->p2_clip;
        // Ponto 1
        double x1_vp = (c1_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y1_vp = (1.0 - c1_scn.y_wc) * (alt_vp / 2.0);

        // Ponto 2
        double x2_vp = (c2_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y2_vp = (1.0 - c2_scn.y_wc) * (alt_vp / 2.0);

        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        painter.drawLine(QLineF(x1_vp, y1_vp, x2_vp, y2_vp));
    }

private:
    Coordenada p1_clip;
    Coordenada p2_clip;
};

#endif // RETA_H
