#ifndef PONTO_H
#define PONTO_H
<<<<<<< HEAD

//#include "forma.h"
//#include "Matriz.h"
=======
#include "forma.h"
#include "Window.h"
#include "Matriz.h"
>>>>>>> refs/remotes/origin/samuel

class Ponto : public Forma
{
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO){
        p.push_back({x,y});
    }

    bool verificarClipping(const Window& win) override{
        if (this->p.empty()) return false;

        const Coordenada& c = this->p.front();
        LimitesWindow limites = win.getLimites();

        int outcode = getOutcode(c.x_wc, c.y_wc, limites);

        if(outcode == INSIDE)
            return true;
        else
            return false;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        if (this->p.empty()) return;
        Coordenada c = this->p.front();
        Coordenada c_scn = mCam * c;

        double x_vp = (c_scn.x_wc + 1.0) * (larg_vp / 2.0);
        double y_vp = (1.0 - c_scn.y_wc) * (alt_vp / 2.0);

        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);
        painter.drawPoint(x_vp, y_vp);
    }

<<<<<<< HEAD

=======
>>>>>>> refs/remotes/origin/samuel
};
#endif // PONTO_H