#include "Matriz.h"
#include <cmath>

Matriz::Matriz()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

Matriz Matriz::gerarMatrizT(double dx, double dy, double dz){ // transalação
    Matriz translacao;
    translacao.m[0][3] = dx;
    translacao.m[1][3] = dy;
    translacao.m[2][3] = dz;
    return translacao;
}

Matriz Matriz::gerarMatrizE(double sx, double sy, double sz){ // escala
    Matriz escala;
    escala.m[0][0] = sx;
    escala.m[1][1] = sy;
    escala.m[2][2] = sz;
    return escala;
}

Matriz Matriz::gerarMatrizRx(double angulo){ // rotação x
    Matriz rotacao;
    double rad = angulo * (M_PI/180.0);
    rotacao.m[1][1] = cos(rad);
    rotacao.m[1][2] = -sin(rad);
    rotacao.m[2][1] = sin(rad);
    rotacao.m[2][2] = cos(rad);
    return rotacao;
}

Matriz Matriz::gerarMatrizRy(double angulo){ // rotação y
    Matriz rotacao;
    double rad = angulo * (M_PI/180.0);
    rotacao.m[0][0] = cos(rad);
    rotacao.m[0][2] = sin(rad);
    rotacao.m[2][0] = -sin(rad);
    rotacao.m[2][2] = cos(rad);
    return rotacao;
}

Matriz Matriz::gerarMatrizRz(double angulo){ // rotação z
    Matriz rotacao;
    double rad = angulo * (M_PI/180.0);
    rotacao.m[0][0] = cos(rad);
    rotacao.m[0][1] = -sin(rad);
    rotacao.m[1][0] = sin(rad);
    rotacao.m[1][1] = cos(rad);
    return rotacao;
}

Matriz Matriz::gerarMatrizPerspectiva(double d)
{
    Matriz p;
    /*
        x' = x / (z/d)
        y' = y / (z/d)
        w = z/d
    */
    p.m[3][2]=1.0/d;
    p.m[3][3]=0;
    return p;
}

Matriz Matriz::operator*(const Matriz& b) const
{
    Matriz r;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            r.m[i][j]=0;
            for(int k=0;k<4;k++)
                r.m[i][j]+=m[i][k]*b.m[k][j];
        }
    }
    return r;

}

Coordenada Matriz::operator*(const Coordenada& p) const
{
    double x = m[0][0]*p.x_wc + m[0][1]*p.y_wc + m[0][2]*p.z_wc + m[0][3];
    double y = m[1][0]*p.x_wc + m[1][1]*p.y_wc + m[1][2]*p.z_wc + m[1][3];
    double z = m[2][0]*p.x_wc + m[2][1]*p.y_wc + m[2][2]*p.z_wc + m[2][3];
    double w = m[3][0]*p.x_wc + m[3][1]*p.y_wc + m[3][2]*p.z_wc + m[3][3];

    Coordenada r;

    if(fabs(w) > 0.0001){
        r.x_wc = x / w;
        r.y_wc = y / w;
        r.z_wc = z / w;
    }else{
        r.x_wc = x;
        r.y_wc = y;
        r.z_wc = z;
    }
    r.x_scn = r.x_wc;
    r.y_scn = r.y_wc;

    return r;
}