#include "Forma.h"
#include "Matriz.h"

Forma::Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}

void Forma::aplicarTransformacao(const Matriz& m){
    for(Coordenada& vertice : this->p)
        vertice = m * vertice;
}

Coordenada Forma::getCentroide() const {
    if(p.empty()){
        return {0.0, 0.0, 0.0};
    }

    //algoritmo de Bounding Box em 3D
    double minX = 1e9, maxX = -1e9;
    double minY = 1e9, maxY = -1e9;
    double minZ = 1e9, maxZ = -1e9;

    for(const auto& pt : p){
        if(pt.x_wc < minX){
            minX = pt.x_wc;
        }
        if(pt.x_wc > maxX){
            maxX = pt.x_wc;
        }
        if(pt.y_wc < minY){
            minY = pt.y_wc;
        }
        if(pt.y_wc > maxY){
            maxY = pt.y_wc;
        }
        if(pt.z_wc < minZ){
            minZ = pt.z_wc;
        }
        if(pt.z_wc > maxZ){
            maxZ = pt.z_wc;
        }
    }

    return {(minX + maxX) / 2.0, (minY + maxY) / 2.0, (minZ + maxZ) / 2.0};
}

std::list<Coordenada>& Forma::getCoordenada(){
    return this->p;
}

QString Forma :: getNome() const {
    return nome;
}

TipoForma Forma :: getTipo() const {
    return o_tipo;
}

std::bitset<4> Forma :: getOutcode(double x, double y, const LimitesSCN& limites){
    std::bitset<4> code = INSIDE;

    if(x < limites.x_min)
        code |= LEFT;    // adiciona o bit da esquerda
    else if (x > limites.x_max)
        code |= RIGHT;   // adiciona o bit da direita

    if(y < limites.y_min)
        code |= BASE;    // adiciona o bit de baixo
    else if (y > limites.y_max)
        code |= TOP;       // adiciona o bit de cima

    return code;
}
