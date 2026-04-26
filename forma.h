#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>

struct Coordenada {
    double x;
    double y;
};


//conjunto de constantes
enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
public:

    Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}
    virtual ~Forma() {}
    virtual void desenhar(QPainter &painter) = 0;
    QString getNome() const { return nome; }
    TipoForma getTipo() const { return o_tipo; }

    Coordenada getCentroide() const {
        double cx = 0.0, cy = 0.0;
        if (p.empty()) return {0.0, 0.0};

        for (const auto& pt : p) {
            cx += pt.x;
            cy += pt.y;
        }
        return {cx / p.size(), cy / p.size()};
    }

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;
};

#endif // FORMA_H