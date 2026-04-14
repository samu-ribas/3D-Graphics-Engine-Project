#ifndef FORMA_H
#define FORMA_H
#include <QPainter>

class Forma
{
public:
    virtual ~Forma() {}
    virtual void desenhar(QPainter &painter) = 0;

};

#endif // FORMA_H
