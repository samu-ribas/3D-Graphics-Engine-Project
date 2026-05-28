#ifndef RETA_H
#define RETA_H
#include "Forma.h"
#include "Matriz.h"

class Reta : public Forma{
public:
    Reta(QString n, double x1, double y1, double x2, double y2): Forma(n, TipoForma::RETA){
        p.push_back({x1, y1});
        p.push_back({x2, y2});
    }

    bool verificarClipping(const Window& win) override{
        return true;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        if (this->p.size() < 2) return;

        auto it = this->p.begin();
        const Coordenada& p1_mundo = *it;
        const Coordenada& p2_mundo = *++it;

        // 1. Aplica a Matriz da Câmera (Mundo -> SCN)
        Coordenada c1_scn = mCam * p1_mundo;
        Coordenada c2_scn = mCam * p2_mundo;

        // 2. Mapeamento para Viewport (SCN -> Pixels)
        // Ponto 1
        double x1_vp = (c1_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y1_vp = (1.0 - c1_scn.y_wc) * (alt_vp / 2.0);

        // Ponto 2
        double x2_vp = (c2_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y2_vp = (1.0 - c2_scn.y_wc) * (alt_vp / 2.0);

        // 3. Rasterização
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);
        painter.drawLine(x1_vp, y1_vp, x2_vp, y2_vp);
    }

};

#endif // RETA_H
