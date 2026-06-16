#ifndef MODELO3D_H
#define MODELO3D_H

#include "Forma.h"
#include "Matriz.h"

struct FaceVertex {
    int vertex_index;   // índice do vértice
};
class Modelo3D : public Forma
{
public:
    Modelo3D(QString n, std::list<Coordenada> vertices, const std::vector<std::vector<int>>& facesObj);


    static Modelo3D* carregarOBJ( const QString& nome, const QString& caminhoRecurso);

    void desenhar(QPainter &painter, const Matriz& mCam, const Window& win);

private:
     std::vector< std::vector<int> > faces;
     std::list<Coordenada> vertices;
};

#endif // MODELO3D_H
