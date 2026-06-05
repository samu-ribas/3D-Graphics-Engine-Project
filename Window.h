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

    Window(double cx, double cy, double w, double h)
        : margem(40), centro_x(cx), centro_y(cy), largura(w), altura(h), angulo(0.0){
    }

    void desenharViewport(QPainter& painter, int larg_tela, int alt_tela){
        painter.translate(this->margem, this->margem);

        int larg_interna = larg_tela - (this->margem * 2);
        int alt_interna  = alt_tela - (this->margem * 2);

        QPen canetaVermelha(Qt::white, 4);
        painter.setPen(canetaVermelha);

        //o desenho vai de 0,0 até a largura interna
        painter.drawRect(0, 0, larg_interna, alt_interna);
    }

    void setLimites(){

        limites.x_min = this->centro_x - (this->largura / 2.0) ;
        limites.x_max = this->centro_x + (this->largura / 2.0) ;

        limites.y_min = this->centro_y - (this->altura / 2.0) ;
        limites.y_max = this->centro_y + (this->altura / 2.0) ;
    }

    LimitesWindow getLimites() const {return limites;}

    int getMargem(){return margem;}
    double getCentro_x(){ return this->centro_x;}
    double getCentro_y(){ return this->centro_y;}
    double getLargura(){ return this->largura;}
    double getAltura(){ return this->altura;}
    double getAngulo(){ return this->angulo;}

    void setCentro_x(double valor){this->centro_x=valor;}
    void setCentro_y(double valor){this->centro_y=valor;}
    void setLargura(double valor){this->largura=valor;}
    void setAltura(double valor){this->altura=valor;}
    void setAngulo(double valor){this->angulo=valor;}
    void setMargem(int valor){ this->margem = valor;}

private:
    int margem;
    double centro_x, centro_y, largura, altura, angulo;
        LimitesWindow limites;
};
#endif // WINDOW_H
