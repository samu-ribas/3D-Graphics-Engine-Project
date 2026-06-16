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
    Window(double cx, double cy, double w, double h);

    void setLimites();

    LimitesWindow getLimites() const;

    static LimitesWindow getLimitesSCN();
    int getMargem();
    double getCentro_x() const;
    double getCentro_y() const;
    double getLargura() const;
    double getAltura() const;
    double getAngulo() const;
    double getZoomViewport() const;
    void setZoomViewport(double z);
    void aumentarZoom();
    void diminuirZoom();
    void setLargura(double valor);
    void setAltura(double valor);
    void setCentro_x(double valor);
    void setCentro_y(double valor);
    void setAngulo(double valor);
    void setMargem(int valor);

private:
    int margem;
    double centro_x, centro_y, largura, altura, angulo;
    double zoomViewport;
    LimitesWindow limites;
};
#endif // WINDOW_H
