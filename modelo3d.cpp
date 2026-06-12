#include "modelo3d.h"

Modelo3D::Modelo3D(QString n, std::list<Coordenada> vertices, const QVector<QVector<int>>& facesObj) : Forma(n, TipoForma::MODELO3D){
    this->p = vertices;
    this->faces = facesObj;
}
