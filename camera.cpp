#include "Camera.h"

Camera::Camera(double cx, double cy, double cz) : x(cx), y(cy), z(cz), angulo(0.0), zoom(1.0), d(50.0) {}

double Camera::getX() const {
    return x;
}

double Camera::getY() const {
    return y;
}

double Camera::getZ() const {
    return z;
}

double Camera::getAngulo() const {
    return angulo;
}

double Camera::getZoom() const {
    return zoom;
}

double Camera::getD() const {
    return d;
}
//--------------------------------------------
void Camera::setX(double valor){
    x = valor;
}

void Camera::setY(double valor){
    y = valor;
}

void Camera::setZ(double valor){
    z = valor;
}

void Camera::setAngulo(double valor){
    angulo = valor;
}

void Camera::setZoom(double z) {
    if(z > 0.0)
        zoom = z;
}

void Camera::setD(double valor) {
    if(valor >= 1.0)
        d = valor;
}

void Camera::aumentarZoom() {
    zoom *= 1.1;
    if(zoom > 20.0){
        zoom = 20.0;
    }
}

void Camera::diminuirZoom() {
    zoom /= 1.1;
    if(zoom < 0.1)
        zoom = 0.1;
}