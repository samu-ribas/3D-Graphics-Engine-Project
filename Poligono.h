#ifndef POLIGONO_H
#define POLIGONO_H
#include "forma.h"

class Poligono : public Forma{

private:
    std::list<std::vector<double>> ponto;
public:
    explicit Poligono( QString n, std::list<std::vector<double>> vertices ) : Forma( n, TipoForma::POLIGONO )
    {
        this->ponto.assign( vertices.begin(), vertices.end() );
    }

    void desenhar( QPainter &painter ) override
    {
        QPen caneta(Qt::white, 5);
        painter.setPen(caneta);

        if(ponto.size()<2) return;

        auto it = ponto.begin();
        auto next = std::next(it);

        while(next != ponto.end()){
            painter.drawLine(QLineF(it->at(0), it->at(1), next->at(0), next->at(1)));
            it++;
            next++;
        }
        auto primeiro = ponto.front();
        auto ultimo = ponto.back();
        painter.drawLine(QLineF(ultimo.at(0), ultimo.at(1), primeiro.at(0), primeiro.at(1)));
    }

    void transfomar( Matriz mt ) override
    {
        std::vector<double> resultado = {0.0, 0.0, 1.0};
        double soma;

        auto it = ponto.begin();
        auto next = std::next(it);

        while(next != ponto.end())
        {
            for ( int i = 0; i < 3 ; i++ )
            {
                soma = 0;
                for ( int j = 0; j < 3; j++ )
                {
                    soma += it->at(j) * mt.m[j][i];
                }
                resultado.at(i) = soma;
            }
            it->at(0) = resultado.at(0);
            it->at(1) = resultado.at(1);
            it++;
            next++;
        }
    }

    std::vector<double> getPos() override
    {
        return ponto.front();
    }
};

#endif // POLIGONO_H
