#ifndef MODELO3D_H
#define MODELO3D_H

#include "Forma.h"
#include "Matriz.h"

class Modelo3D : public Forma
{
public:
    Modelo3D(QString n, std::list<Coordenada> vertices, const std::vector<std::vector<int>>& facesObj);


    static Modelo3D* carregarOBJ( const QString& nome, const QString& caminhoRecurso);

    void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) override  ;

private:
     std::vector< std::vector<int> > faces;
     std::list<Coordenada> vertices;
};

#endif // MODELO3D_H
