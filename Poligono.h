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

        // limites Absolutos do SCN para guilhotina e interseções
        LimitesWindow limitesSCN = Window::getLimitesSCN();

        std::list<Coordenada> saida;

        // algoritmo Sutherland-Hodgman no SCN usando getOutcode
        for(int lado = 0; lado < 4; ++lado){
            saida.clear();
            if(entrada.empty()){
                break;
            }

            Coordenada S = entrada.back();

            for(const Coordenada& E : entrada){
                // Calcula o outcode para S e E no SCN
                std::bitset<4> outS = this->getOutcode(S.x_wc, S.y_wc, limitesSCN);
                std::bitset<4> outE = this->getOutcode(E.x_wc, E.y_wc, limitesSCN);

                // se o bit correspondente ao lado atual for 0, o ponto está DENTRO.
                bool comecoDentro = !outS.test(lado);
                bool finalDentro = !outE.test(lado);

                if(finalDentro){
                    if(!comecoDentro){
                        // Interseção entrando
                        Coordenada i;
                        double dx = E.x_wc - S.x_wc;
                        double dy = E.y_wc - S.y_wc;

                        if(lado == 0){ // LEFT
                            i.x_wc = limitesSCN.x_min;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (limitesSCN.x_min - S.x_wc) / dx;
                        } else if(lado == 1){ // RIGHT
                            i.x_wc = limitesSCN.x_max;
                            i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (limitesSCN.x_max - S.x_wc) / dx;
                        } else if(lado == 2){ // BASE
                            i.y_wc = limitesSCN.y_min;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (limitesSCN.y_min - S.y_wc) / dy;
                        } else { // TOP
                            i.y_wc = limitesSCN.y_max;
                            i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (limitesSCN.y_max - S.y_wc) / dy;
                        }
                        saida.push_back(i);
                    }
                    saida.push_back(E);
                }
                else if(comecoDentro){
                    // Interseção saindo
                    Coordenada i;
                    double dx = E.x_wc - S.x_wc;
                    double dy = E.y_wc - S.y_wc;

                    if(lado == 0){ // LEFT
                        i.x_wc = limitesSCN.x_min;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (limitesSCN.x_min - S.x_wc) / dx;
                    } else if(lado == 1){ // RIGHT
                        i.x_wc = limitesSCN.x_max;
                        i.y_wc = (dx == 0.0) ? S.y_wc : S.y_wc + dy * (limitesSCN.x_max - S.x_wc) / dx;
                    } else if(lado == 2){ // BASE
                        i.y_wc = limitesSCN.y_min;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (limitesSCN.y_min - S.y_wc) / dy;
                    } else { // TOP
                        i.y_wc = limitesSCN.y_max;
                        i.x_wc = (dy == 0.0) ? S.x_wc : S.x_wc + dx * (limitesSCN.y_max - S.y_wc) / dy;
                    }
                    saida.push_back(i);
                }
                S = E;
            }
            entrada = saida; // alimenta o próximo corte com o polígono já recotado
        }


        if(entrada.size() < 3){
            return;
        }

        std::vector<QPointF> pontos_tela;
        pontos_tela.reserve(entrada.size());

        for(const Coordenada& c_scn : entrada){
            double x_vp = (c_scn.x_wc + 1.0) * (win.getLargura() / 2.0);
            double y_vp = (1.0 - c_scn.y_wc) * (win.getAltura() / 2.0);
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
