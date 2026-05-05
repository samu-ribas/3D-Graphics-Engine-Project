#ifndef COORDENADA_H
#define COORDENADA_H

struct Coordenada {
    double x;
    double y;

    Coordenada operator* (const Coordenada& ponto) const {
        return {this->x * ponto.x, this->y * ponto.y};
    }

    Coordenada operator- () const {
        return {-this->x, -this->y};
    }
};

#endif // COORDENADA_H
