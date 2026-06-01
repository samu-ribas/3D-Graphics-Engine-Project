#ifndef COORDENADA_H
#define COORDENADA_H

#include <bitset>
#include <QDebug>


struct Coordenada {
    double x;
    double y;
    double xScn;
    double yScn;
    std::bitset<4> pos;

    Coordenada() {
        x = 0;
        y = 0;
        xScn = 0;
        yScn = 0;
        pos.set(false);
    }

    Coordenada(double x, double y) : x(x), y(y), xScn(x), yScn(y) {
        pos.set(false);
    }

    Coordenada operator* (const Coordenada& ponto) const {
        return {this->x * ponto.x, this->y * ponto.y};
    }

    Coordenada operator- () const {
        return {-this->x, -this->y};
    }

    Coordenada operator/ (const Coordenada& ponto) const {
        return {this->x / ponto.x, this->y / ponto.y};
    }

    static float produtoVetorial(Coordenada a, Coordenada b) {
        return a.x * b.y - b.x * a.y;
    }

    static float produtoVetorial(float ax, float ay, float bx, float by) {
        return ax * by - bx * ay;
    }
};

struct Linha
{
    Coordenada p1;
    Coordenada p2;

    Linha() {}

    Linha(Coordenada c1, Coordenada c2) {
        this->p1 = c1;
        this->p2 = c2;
    }

    Linha(double ax, double ay, double bx, double by) {
        this->p1.x = ax;
        this->p1.y = ay;
        this->p2.x = bx;
        this->p2.y = by;
    }



    static Coordenada *calcularIntercecao(Linha l1, Linha l2) {
        Coordenada *resultado = new Coordenada();

        //qDebug() << "Calculando interceção...";
        //qDebug() << l1.p1.x << l1.p1.y << l1.p2.x << l1.p2.y;
        //qDebug() << l2.p1.x << l2.p1.y << l2.p2.x << l2.p2.y;

        float s1_x = l1.p2.x - l1.p1.x;
        float s1_y = l1.p2.y - l1.p1.y;
        float s2_x = l2.p2.x - l2.p1.x;
        float s2_y = l2.p2.y - l2.p1.y;

        //qDebug() << s1_x;
        //qDebug() << s1_y;
        //qDebug() << s2_x;
        //qDebug() << s2_y;

        float denom = Coordenada::produtoVetorial(s1_x, s1_y, s2_x, s2_y);
        //qDebug() << denom;


        float s = (-s1_y * (l1.p1.x - l2.p1.x) + s1_x * (l1.p1.y - l2.p1.y)) / denom;
        //qDebug() << s;
        float t = (s2_x * (l1.p1.y - l2.p1.y) - s2_y * (l1.p1.x - l2.p1.x)) / denom;
        //qDebug() << t;

        resultado->x = l1.p1.x + (t * s1_x);
        resultado->y = l1.p1.y + (t * s1_y);

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
            //qDebug() << "Foi";
            return resultado;
        }

        return nullptr;
    }
};

#endif // COORDENADA_H
