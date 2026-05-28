#ifndef PONTO_H
#define PONTO_H
#include "forma.h"
#include "Window.h"
#include "Matriz.h"

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    bool verificarClipping(const Window& win) override{
        if (this->p.empty()) return false;

        const Coordenada& c = this->p.front();

        // 1. Obtém os limites calculados pela Window
        LimitesWindow limites = win.getLimites();

        // 2. Compara as Coordenadas Originais do Mundo (WC) contra os limites
        return (c.x_wc >= limites.x_min && c.x_wc <= limites.x_max &&
                c.y_wc >= limites.y_min && c.y_wc <= limites.y_max);
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        if (this->p.empty()) return;

        // 1. Pega a coordenada bruta (Mundo)
        Coordenada c = this->p.front();

        // 2. APLICA A MATRIZ SCN (Só roda porque passou no clipping)
        Coordenada c_scn = mCam * c;

        // 3. TRANSFORMAÇÃO VIEWPORT
        double x_vp = (c_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y_vp = (1.0 - c_scn.y_wc) * (alt_vp / 2.0);

        // 4. DESENHA
        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);
        painter.drawPoint(x_vp, y_vp);
    }

};
#endif // PONTO_H