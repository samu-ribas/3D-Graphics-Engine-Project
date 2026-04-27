#ifndef PONTO_H
#define PONTO_H

#include "Forma.h"

class Ponto : public Forma
{
private:
    std::vector<double> p = {0.0, 0.0, 1.0};
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO)
    {
        p.at(0) = x;
        p.at(1) = y;
        p.at(2) = 1.0;
    }

    void desenhar(QPainter &painter) override
    {
        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        painter.drawPoint(p.at(0), p.at(1));

        //if(!p.empty()){
            //Coordenada coorde = p.front();
            //painter.drawPoint(p.cod[0], p.cod[1]);
        //}
    }

    void transfomar( Matriz mt ) override
    {
        std::vector<double> resultado = {0.0, 0.0, 0.0};
        for ( int i = 0; i < 3 ; i++ )
        {
            double soma = 0;
            for ( int j = 0; j < 3; j++ )
            {
                soma += p.at(j) * mt.m[j][i];
            }
            resultado.at(i) = soma;
        }
        p.at(0) = resultado.at(0);
        p.at(1) = resultado.at(1);
    }

    std::vector<double> getPos() override
    {
        return p;
    }
};

#endif // PONTO_H