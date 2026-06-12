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

        if(lado == 0){
            return !code.test(0); // LEFT
        }

        if(lado == 1){
            return !code.test(1); // RIGHT
        }

        if(lado == 2){
            return !code.test(2); // BASE
        }

        if(lado == 3){
            return !code.test(3); // TOP
        }

        return false;
    }

    Coordenada intersec(const Coordenada& a, const Coordenada& b, int lado, const LimitesWindow& limites){
        Coordenada r;

        double dx = b.x_wc - a.x_wc;
        double dy = b.y_wc - a.y_wc;

        if(lado == 0){  // esquerda
            r.x_wc = limites.x_min;

            if (dx == 0.0){
                r.y_wc = a.y_wc;
            }
            else{
                r.y_wc = a.y_wc + dy * (limites.x_min - a.x_wc) / dx;
            }
        }
        else if(lado == 1){ // direita
            r.x_wc = limites.x_max;

            if(dx == 0.0){
                r.y_wc = a.y_wc;
            }
            else{
                r.y_wc = a.y_wc + dy * (limites.x_max - a.x_wc) / dx;
            }
        }
        else if(lado == 2){ // baixo
            r.y_wc = limites.y_min;

            if(dy == 0.0){
                r.x_wc = a.x_wc;
            }
            else{
                r.x_wc = a.x_wc +dx * (limites.y_min - a.y_wc) / dy;
            }
        }
        else{   // cima
            r.y_wc = limites.y_max;

            if(dy == 0.0){
                r.x_wc = a.x_wc;
            }
            else{
                r.x_wc = a.x_wc +dx * (limites.y_max - a.y_wc) / dy;
            }
        }
        r.x_scn = r.x_wc;
        r.y_scn = r.y_wc;

        return r;
    }

    bool verificarClipping(const Window& win) override {
        if(this->p.size() < 3){
            return false;
        }
        this->p_clip.clear();

        //obter parâmetros da janela
        double larg = win.getLargura();
        double alt = win.getAltura();
        double cx = win.getCentro_x();
        double cy = win.getCentro_y();
        double ang = win.getAngulo();

        //construir matriz mundo     câmera: T(-cx,-cy) * R(-ang)
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

        //construir matriz inversa    câmera -> mundo: T(cx,cy) * R(ang)
        Matriz translacao_inv;
        translacao_inv.m[0][2] = cx;
        translacao_inv.m[1][2] = cy;
        Matriz rotacao_inv;
        double rad_inv = ang * (M_PI / 180.0);
        rotacao_inv.m[0][0] = cos(rad_inv);
        rotacao_inv.m[0][1] = -sin(rad_inv);
        rotacao_inv.m[1][0] = sin(rad_inv);
        rotacao_inv.m[1][1] = cos(rad_inv);
        Matriz camera_para_mundo = translacao_inv * rotacao_inv;

        //converter todos os vértices para coordenadas de câmera
        std::list<Coordenada> entrada_cam;
        for(const Coordenada& v : this->p){
            entrada_cam.push_back(mundo_para_camera * v);
        }
        //limites no espaço da câmera, janela centralizada na origem
        double x_min_cam = -larg / 2.0;
        double x_max_cam = larg / 2.0;
        double y_min_cam = -alt / 2.0;
        double y_max_cam = alt / 2.0;


        std::list<Coordenada> entrada = entrada_cam;
        std::list<Coordenada> saida;

        for(int lado = 0; lado < 4; ++lado){
            saida.clear();
            if (entrada.empty()) break;
            Coordenada S = entrada.back();
            for(const Coordenada& E : entrada){
                bool S_dentro, E_dentro;
                // lado 0 esquerda
                if(lado == 0){
                    S_dentro = (S.x_wc >= x_min_cam);
                    E_dentro = (E.x_wc >= x_min_cam);
                }
                // lado 1 direita
                else if(lado == 1){
                    S_dentro = (S.x_wc <= x_max_cam);
                    E_dentro = (E.x_wc <= x_max_cam);
                }
                // lado 2 baixo
                else if(lado == 2){
                    S_dentro = (S.y_wc >= y_min_cam);
                    E_dentro = (E.y_wc >= y_min_cam);
                }
                // lado 3 topo
                else{
                    S_dentro = (S.y_wc <= y_max_cam);
                    E_dentro = (E.y_wc <= y_max_cam);
                }

                if(E_dentro){
                    if(!S_dentro){
                        Coordenada i;
                        double dx = E.x_wc - S.x_wc;
                        double dy = E.y_wc - S.y_wc;
                        if(lado == 0){ // esquera
                            i.x_wc = x_min_cam;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_min_cam - S.x_wc) / dx;
                        }else if(lado == 1){ // direia
                            i.x_wc = x_max_cam;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_max_cam - S.x_wc) / dx;
                        }else if(lado == 2){ // baixo
                            i.y_wc = y_min_cam;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_min_cam - S.y_wc) / dy;
                        }else{ // topo
                            i.y_wc = y_max_cam;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_max_cam - S.y_wc) / dy;
                        }
                        saida.push_back(i);
                    }
                    saida.push_back(E);
                }
                else if(S_dentro){
                    //calcular interseção
                    Coordenada i;
                    double dx = E.x_wc - S.x_wc;
                    double dy = E.y_wc - S.y_wc;
                    if(lado == 0){
                        i.x_wc = x_min_cam;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_min_cam - S.x_wc) / dx;
                    }else if(lado == 1){
                        i.x_wc = x_max_cam;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_max_cam - S.x_wc) / dx;
                    }else if(lado == 2){
                        i.y_wc = y_min_cam;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_min_cam - S.y_wc) / dy;
                    }else{
                        i.y_wc = y_max_cam;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_max_cam - S.y_wc) / dy;
                    }
                    saida.push_back(i);
                }
                S = E;
            }
            entrada = saida;
        }

        if(entrada.empty()){
            return false;
        }
        for(const Coordenada& c : entrada){
            this->p_clip.push_back(camera_para_mundo * c);
        }
        return true;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp, const Window& win) override{
        const std::list<Coordenada>& lista = (this->p_clip.empty() ? this->p : this->p_clip);

        if(lista.size() < 3) return;

        double zoom = win.getZoomViewport();
        double larg_vp_zoom = larg_vp * zoom;
        double alt_vp_zoom = alt_vp * zoom;

        std::vector<QPointF> pontos_tela;
        pontos_tela.reserve(lista.size());

        for(const Coordenada& c : lista){
            Coordenada c_scn = mCam * c;

            double x_vp = (c_scn.x_wc + 1.0) * (larg_vp_zoom/2.0) + (larg_vp - larg_vp_zoom) / 2.0;
            double y_vp = (1.0 - c_scn.y_wc) * (alt_vp_zoom / 2.0) + (alt_vp - alt_vp_zoom) / 2.0;

            pontos_tela.push_back(QPointF(x_vp, y_vp));
        }

        QPen caneta(Qt::white, 4);
        painter.setPen(caneta);

        for(size_t i = 0 ; i < pontos_tela.size() - 1 ; ++i){
            painter.drawLine(pontos_tela[i], pontos_tela[i + 1]);
        }
        painter.drawLine(pontos_tela.back(), pontos_tela.front());
    }

private:
    std::list<Coordenada> p_clip;
};
#endif // POLIGONO_H
