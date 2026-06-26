#include "viewport.h"

Viewport::Viewport(double x, double y , double w, double h) : x_vp(x), y_vp(y), largura(w), altura(h) {}

LimitesSCN Viewport::getLimitesSCN() {
    return {-1.0, 1.0, -1.0, 1.0};
}

double Viewport::getLargura() const {
    return largura;
}

double Viewport::getAltura() const {
    return altura;
}

double Viewport::getXvp() const{
    return this->x_vp;
}

double Viewport::getYvp() const{
    return this->y_vp;
}

void Viewport:: setXvp(double x){
    this->x_vp = x;
}

void Viewport:: setYvp(double y){
    this->y_vp = y;
}


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