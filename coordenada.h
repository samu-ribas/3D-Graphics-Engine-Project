#ifndef COORDENADA_H
#define COORDENADA_H

struct Coordenada {
    double x;
    double y;
    double xScn;
    double yScn;

    Coordenada() {
        x = 0;
        y = 0;
        xScn = 0;
        yScn = 0;
    }
    Coordenada(double x, double y) : x(x), y(y), xScn(x), yScn(y) {}

    Coordenada operator* (const Coordenada& ponto) const {
        return {this->x * ponto.x, this->y * ponto.y};
    }

    Coordenada operator- () const {
        return {-this->x, -this->y};
    }

    Coordenada operator/ (const Coordenada& ponto) const {
        return {this->x / ponto.x, this->y / ponto.y};
    }
};

#endif // COORDENADA_H
