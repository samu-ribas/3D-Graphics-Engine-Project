#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>
#include "Viewport.h"

struct Coordenada{
    double x_wc;
    double y_wc;
    double z_wc;
    double x_scn;
    double y_scn;

    Coordenada(double x = 0.0, double y = 0.0, double z = 0.0) : x_wc(x), y_wc(y), z_wc(z), x_scn(x), y_scn(y) {}

    Coordenada operator*(const Coordenada& ponto) const{
        return {this->x_wc * ponto.x_wc, this->y_wc * ponto.y_wc, this->z_wc * ponto.z_wc};
    }
};

class Matriz;

enum class TipoForma{PONTO, RETA, POLIGONO, MODELO3D};

class Forma{
public:
    Forma(QString n, TipoForma tipo);

    virtual ~Forma(){}
    virtual void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) = 0;
    void aplicarTransformacao(const Matriz& m);

    Coordenada getCentroide() const;
    std::list<Coordenada>& getCoordenada();
    QString getNome() const;
    TipoForma getTipo() const;
    int obterOutCode(double x, double y, const LimitesSCN& limites);
    bool cohenSutherland(Coordenada& p1, Coordenada& p2, const LimitesSCN& limites);
    bool clipNearPlane(Coordenada& p1, Coordenada& p2, double z_near);

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;
};

#endif // FORMA_H