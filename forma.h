#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>

struct Coordenada {
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

//conjunto de constantes
enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
public:
    Forma(QString n, TipoForma tipo);
    virtual ~Forma() {}

    virtual void desenhar(QPainter &painter, int largura_vp, int altura_vp) = 0;
    virtual void aplicarTransformacao(const Matriz& m) = 0;

    Coordenada getCentroide() const;
    std::list<Coordenada>& getCoordenada();
    QString getNome() const ;
    TipoForma getTipo() const ;

protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada>p;
};

#endif // FORMA_H