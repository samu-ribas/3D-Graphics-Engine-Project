#ifndef PONTO_H
#define PONTO_H

#include "fsorma.h"

class Ponto : public Forma
{
private:
    std::vector<double> ponto = {0.0, 0.0, 1.0};
    std::vector<double> pontoOriginal = {0.0, 0.0, 1.0};
public:
    Ponto(QString n, double x, double y) : Forma(n, TipoForma::PONTO)
    {
        ponto.at(0) = x;
        ponto.at(1) = y;
        ponto.at(2) = 1.0;
    }

    void desenhar(QPainter &painter) override
    {
        QPen caneta(Qt::white, 5, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(caneta);
        painter.drawPoint(ponto.at(0), ponto.at(1));

        //if(!ponto.empty()){
            //Coordenada coorde = ponto.front();
            //painter.drawPoint(ponto.cod[0], ponto.cod[1]);
        //}
    }

    void transfomar( Matriz mt ) override
    {
        std::vector<double> resultado = {0.0, 0.0, 0.0};
        double soma;

        for ( int i = 0; i < 3 ; i++ )
        {
            soma = 0;
            for ( int j = 0; j < 3; j++ )
            {
                soma += ponto.at(j) * mt.m[j][i];
            }
            resultado.at(i) = soma;
        }
        pontoOriginal.at(0) = resultado.at(0);
        pontoOriginal.at(1) = resultado.at(1);
        transformacaoNaoDestrutiva( mt );
    }

    void transformacaoNaoDestrutiva( Matriz mt) override
    {
        std::vector<double> resultado = {0.0, 0.0, 0.0};
        double soma;

        for ( int i = 0; i < 3 ; i++ )
        {
            soma = 0;
            for ( int j = 0; j < 3; j++ )
            {
                soma += ponto.at(j) * mt.m[j][i];
            }
            resultado.at(i) = soma;
        }
        ponto.at(0) = resultado.at(0);
        ponto.at(1) = resultado.at(1);
    }

    //void incronizar

    std::vector<double> getPos() override
    {
        return ponto;
    }

    std::vector<double> getCentroide() override
    {
        return ponto;
    }
};

#endif // PONTO_H