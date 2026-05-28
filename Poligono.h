#ifndef POLIGONO_H
#define POLIGONO_H
#include "Forma.h"
#include "Matriz.h"

class Poligono : public Forma{

public:
    Poligono(QString n, std::list<Coordenada> vertices): Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    bool verificarClipping(const Window& win) override{
        return true;
    }


    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        if (this->p.size() < 3) return;

        // vetor temporário para guardar as coordenadas já convertidas em pixels
        std::vector<QPointF> pontos_tela;
        pontos_tela.reserve(this->p.size());

        for (const Coordenada& c : this->p) {
            // aplica a Matriz scn (que já contém a translação/rotação/escala da câmera)
            Coordenada c_scn = mCam * c;

            double x_vp = (c_scn.x_wc + 1.0) * (larg_vp / 2.0);
            double y_vp = (1.0 - c_scn.y_wc) * (alt_vp / 2.0);

            // guarda o pixel pronto
            pontos_tela.push_back(QPointF(x_vp, y_vp));
        }
        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);

        for (size_t i = 0; i < pontos_tela.size() - 1; ++i) {
            painter.drawLine(pontos_tela[i], pontos_tela[i+1]);
        }
        painter.drawLine(pontos_tela.back(), pontos_tela.front());
    }
};
#endif // POLIGONO_H
