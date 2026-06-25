#ifndef VIEWPORT_H
#define VIEWPORT_H

struct LimitesSCN {
    double x_min;
    double x_max;
    double y_min;
    double y_max;
};

class Viewport {
public:
    Viewport(double x = 0.0, double y = 0.0, double w = 500.0, double h = 250.0);

    static LimitesSCN getLimitesSCN();

    double getLargura() const;
    double getAltura() const;
    double getXvp() const;
    double getYvp() const;

    void setXvp(double x);
    void setYvp(double y);
    void setLargura(double valor);
    void setAltura(double valor);

private:
    double x_vp;
    double y_vp;
    double largura;
    double altura;
};
#endif // VIEWPORT_H