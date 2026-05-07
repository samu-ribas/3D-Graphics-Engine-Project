#include "viewport.h"

Viewport::Viewport( QString nome, double x, double y, double largura, double altura ) : nome(nome)
{
    this->centro = {x, y};
    this->largura = largura;
    this->altura = altura;
}

Coordenada Viewport::getCentro() {
    return this->centro;
}

double Viewport::getAltura() {
    return this->altura;
}

double Viewport::getLargura() {
    return this->largura;
}

Coordenada Viewport::getMin() {
    return {centro.x - (largura / 2), centro.y - (altura / 2)};
}

Coordenada Viewport::getMax() {
    return {centro.x + (largura / 2), centro.y + (altura / 2)};
}

QString Viewport::getNome() { return nome; }