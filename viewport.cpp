#include "viewport.h"

Viewport::Viewport( QString nome, double x, double y, double largura, double altura ) : nome(nome)
{
    this->centro = {x, y};
    this->largura = largura;
    this->altura = altura;
    this->angulo = 0;
}

Viewport::Viewport( QString nome, double x, double y, double largura, double altura, double angulo ) : nome(nome)
{
    this->centro = {x, y};
    this->largura = largura;
    this->altura = altura;
    this->angulo = angulo;
}

Coordenada Viewport::getCentro() { return this->centro; }

double Viewport::getAltura() { return this->altura; }

double Viewport::getLargura() { return this->largura; }

Coordenada Viewport::getMin() { return {centro.x - (largura / 2), centro.y - (altura / 2)}; }

Coordenada Viewport::getMax() { return {centro.x + (largura / 2), centro.y + (altura / 2)}; }

double Viewport::getAngulo() { return this->angulo; }





void Viewport::setCentro( Coordenada centro ) {
    this->centro = centro;
}

void Viewport::setAltura( double altura ) {
    this->altura = altura;
}

void Viewport::setLargura( double largura ) {
    this->largura = largura;
}

void Viewport::setAngulo( double angulo ) {
    this->angulo = angulo;
}

QString Viewport::getNome() { return nome; }