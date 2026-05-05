#include "janela.h"

Janela::Janela( double largura, double altura, double x, double y ) {
    listaPonto.push_back({x - (largura / 2.0), y - (altura  / 2.0)});
    listaPonto.push_back({x + (largura / 2.0), y - (altura  / 2.0)});
    listaPonto.push_back({x - (largura / 2.0), y + (altura  / 2.0)});
    listaPonto.push_back({x + (largura / 2.0), y + (altura  / 2.0)});
}

Coordenada Janela::getMin() {
    return listaPonto.front();
}

Coordenada Janela::getMax() {
    return listaPonto.back();
}
