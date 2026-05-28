#ifndef PONTO_H
#define PONTO_H
#include "forma.h"
#include "Window.h"

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

    void desenhar(QPainter &painter, int largura_vp, int altura_vp) override{
        const Coordenada& c = this->p.front();
        double x_vp = ((c.x_scn + 1.0) / 2.0) * largura_vp;
        double y_vp = (1.0 - ((c.y_scn + 1.0) / 2.0)) * altura_vp;

        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        painter.drawPoint(QPointF(x_vp, y_vp));
    }

};
#endif // PONTO_H