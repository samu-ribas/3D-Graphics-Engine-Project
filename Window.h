#ifndef WINDOW_H
#define WINDOW_H
#include<BitsClipping.h>

class Window
{
public:
    Window(double cx, double cy, double w, double h)
        : centro_x(cx), centro_y(cy), largura(w), altura(h), angulo(0.0) {}

    double centro_x, centro_y, largura, altura, angulo;

    BitsClipping bits = BitsClipping();
};

#endif // WINDOW_H
