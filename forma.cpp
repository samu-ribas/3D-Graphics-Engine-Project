#include "forma.h"

Forma::Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}

Coordenada Forma :: getCentroide() const { // retorna o centroide do objeto
    double cx = 0.0, cy = 0.0;
    if(p.empty())
        return {0.0, 0.0};

    for(const auto& pt : p){
        cx += pt.x_wc;
        cy += pt.y_wc;
    }
    return {cx / p.size(), cy / p.size()};
}

std::list<Coordenada>& Forma::getCoordenada(){
    return this->p;
}

QString Forma :: getNome() const { return nome; }

TipoForma Forma :: getTipo() const { return o_tipo; }
