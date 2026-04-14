#include "ponto.h"

Ponto::Ponto(int x, int y) : m_x(x), m_y(y){}

void Ponto::desenhar(QPainter &painter){

    // 1. Cria a caneta com a cor e a espessura desejadas
    QPen caneta(Qt::white, 5);

    // 2. Define o formato da caneta para redondo (bolinha)
    //caneta.setCapStyle(Qt::RoundCap);

    // 3. Entrega a caneta configurada para o painter
    painter.setPen(caneta);

    // 4. Desenha o ponto
    painter.drawPoint(m_x, m_y);
}
/*
bool Ponto::contem(int px, int py) {
    int raio = (m_espessura < 5) ? 5 : m_espessura / 2;
    double distancia = std::sqrt(std::pow(px - m_x, 2) + std::pow(py - m_y, 2));
    return distancia <= raio;
}

void Ponto::setPosicao(int x, int y) {
    m_x = x;
    m_y = y;
}

void Ponto::setEspessura(int e) {
    m_espessura = e;
}

int Ponto::getEspessura() const {
    return m_espessura;
}
*/