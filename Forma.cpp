#include "Forma.h"
#include "Matriz.h"

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

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

int Forma::obterOutCode(double x, double y, const LimitesSCN& limites){
    int code = INSIDE;
    if (x < limites.x_min) code |= LEFT;
    else if (x > limites.x_max) code |= RIGHT;
    if (y < limites.y_min) code |= BOTTOM;
    else if (y > limites.y_max) code |= TOP;
    return code;
}

bool Forma::cohenSutherland(Coordenada& p1, Coordenada& p2, const LimitesSCN& limites)
{
    int outcode1 = obterOutCode(p1.x_wc, p1.y_wc, limites);
    int outcode2 = obterOutCode(p2.x_wc, p2.y_wc, limites);
    bool aceito = false;

    while(true){
        if(!(outcode1 | outcode2)){ // ambos dentro
            aceito = true;
            break;
        }
        if (outcode1 & outcode2){   // ambos fora do mesmo lado
            break;
        }
        int outcodeOut = outcode1 ? outcode1 : outcode2;
        double x = 0.0, y = 0.0;

        //calcula interseção com as bordas do SCN
        if (outcodeOut & TOP){ //y > y_max
            x = p1.x_wc + (p2.x_wc - p1.x_wc) * (limites.y_max - p1.y_wc) / (p2.y_wc - p1.y_wc);
            y = limites.y_max;
        }
        else if(outcodeOut & BOTTOM){ //y < y_min
            x = p1.x_wc + (p2.x_wc - p1.x_wc) * (limites.y_min - p1.y_wc) / (p2.y_wc - p1.y_wc);
            y = limites.y_min;
        }
        else if(outcodeOut & RIGHT){ //x > x_max
            y = p1.y_wc + (p2.y_wc - p1.y_wc) * (limites.x_max - p1.x_wc) / (p2.x_wc - p1.x_wc);
            x = limites.x_max;
        }
        else if(outcodeOut & LEFT){ //x < x_min
            y = p1.y_wc + (p2.y_wc - p1.y_wc) * (limites.x_min - p1.x_wc) / (p2.x_wc - p1.x_wc);
            x = limites.x_min;
        }

        //substitui o ponto fora pela interseção
        if(outcodeOut == outcode1){
            p1.x_wc = x;
            p1.y_wc = y;
            outcode1 = obterOutCode(p1.x_wc, p1.y_wc, limites);
        }else{
            p2.x_wc = x;
            p2.y_wc = y;
            outcode2 = obterOutCode(p2.x_wc, p2.y_wc, limites);
        }
    }
    return aceito;
}

bool Forma::clipNearPlane(Coordenada& p1, Coordenada& p2, double z_near) {
    //ambos os pontos estão completamente atrás do observador
    if(p1.z_wc < z_near && p2.z_wc < z_near){
        return false;
    }

    //interpolação no plano z_near
    if(p1.z_wc < z_near){
        double t = (z_near - p1.z_wc) / (p2.z_wc - p1.z_wc);
        p1.x_wc = p1.x_wc + t * (p2.x_wc - p1.x_wc);
        p1.y_wc = p1.y_wc + t * (p2.y_wc - p1.y_wc);
        p1.z_wc = z_near;
    }else if(p2.z_wc < z_near){
        double t = (z_near - p2.z_wc) / (p1.z_wc - p2.z_wc);
        p2.x_wc = p2.x_wc + t * (p1.x_wc - p2.x_wc);
        p2.y_wc = p2.y_wc + t * (p1.y_wc - p2.y_wc);
        p2.z_wc = z_near;
    }

    return true; //aresta sobreviveu(total ou parcialmente)
}