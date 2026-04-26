#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>

struct Coordenada {
    double x;
    double y;
};

class Matriz;

//conjunto de constantes
enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
public:
    Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}
    virtual ~Forma() {}

    virtual void desenhar(QPainter &painter) = 0;
    virtual void aplicarTransformacao(const Matriz& m) = 0;

    Coordenada getCentroide() const { // retorna o centroide do objeto
        double cx = 0.0, cy = 0.0;
        if(p.empty())
            return {0.0, 0.0};

        for(const auto& pt : p){
            cx += pt.x;
            cy += pt.y;
        }
        return {cx / p.size(), cy / p.size()};
    }

    QString getNome() const { return nome; }
    TipoForma getTipo() const { return o_tipo; }

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;
};

#endif // FORMA_H