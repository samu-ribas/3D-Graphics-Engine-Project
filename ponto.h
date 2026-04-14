#ifndef PONTO_H
#define PONTO_H

#include "forma.h"

class Ponto : public Forma
{
public:
    Ponto(int x, int y);

    void desenhar(QPainter &painter) override;
    /*
    virtual bool contem(int px, int py) override;
    virtual void setPosicao(int x, int y) override;
    virtual void setEspessura(int e) override;
    virtual int getEspessura() const override;
    */
private:
    int m_x;
    int m_y;
    //int m_espessura;
};

#endif // PONTO_H
