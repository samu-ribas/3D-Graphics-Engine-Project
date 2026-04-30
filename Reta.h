#ifndef RETA_H
#define RETA_H

#include "forma.h"
#include <QDebug>

class Reta : public Forma{
private:
    std::vector<double> ponto[2] = {{0.0, 0.0, 1.0},{0.0, 0.0, 1.0}};
    std::vector<double> pontoOriginal[2] = {{0.0, 0.0, 1.0},{0.0, 0.0, 1.0}};
public:
    Reta( QString n, double x1, double y1, double x2, double y2 ): Forma( n, TipoForma::RETA )
    {
        ponto[0].at(0) = x1;
        ponto[0].at(1) = y1;
        ponto[1].at(0) = x2;
        ponto[1].at(1) = y2;

    }

    void desenhar( QPainter &painter ) override
    {
        QPen caneta( Qt::white, 3 );
        painter.setPen(caneta);
        painter.drawLine( QLineF(
            ponto[0].at(0), ponto[0].at(1),
            ponto[1].at(0), ponto[1].at(1)
        ));
        /*if ( p.size()>=2 )
        {
            auto it = p.begin();
            Coordenada p1 = *it;
            it++;
            Coordenada p2 = *it;

        }*/
    }

    void transfomar( Matriz mt ) override
    {
        std::vector<double> resultado = {0.0, 0.0, 1.0};
        double soma;

        for (int n = 0; n < 2; n++ )
        {
            for ( int i = 0; i < 3 ; i++ )
            {
                soma = 0;
                for ( int j = 0; j < 3; j++ )
                {
                    soma += pontoOriginal[n].at(j) * mt.m[j][i];
                }
                resultado.at(i) = soma;
            }
            //qDebug() << resultado;
            pontoOriginal[n].at(0) = resultado.at(0);
            pontoOriginal[n].at(1) = resultado.at(1);
        }
        transformacaoNaoDestrutiva( mt );
    }

    void transformacaoNaoDestrutiva( Matriz mt ) override
    {
        std::vector<double> resultado = {0.0, 0.0, 1.0};
        double soma;

        for (int n = 0; n < 2; n++ )
        {
            for ( int i = 0; i < 3 ; i++ )
            {
                soma = 0;
                for ( int j = 0; j < 3; j++ )
                {
                    soma += ponto[n].at(j) * mt.m[j][i];
                }
                resultado.at(i) = soma;
            }
            //qDebug() << resultado;
            ponto[n].at(0) = resultado.at(0);
            ponto[n].at(1) = resultado.at(1);
        }
    }

    void reiniciar

    std::vector<double> getPos() override
    {
        return ponto[0];
    }

    std::vector<double> getCentroide() override
    {
        std::vector<double> centroide = {0.0, 0.0};

        centroide.at(0) = (ponto[0].at(0) + ponto[1].at(0)) / 2.0;
        centroide.at(1) = (ponto[0].at(1) + ponto[1].at(1)) / 2.0;

        return centroide;
    }
};

#endif // RETA_H
