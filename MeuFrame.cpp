#include "MeuFrame.h"
#include "Ponto.h"
#include "Reta.h"
#include "Poligono.h"
#include "Matriz.h"
#include "Forma.h"
#include <cmath>
#include <QPainter>
#include <QDebug>

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent), window(0,0,1000,500) {}

void MeuFrame:: adicionarPonto(QString name, double x, double y){
    displayFile.append(new Ponto(name ,x ,y));
    recalcularSCN();
}

void MeuFrame:: adicionarReta(QString name, double x1, double y1, double x2, double y2){
    displayFile.append(new Reta(name, x1,y1,x2,y2));
    recalcularSCN();
}

void MeuFrame:: adicionarPoligono(QString name, std::list<Coordenada> pontos){
    displayFile.append(new Poligono(name, pontos));
    recalcularSCN();
}

void MeuFrame::transladarObjeto(QString n, double dx, double dy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Matriz t = Matriz::gerarMatrizT(dx, dy);
            df->aplicarTransformacao(t);
            break;
        }
    }
}

void MeuFrame::escalarObjeto(QString n, double sx, double sy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Coordenada centro = df->getCentroide();
            Matriz mToOrigin = Matriz::gerarMatrizT(-centro.x_wc, -centro.y_wc);
            Matriz escala = Matriz::gerarMatrizE(sx, sy);
            Matriz mToReturn = Matriz::gerarMatrizT(centro.x_wc, centro.y_wc);

            Matriz composta = mToReturn * escala * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
}

void MeuFrame::rotacionarObjeto(QString n, double angulo, double x, double y, bool usarCentroide){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome() == n){
            double px, py;

            if(usarCentroide){
                Coordenada centro = df->getCentroide();
                px = centro.x_wc;
                py = centro.y_wc;
            }else{
                int larg_vp = this->width() - 80;
                int alt_vp  = this->height() - 80;

                if (larg_vp <= 0 || alt_vp <= 0 || window.largura == 0 || window.altura == 0) return;

                double x_scn = x / (larg_vp / 2.0);
                double y_scn = y / (alt_vp / 2.0);

                px = x_scn * (window.largura / 2.0) + window.centro_x;
                py = y_scn * (window.altura / 2.0) + window.centro_y;
            }
            Matriz mToOrigin = Matriz::gerarMatrizT(-px, -py);
            Matriz mRotation = Matriz::gerarMatrizR(-angulo);
            Matriz mToReturn = Matriz::gerarMatrizT(px, py);

            Matriz composta = mToReturn * mRotation * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
}

bool MeuFrame::contemObjeto(const QString& nome) const {
    for(Forma* df : std::as_const(displayFile)) {
        if(df->getNome() == nome)
            return true;
    }
    return false;
}

void MeuFrame::recalcularSCN(){
    Matriz mTranslacao;
    Matriz mRotacao;
    Matriz mEscala;

    mTranslacao.m[0][2] = -window.centro_x;
    mTranslacao.m[1][2] = -window.centro_y;

    double rad = -window.angulo * (M_PI/180.0);
    mRotacao.m[0][0] = cos(rad);
    mRotacao.m[0][1] = -sin(rad);
    mRotacao.m[1][0] = sin(rad);
    mRotacao.m[1][1] = cos(rad);

    mEscala.m[0][0] = 2.0/window.largura;
    mEscala.m[1][1] = 2.0/window.altura;

    this->mCameraAtual = mEscala * mRotacao * mTranslacao;
    this->update();
}


void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    this->window.desenharViewport(painter, this->width(), this->height());

    int larg_vp = this->width() - 80;
    int alt_vp = this->height() - 80;

    for(Forma* df : std::as_const(displayFile)){
        if(df->verificarClipping(this->window)){
            df->desenhar(painter, this->mCameraAtual, larg_vp, alt_vp);
        }
    }
}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}