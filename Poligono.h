#ifndef POLIGONO_H
#define POLIGONO_H

#include "Matriz.h"

class Poligono : public Forma
{
public:
    Poligono(QString n, std::list<Coordenada> vertices) : Forma(n, TipoForma::POLIGONO){
        this->p = vertices;
    }

    void desenhar(QPainter &painter, const Matriz& mCam, const Window& win) override{
        if(this->p.size() < 3){
            return;
        }

        // converter todos os vértices originais para o SCN
        std::list<Coordenada> entrada;
        for(const Coordenada& v : this->p){
            entrada.push_back(mCam * v);
        }

        // limites Absolutos do SCN
        double x_min = -1.0;
        double x_max = 1.0;
        double y_min = -1.0;
        double y_max = 1.0;

        std::list<Coordenada> saida;

        // algoritmo Sutherland-Hodgman em SCN
        for(int lado = 0; lado < 4; ++lado){
            saida.clear();
            if(entrada.empty()){
                break;
            }

            Coordenada S = entrada.back();

            for(const Coordenada& E : entrada){
                //comecoDentro: É o ponto inicial da aresta que está sendo analisada
                //finalDentro: É o ponto final da aresta que está sendo analisada
                bool comecoDentro = false;
                bool finalDentro = false;

                if(lado == 0){ // left
                    comecoDentro = (S.x_wc >= x_min);
                    finalDentro = (E.x_wc >= x_min);
                }else if(lado == 1){ // right
                    comecoDentro = (S.x_wc <= x_max);
                    finalDentro = (E.x_wc <= x_max);
                }else if(lado == 2){ // base
                    comecoDentro = (S.y_wc >= y_min);
                    finalDentro = (E.y_wc >= y_min);
                }else{ // top
                    comecoDentro = (S.y_wc <= y_max);
                    finalDentro = (E.y_wc <= y_max);
                }

                if(finalDentro){
                    if(!comecoDentro){
                        // interseção entrando
                        Coordenada i;
                        double dx = E.x_wc - S.x_wc;
                        double dy = E.y_wc - S.y_wc;

                        if(lado == 0){
                            i.x_wc = x_min;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_min - S.x_wc) / dx;
                        } else if(lado == 1){
                            i.x_wc = x_max;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_max - S.x_wc) / dx;
                        } else if(lado == 2){
                            i.y_wc = y_min;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_min - S.y_wc) / dy;
                        } else {
                            i.y_wc = y_max;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_max - S.y_wc) / dy;
                        }
                        saida.push_back(i);
                    }
                    saida.push_back(E);
                }
                else if(comecoDentro){
                    // interseção saindo
                    Coordenada i;
                    double dx = E.x_wc - S.x_wc;
                    double dy = E.y_wc - S.y_wc;

                    if(lado == 0){
                        i.x_wc = x_min;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_min - S.x_wc) / dx;
                    } else if(lado == 1){
                        i.x_wc = x_max;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (x_max - S.x_wc) / dx;
                    } else if(lado == 2){
                        i.y_wc = y_min;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_min - S.y_wc) / dy;
                    } else {
                        i.y_wc = y_max;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (y_max - S.y_wc) / dy;
                    }
                    saida.push_back(i);
                }
                S = E;
            }
            entrada = saida; //alimenta o próximo corte com o polígono já recotado
        }


        if(entrada.size() < 3){
            return;
        }

        double offX = (win.getLargura() - (win.getLargura()*win.getZoomViewport())) / 2.0;
        double offY = (win.getAltura() - (win.getAltura()*win.getZoomViewport())) / 2.0;

        std::vector<QPointF> pontos_tela;
        pontos_tela.reserve(entrada.size());

        for(const Coordenada& c_scn : entrada){
            double x_vp = (c_scn.x_wc + 1.0) * ((win.getLargura()*win.getZoomViewport())/2.0) + offX;
            double y_vp = (1.0 - c_scn.y_wc) * ((win.getAltura()*win.getZoomViewport())/ 2.0) + offY;
            pontos_tela.push_back(QPointF(x_vp, y_vp));
        }

        QPen caneta(Qt::white, 3);
        painter.setPen(caneta);

        for(size_t i = 0 ; i < pontos_tela.size() - 1 ; ++i){
            painter.drawLine(pontos_tela[i], pontos_tela[i + 1]);
        }
        painter.drawLine(pontos_tela.back(), pontos_tela.front());
    }
};
#endif // POLIGONO_H
