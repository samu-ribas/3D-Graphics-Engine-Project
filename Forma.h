#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>
#include <bitset>
#include "Window.h"

struct Coordenada{
    double x_wc;
    double y_wc;
    double x_scn;
    double y_scn;

    Coordenada(double x = 0.0, double y = 0.0) : x_wc(x), y_wc(y), x_scn(x), y_scn(y) {}

    Coordenada operator*(const Coordenada& ponto) const{
        return {this->x_wc * ponto.x_wc, this->y_wc * ponto.y_wc};
    }
};

class Matriz;

enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma{
public:
    const std::bitset<4> INSIDE = (0b0000);
    const std::bitset<4> LEFT   = (0b0001);
    const std::bitset<4> RIGHT  = (0b0010);
    const std::bitset<4> BASE   = (0b0100);
    const std::bitset<4> TOP    = (0b1000);

    Forma(QString n, TipoForma tipo);

    virtual ~Forma(){}

    virtual void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp, const Window& win) = 0;

    virtual bool verificarClipping(const Window& win) = 0;

    void aplicarTransformacao(const Matriz& m);

    Coordenada getCentroide() const;
    std::list<Coordenada>& getCoordenada();
    QString getNome() const ;
    TipoForma getTipo() const ;
    std::bitset<4> getOutcode(double x, double y, const LimitesWindow& limites);

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;
};

#endif // FORMA_H
