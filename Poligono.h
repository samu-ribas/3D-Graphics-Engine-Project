#ifndef POLIGONO_H
#define POLIGONO_H

#include "Matriz.h"

class Poligono : public Forma
{
public:
    Poligono(QString n, std::list<Coordenada> vertices) : Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    bool dentro(const Coordenada& c,int lado,const LimitesWindow& limites){
        std::bitset<4> code = getOutcode(c.x_wc, c.y_wc, limites);

        if(lado == 0)
            return !code.test(0); // LEFT

        if(lado == 1)
            return !code.test(1); // RIGHT

        if(lado == 2)
            return !code.test(2); // BASE

        if(lado == 3)
            return !code.test(3); // TOP

        return false;
    }

    Coordenada intersec(const Coordenada& a, const Coordenada& b, int lado, const LimitesWindow& limites){
        Coordenada r;

        double dx = b.x_wc - a.x_wc;
        double dy = b.y_wc - a.y_wc;

        if(lado == 0){  // esquerda
            r.x_wc = limites.x_min;

            if (dx == 0.0)
                r.y_wc = a.y_wc;
            else
                r.y_wc = a.y_wc + dy * (limites.x_min - a.x_wc) / dx;
        }
        else if(lado == 1){ // direita
            r.x_wc = limites.x_max;

            if(dx == 0.0)
                r.y_wc = a.y_wc;
            else
                r.y_wc = a.y_wc + dy * (limites.x_max - a.x_wc) / dx;
        }
        else if(lado == 2){ // baixo
            r.y_wc = limites.y_min;

            if(dy == 0.0)
                r.x_wc = a.x_wc;
            else
                r.x_wc = a.x_wc +dx * (limites.y_min - a.y_wc) / dy;
        }
        else{   // cima
            r.y_wc = limites.y_max;

            if(dy == 0.0)
                r.x_wc = a.x_wc;
            else
                r.x_wc = a.x_wc +dx * (limites.y_max - a.y_wc) / dy;
        }
        r.x_scn = r.x_wc;
        r.y_scn = r.y_wc;

        return r;
    }

    bool verificarClipping(const Window& win) override {
        if(this->p.size() < 3) return false;

        this->p_clip.clear();

        LimitesWindow limites = win.getLimites();

        std::list<Coordenada> entrada = this->p;
        std::list<Coordenada> saida;

        for(int lado = 0; lado < 4; ++lado){
            saida.clear();

            if(entrada.empty()) break;

            Coordenada S = entrada.back();

            for(const Coordenada& E : entrada) {
                bool S_dentro = dentro(S, lado, limites);
                bool E_dentro = dentro(E, lado, limites);

                if(E_dentro){
                    if(!S_dentro)
                        saida.push_back(intersec(S, E, lado, limites));
                    saida.push_back(E);
                }
                else if(S_dentro)
                    saida.push_back(intersec(S, E, lado, limites));

                S = E;
            }

            entrada = saida;
        }
        this->p_clip = entrada;
        return !this->p_clip.empty();
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) override{
        const std::list<Coordenada>& lista = (this->p_clip.empty() ? this->p : this->p_clip);
        if(lista.size() < 3) return;

        std::vector<QPointF> pontos_tela;
        pontos_tela.reserve(lista.size());

        for(const Coordenada& c : lista){
            Coordenada c_scn = mCam * c;

            double x_vp = (c_scn.x_wc + 1.0) * (larg_vp / 2.0);
            double y_vp = (1.0 - c_scn.y_wc) * (alt_vp / 2.0);

            pontos_tela.push_back(QPointF(x_vp, y_vp));
        }

        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);

        for (size_t i = 0; i < pontos_tela.size() - 1; ++i)
            painter.drawLine(pontos_tela[i], pontos_tela[i + 1]);

        painter.drawLine(pontos_tela.back(), pontos_tela.front());
    }

private:
    std::list<Coordenada> p_clip;
};
#endif // POLIGONO_H
