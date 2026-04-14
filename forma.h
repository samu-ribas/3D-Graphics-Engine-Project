#ifndef FORMA_H
#define FORMA_H
#include <QPainter>
#include <QVector>
#include <QPoint>

enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
public:
    Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}
    virtual ~Forma() {}
    virtual void desenhar(QPainter &painter) = 0;
    //QString getNome(){const return nome;}
    //QString getTipo(){const return tipo;}

protected:
    QString nome;
    TipoForma o_tipo;
};

#endif // FORMA_H
