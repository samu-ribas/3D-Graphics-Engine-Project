#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>
#include "matriz.h"

//struct Coordenada {
//    std::vector<double> cod = {0.0, 0.0, 1.0};
//};

enum class TipoForma {PONTO = 0, RETA = 1, POLIGONO = 2};

class Forma
{
public:
    Forma( QString n, TipoForma tipo ) : nome(n), o_tipo(tipo){}
    virtual ~Forma() {}
    virtual void desenhar( QPainter &painter ) = 0;
    virtual void transfomar( Matriz mt ) = 0;

    const QString getNome() { return nome; }
    virtual std::vector<double> getPos() = 0;
    virtual std::vector<double> getCentroide() = 0;
    //int getTipo() { return o_tipo; }

protected:
    QString nome;
    TipoForma o_tipo;

};

#endif // FORMA_H
