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

    void desenharViewport(QPainter& painter, int larg_tela, int alt_tela){
        int margem = 40;

        painter.translate(margem, margem);

        int larg_interna = larg_tela - (margem * 2);
        int alt_interna  = alt_tela - (margem * 2);

        QPen canetaVermelha(Qt::darkRed, 2);
        painter.setPen(canetaVermelha);

        //o desenho vai de 0,0 até a largura interna
        painter.drawRect(0, 0, larg_interna, alt_interna);
    }

    LimitesWindow getLimites() const {
        LimitesWindow limites;

        limites.x_min = this->centro_x - (this->largura / 2.0);
        limites.x_max = this->centro_x + (this->largura / 2.0);
        limites.y_min = this->centro_y - (this->altura / 2.0);
        limites.y_max = this->centro_y + (this->altura / 2.0);

        return limites;
    }
};
#endif // WINDOW_H
