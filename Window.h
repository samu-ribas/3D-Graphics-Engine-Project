#ifndef WINDOW_H
#define WINDOW_H
#include <QPainter>

struct LimitesWindow {
    double x_min;
    double x_max;
    double y_min;
    double y_max;
};

class Window
{
public:
    double centro_x, centro_y, largura, altura, angulo;

    Window(double cx, double cy, double w, double h)
        : centro_x(cx), centro_y(cy), largura(w), altura(h), angulo(0.0) {

    }

    void desenharViewport(QPainter &painter, int larguraFrame, int alturaFrame){
        int margem = 60;
        int vp_x_min = margem;
        int vp_y_min = margem;
        int vp_x_max = larguraFrame - margem;
        int vp_y_max = alturaFrame - margem;

        QPen caneta(Qt::darkRed, 5);
        painter.setPen(caneta);

        painter.drawLine(vp_x_min, vp_y_min, vp_x_max, vp_y_min);
        painter.drawLine(vp_x_max, vp_y_min, vp_x_max, vp_y_max);
        painter.drawLine(vp_x_max, vp_y_max, vp_x_min, vp_y_max);
        painter.drawLine(vp_x_min, vp_y_max, vp_x_min, vp_y_min);

        // move o eixo 0,0 do Qt para o canto superior esquerdo do viewport para que as formas sejam desenhadas dentro deste limite
        painter.translate(vp_x_min, vp_y_min);
    }

    LimitesWindow getLimites() const {
        LimitesWindow limites;

        double metade_largura = this->largura / 2.0;
        double metade_altura  = this->altura / 2.0;

        limites.x_min = this->centro_x - metade_largura;
        limites.x_max = this->centro_x + metade_largura;

        limites.y_min = this->centro_y - metade_altura;
        limites.y_max = this->centro_y + metade_altura;

        return limites;
    }
};

#endif // WINDOW_H
