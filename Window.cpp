#include "Window.h"
#include <QDebug>
Window::Window(double cx, double cy, double w, double h)
    : margem(80), centro_x(cx), centro_y(cy), largura(w), altura(h), angulo(0.0), zoomViewport(1.0){}

LimitesWindow Window:: getLimitesSCN(){
    return {-1.0, 1.0, -1.0, 1.0};
}

int Window::getMargem(){
    return this->margem;
}

double Window::getCentro_x() const {
    return this->centro_x;
}

double Window::getCentro_y() const {
    return this->centro_y;
}

double Window::getLargura() const {
    return this->largura;
}

double Window::getAltura() const {
    return this->altura;
}

double Window::getAngulo() const {
    return this->angulo;
}

double Window:: getZoomViewport() const {
    return zoomViewport;
}

void Window:: setZoomViewport(double z) {
    if (z > 0.0)
        zoomViewport = z;
}

void Window:: aumentarZoom(){
    zoomViewport *= 1.1;
    if (zoomViewport > 20.0)
        zoomViewport = 20.0;
}

void Window:: diminuirZoom(){
    zoomViewport /= 1.1;
    if (zoomViewport < 0.0)
        zoomViewport = 0.0;
}

void Window:: setLargura(double valor){
    if(valor>0.0){
        if(valor>891)
            valor = 891;
        this->largura=valor;
    }
}

void Window:: setAltura(double valor){
    if(valor>0.0){
        if(valor>431)
            valor = 431;
        this->altura=valor;
    }
}

void Window::setCentro_x(double valor){
    this->centro_x=valor;
}

void Window::setCentro_y(double valor){
    this->centro_y=valor;
}

void Window::setAngulo(double valor){
    this->angulo=valor;
}