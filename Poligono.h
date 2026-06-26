#ifndef POLIGONO_H
#define POLIGONO_H

#include "Matriz.h"

class Poligono : public Forma
{
public:
    Poligono(QString n, std::list<Coordenada> vertices) : Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }
    
    void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) override {
        if (this->p.size() < 3) return;

        double sx = (2.0 / win.getLargura()) * zoom;
        double sy = (2.0 / win.getAltura())  * zoom;
        double z_near = 1.0;
        LimitesSCN limites = Viewport::getLimitesSCN();

        std::vector<Coordenada> vertices_cam;
        for (const Coordenada& v : this->p) {
            vertices_cam.push_back(mView * v);
        }

        // Aplica near plane clipping em cada aresta e desenha
        for (size_t i = 0; i < vertices_cam.size(); ++i) {
            Coordenada p1 = vertices_cam[i];
            Coordenada p2 = vertices_cam[(i+1) % vertices_cam.size()];

            if (!clipNearPlane(p1, p2, z_near)) continue;

            p1 = mProj * p1;
            p2 = mProj * p2;

            // Aplicar escala
            p1.x_wc *= sx; p1.y_wc *= sy;
            p2.x_wc *= sx; p2.y_wc *= sy;

            p1.x_scn = p1.x_wc; p1.y_scn = p1.y_wc;
            p2.x_scn = p2.x_wc; p2.y_scn = p2.y_wc;

            if (cohenSutherland(p1, p2, limites)) {
                double x1_vp = (p1.x_wc + 1.0) * (win.getLargura() / 2.0);
                double y1_vp = (1.0 - p1.y_wc) * (win.getAltura() / 2.0);
                double x2_vp = (p2.x_wc + 1.0) * (win.getLargura() / 2.0);
                double y2_vp = (1.0 - p2.y_wc) * (win.getAltura() / 2.0);
                painter.drawLine(QPointF(x1_vp, y1_vp), QPointF(x2_vp, y2_vp));
            }
        }
    }
};
#endif // POLIGONO_H
