#include "ponto.h"

Ponto::Ponto(int x, int y) : m_x(x), m_y(y){}

void Ponto::desenhar(QPainter &painter){
    QPen caneta(Qt::white, 5);
    painter.setPen(caneta);
    painter.drawPoint(m_x, m_y);
}
