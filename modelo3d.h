#ifndef MODELO3D_H
#define MODELO3D_H

#include <QVector>
#include "Forma.h"

class Modelo3D : public Forma
{
public:
    Modelo3D(QString n, std::list<Coordenada> vertices, const QVector<QVector<int>>& faces);

private:
     QVector<QVector<int>> faces;
};

#endif // MODELO3D_H
