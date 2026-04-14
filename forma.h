#ifndef FORMA_H
#define FORMA_H
#include <QPainter>

class Forma
{
public:
    virtual ~Forma() {}
    virtual void desenhar(QPainter &painter) = 0;
    /*
    virtual bool contem(int px, int py) = 0;
    virtual void setPosicao(int x, int y) = 0;
    virtual void setEspessura(int e) = 0;
    virtual int getEspessura() const = 0;
    */
};

#endif // FORMA_H
