#include "Viewport.h"

Viewport::Viewport(double x, double y , double w, double h) : x_vp(x), y_vp(y), largura(w), altura(h) {}

LimitesSCN Viewport::getLimitesSCN() {
    return {-1.0, 1.0, -1.0, 1.0};
}

double Viewport::getLargura() const { return largura; }
double Viewport::getAltura() const { return altura; }

void Viewport::setLargura(double valor) {
    if(valor > 0.0) {
        if(valor > 891) valor = 891;
        largura = valor;
    }
}

void Viewport::setAltura(double valor) {
    if(valor > 0.0) {
        if(valor > 431) valor = 431;
        altura = valor;
    }
}