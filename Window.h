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
        : margem(80), centro_x(cx), centro_y(cy), largura(w), altura(h), angulo(0.0){
    }

    void setLimites(){
        limites.x_min = this->centro_x - (this->largura / 2.0) ;
        limites.x_max = this->centro_x + (this->largura / 2.0) ;

        limites.y_min = this->centro_y - (this->altura / 2.0) ;
        limites.y_max = this->centro_y + (this->altura / 2.0) ;
    }

    LimitesWindow getLimites() const {return limites;}

    int getMargem(){return margem;}
    double getCentro_x() const { return this->centro_x;}
    double getCentro_y() const { return this->centro_y;}
    double getLargura() const { return this->largura;}
    double getAltura() const { return this->altura;}
    double getAngulo() const { return this->angulo;}

    void setLargura(double valor){
        if(valor>0.0){
            if(valor>891)
                valor = 891;
            this->largura=valor;
        }
    }

    void setAltura(double valor){
        if(valor>0.0){
            if(valor>431)
                valor = 431;
            this->altura=valor;
        }
    }

    void setCentro_x(double valor){this->centro_x=valor;}
    void setCentro_y(double valor){this->centro_y=valor;}
    void setAngulo(double valor){this->angulo=valor;}
    void setMargem(int valor){ this->margem = valor;}

private:
    int margem;
    double centro_x, centro_y, largura, altura, angulo;
    LimitesWindow limites;
};
#endif // WINDOW_H
