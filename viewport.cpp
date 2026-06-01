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

Coordenada Viewport::getUnprocessedMin() {
    return {centro.x - (largura / 2), centro.y - (altura / 2)};
}
Coordenada Viewport::getUnprocessedMax() {
    return {centro.x + (largura / 2), centro.y + (altura / 2)};
}

Coordenada Viewport::getCentro() {
    return this->centro;
}

double Viewport::getAltura() {
    return this->altura;
}

double Viewport::getLargura() { return this->largura; }

Coordenada Viewport::getMin() {

    Coordenada resultado = getUnprocessedMin();

    Matriz rotacao = Matriz::gerarMatrizR(getAngulo());
    Matriz translasao = Matriz::gerarMatrizT(getCentro());
    Matriz translasaoVolta = Matriz::gerarMatrizT(-getCentro());

    translasao = translasaoVolta * rotacao * translasao;
    resultado = translasao * resultado;

    return resultado;
}

Coordenada Viewport::getMax() {

    Coordenada resultado = getUnprocessedMax();

    Matriz rotacao = Matriz::gerarMatrizR(getAngulo());
    Matriz translasao = Matriz::gerarMatrizT(getCentro());
    Matriz translasaoVolta = Matriz::gerarMatrizT(-getCentro());

    translasao = translasaoVolta * rotacao * translasao;
    resultado = translasao * resultado;

    return resultado;
}

double Viewport::getAngulo() { return this->angulo; }


Linha Viewport::getTopo() {
    Coordenada ponto1;
    Coordenada ponto2;

    ponto1 = {getMax()};

    ponto2 = {getMin().x, getMax().y};

    return {ponto1, ponto2};
}

Linha Viewport::getFundo() {
    Coordenada ponto1;
    Coordenada ponto2;

    ponto1 = {getMin()};

    ponto2 = {getMax().x, getMin().y};

    return {ponto1, ponto2};
}

Linha Viewport::getDireita() {
    Coordenada ponto1;
    Coordenada ponto2;

    ponto1 = {getMin()};

    ponto2 = {getMin().x, getMax().y};

    return {ponto1, ponto2};
}

Linha Viewport::getEsquerda() {
    Coordenada ponto1;
    Coordenada ponto2;

    ponto1 = {getMax()};

    ponto2 = {getMax().x, getMin().y};

    return {ponto1, ponto2};
}



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