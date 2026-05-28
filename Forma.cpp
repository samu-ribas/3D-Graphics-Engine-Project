#include "Forma.h"
#include "Matriz.h"

Forma::Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}

void Forma::aplicarTransformacao(const Matriz& m){
    for(Coordenada& vertice : this->p)
        vertice = m * vertice;
}

Coordenada Forma :: getCentroide() const{
    double cx = 0.0, cy = 0.0;
    if(p.empty())
        return {0.0, 0.0};

    for(const auto& pt : p){
        cx += pt.x_wc;
        cy += pt.y_wc;
    }
    return {cx / p.size(), cy / p.size()};
}

std::list<Coordenada>& Forma::getCoordenada(){ return this->p; }

QString Forma :: getNome() const { return nome; }

TipoForma Forma :: getTipo() const { return o_tipo; }

int Forma ::getOutcode(double x, double y, const LimitesWindow& limites){
    int code = INSIDE;

    if(x < limites.x_min)
        code |= LEFT;    // adiciona o bit da esquerda
    else if (x > limites.x_max)
        code |= RIGHT;   // adiciona o bit da direita

    if(y < limites.y_min)
        code |= BOTTOM;    // adiciona o bit de baixo
    else if (y > limites.y_max)
        code |= TOP;       // adiciona o bit de cima

    return code;
}