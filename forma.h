#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>

struct Coordenada {
    double x;
    double y;
};

enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
public:
    Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}
    virtual ~Forma() {}
    virtual void desenhar(QPainter &painter) = 0;

    const QString getNome() { return nome; }
    //QString getTipo(){const return tipo;}


protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada> p;
};

#endif // FORMA_H
