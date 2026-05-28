#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>
#include <BitsClipping.h>
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
    const int INSIDE = 0; // 0000
    const int LEFT   = 1; // 0001
    const int RIGHT  = 2; // 0010
    const int BOTTOM = 4; // 0100
    const int TOP    = 8; // 1000
    Forma(QString n, TipoForma tipo);

    virtual ~Forma(){}

    virtual void desenhar(QPainter &painter, const Matriz& mCam, int larg_vp, int alt_vp) = 0;

    virtual bool verificarClipping(const Window& win) = 0;

    void aplicarTransformacao(const Matriz& m);

    Coordenada getCentroide() const;
    std::list<Coordenada>& getCoordenada();
    QString getNome() const ;
    TipoForma getTipo() const ;
    int getOutcode(double x, double y, const LimitesWindow& limites);

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;

private:
    BitsClipping bitObj;
};

#endif // FORMA_H
